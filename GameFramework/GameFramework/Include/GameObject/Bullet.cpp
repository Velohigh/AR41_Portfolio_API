
#include "Bullet.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Scene/Camera.h"
#include "../Collision/ColliderBox.h"
#include "../Collision/ColliderCircle.h"
#include "Effect.h"
#include "../GameManager.h"
#include "Player.h"
#include "../Resource/Texture/Texture.h"
#include "Effect_SniperBullet.h"

CBullet::CBullet()	:
	m_Damage(0.f)
{
	SetTypeID<CBullet>();
}

CBullet::CBullet(const CBullet& Obj) :
	CGameObject(Obj),
	m_Distance(Obj.m_Distance)
{
}

CBullet::~CBullet()
{
}

bool CBullet::Init()
{
	CGameObject::Init();

	m_MoveSpeed = 1100.f;

	SetSize(48.f, 48.f);
	SetPivot(0.5f, 0.5f);
	
	CColliderCircle* Circle = AddCollider<CColliderCircle>("Body");

	Circle->SetRadius(10.f);
	//Circle->SetCollisionProfile("Monster");

	Circle->SetCollisionBeginFunction<CBullet>(this, &CBullet::CollisionBegin);
	Circle->SetCollisionEndFunction<CBullet>(this, &CBullet::CollisionEnd);

	SetTexture("Bullet_y", TEXT("enemy_bullet.bmp"));

	// 회전 이미지용 Plg 텍스쳐
	m_Scene->GetSceneResource()->LoadTexture("Plg", TEXT("Plg.bmp"));
	m_PlgTexture = m_Scene->GetSceneResource()->FindTexture("Plg");


	m_bRotate = true;

	return true;
}

void CBullet::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	Move(m_MoveDir * DELTA_TIME * m_MoveSpeed);
	m_EnemyAttackDir = m_MoveDir * m_MoveSpeed + Vector2{ 0.f, -400.f };

	Vector2 NewVector = {};
	m_Angle = NewVector.Angle(m_MoveDir);

}

void CBullet::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);

	// 벽에 부딪히면 총알 삭제
	int Color = m_MapColTexture->GetImagePixel(m_Pos);
	if (Color == RGB(0, 0, 0))
		SetActive(false);


	// 이미지 회전에 사용할 변수들
	float fCenterX = m_Texture->GetWidth() / 2.f;
	float fCenterY = m_Texture->GetHeight() / 2.f;
	float fDis = sqrtf(fCenterX * fCenterX + fCenterY * fCenterY);

	m_ptPos[0].x = (LONG)(fCenterX + cosf((135.f + m_Angle) * PI / 180.f) * fDis);
	m_ptPos[0].y = (LONG)(fCenterY - sinf((135.f + m_Angle) * PI / 180.f) * fDis);
	m_ptPos[1].x = (LONG)(fCenterX + cosf((45.f + m_Angle) * PI / 180.f) * fDis);
	m_ptPos[1].y = (LONG)(fCenterY - sinf((45.f + m_Angle) * PI / 180.f) * fDis);
	m_ptPos[2].x = (LONG)(fCenterX + cosf((225.f + m_Angle) * PI / 180.f) * fDis);
	m_ptPos[2].y = (LONG)(fCenterY - sinf((225.f + m_Angle) * PI / 180.f) * fDis);

}

void CBullet::Render(HDC hDC, float DeltaTime)
{
	PlgBlt(m_PlgTexture->GetDC(),
		m_ptPos,
		m_Texture->GetDC(),
		0, 0,
		48, 48,
		NULL, NULL, NULL);

	CGameObject::Render(hDC, DeltaTime);

	//Vector2	RenderLT;
	//RenderLT = m_Pos - m_Pivot * m_Size - m_Scene->GetCamera()->GetPos();

	//Ellipse(hDC, (int)RenderLT.x, (int)RenderLT.y,
	//	(int)(RenderLT.x + m_Size.x), (int)(RenderLT.y + m_Size.y));
}

void CBullet::CollisionBegin(CCollider* Src, CCollider* Dest)
{
	
	if (Dest == m_Scene->GetPlayer()->FindCollider("HitBox"))
	{
		if (static_cast<CPlayer*>(m_Scene->GetPlayer())->GetState() != PlayerState::Dodge)
			SetActive(false);

		// 플레이어 CollisionBegin 이 먼저 실행되서 의미가 없지만 일단 남겨둠.
		static_cast<CPlayer*>(Dest->GetOwner())->SetEnemyAttackDir(m_MoveDir * m_MoveSpeed + Vector2{ 0.f, -400.f });

	}

	// 플레이어 공격에 닿을경우 플레이어 총알이 된다.
	else if (Dest == m_Scene->GetPlayer()->FindCollider("PlayerAttack"))
	{
		m_MoveDir *= -1.f;
		FindCollider("Body")->SetCollisionProfile("PlayerAttack");

		CEffect_SniperBullet* NewEffect = m_Scene->CreateObject<CEffect_SniperBullet>("SniperBullet");
		NewEffect->SetPos(m_Pos);
		NewEffect->AddAnimation("spr_sniperbullet", false, 0.15f);
		NewEffect->SetPivot(0.5f, 0.5f);

		CEffect* SlashhitEffect = m_Scene->CreateObject<CEffect>("SlashHit");
		SlashhitEffect->SetPos(Src->GetHitPoint());
		SlashhitEffect->AddAnimation("effect_slash_hit", false, 0.1f);
		SlashhitEffect->SetPivot(0.5f, 0.5f);

		m_Scene->GetSceneResource()->SoundPlay("reflect");

	}

	// 플레이어 총알에 적이 맞을경우
	else if (Dest->GetOwner()->GetState() != ObjState::Dead && 
		Dest->GetOwner()->GetState() != ObjState::HurtFly &&
		Dest->GetOwner()->GetState() != ObjState::HurtGround &&
		Dest->GetOwner() != m_Scene->GetPlayer())
	{
		Dest->GetOwner()->SetEnemyAttackDir(m_MoveDir * m_MoveSpeed + Vector2{ 0.f, -400.f });
		Dest->GetOwner()->SetState(ObjState::HurtFly);
		SetActive(false);
		m_Scene->GetSceneResource()->SoundPause("death_bullet");

		CEffect* SlashhitEffect = m_Scene->CreateObject<CEffect>("SlashHit");
		SlashhitEffect->SetPos(Src->GetHitPoint());
		SlashhitEffect->AddAnimation("effect_slash_hit", false, 0.1f);
		SlashhitEffect->SetPivot(0.5f, 0.5f);

	}

}

void CBullet::CollisionEnd(CCollider* Src, CCollider* Dest)
{
}
