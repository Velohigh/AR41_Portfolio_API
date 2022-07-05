
#include "Gangster.h"
#include "../Collision/ColliderBox.h"
#include <random>
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "Effect_BloodRemain.h"
#include "Effect_BloodAnimation.h"
#include "Effect_BloodAnimation2.h"
#include "Effect_GunSpark.h"
#include "../GameManager.h"
#include "../Collision/CollisionManager.h"
#include "../Resource/Texture/Texture.h"
#include "Effect_Enemy_Follow.h"
#include "Player.h"
#include "GangsterLeftArm.h"
#include "Bullet.h"

extern Vector2 g_AttackDir;

CGangster::CGangster()
{
	SetTypeID<CGangster>();
}

CGangster::CGangster(const CGangster& Obj) :
	CCharacter(Obj)
{
}

CGangster::~CGangster()
{
}

bool CGangster::Init()
{
	CGameObject::Init();

	CreateAnimation();

	SetSize(36.f, 70.f);
	SetRenderScale(2);
	SetPivot(0.5f, 1.f);

	// 충돌체 추가
	CColliderBox* Box = AddCollider<CColliderBox>("Body");
	Box->SetExtent(36.f, 70.f);
	Box->SetOffset(0.f, -35.f);
	Box->SetCollisionProfile("MonsterHitBox");

	// 충돌체 시야 추가
	m_ViewCollider = AddCollider<CColliderBox>("View");
	m_ViewCollider->SetExtent(600.f, 180.f);
	m_ViewCollider->SetCollisionProfile("Monster");


	Box->SetCollisionBeginFunction<CGangster>(this, &CGangster::CollisionBegin);
	Box->SetCollisionEndFunction<CGangster>(this, &CGangster::CollisionEnd);

	m_AnimationName = "spr_gangster_idle_";
	m_CurState = ObjState::Idle;
	m_CurDir = ObjDir::Right;
	m_ChangeDirText = "right";

	// 애니메이션
	AddAnimation("spr_gangster_idle_left", true, 0.96f);
	AddAnimation("spr_gangster_idle_right", true, 0.96f);

	AddAnimation("spr_gangsteraim_left", true, 0.8f);
	AddAnimation("spr_gangsteraim_right", true, 0.8f);

	AddAnimation("spr_gangsterhurtground_left", false, 0.98f);
	AddAnimation("spr_gangsterhurtground_right", false, 0.98f);

	AddAnimation("spr_gangsterhurtfly_left", false, 0.4f);
	AddAnimation("spr_gangsterhurtfly_right", false, 0.4f);

	AddAnimation("spr_gangsterrun_left", true, 0.7f);
	AddAnimation("spr_gangsterrun_right", true, 0.7f);

	AddAnimation("spr_gangsterturn_left", false, 0.42f);
	AddAnimation("spr_gangsterturn_right", false, 0.42f);

	AddAnimation("spr_gangsterwalk_left", true, 0.56f);
	AddAnimation("spr_gangsterwalk_right", true, 0.56f);


	return true;
}

void CGangster::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	if (static_cast<CPlayer*>(m_Scene->GetPlayer())->GetState() == PlayerState::Dead &&
		m_CurState != ObjState::Dead)
		StateChange(ObjState::Idle);
	else
	{
		DirAnimationCheck();
		ObjStateUpdate();
	}

	if (m_CurDir == ObjDir::Right)
		m_ViewCollider->SetOffset(300.f, -35.f);
	else if (m_CurDir == ObjDir::Left)
		m_ViewCollider->SetOffset(-300.f, -35.f);

}

void CGangster::PostUpdate(float DeltaTime)
{
	CCharacter::PostUpdate(DeltaTime);

}

void CGangster::Render(HDC hDC, float DeltaTime)
{
	CCharacter::Render(hDC, DeltaTime);

}

float CGangster::InflictDamage(float Damage)
{
	return 0.0f;
}

void CGangster::CollisionBegin(CCollider* Src, CCollider* Dest)
{
}

void CGangster::CollisionEnd(CCollider* Src, CCollider* Dest)
{
}



//////////////////////////////	
////	FSM
void CGangster::IdleStart()
{
	m_StateTime[static_cast<int>(ObjState::Idle)] = 0.f;
	m_AnimationName = "spr_gangster_idle_";
	ChangeAnimation(m_AnimationName + m_ChangeDirText);
	SetSpeed(0.f);
}

void CGangster::WalkStart()
{
	m_StateTime[static_cast<int>(ObjState::Walk)] = 0.f;
	m_AnimationName = "spr_gangsterwalk_";
	ChangeAnimation(m_AnimationName + m_ChangeDirText);
	SetSpeed(80.f);
}

void CGangster::TurnStart()
{
	m_StateTime[static_cast<int>(ObjState::Turn)] = 0.f;
	m_AnimationName = "spr_gangsterturn_";
	ChangeAnimation(m_AnimationName + m_ChangeDirText);
	SetSpeed(0.f);
}

void CGangster::RunStart()
{
	m_AnimationName = "spr_gangsterrun_";
	ChangeAnimation(m_AnimationName + m_ChangeDirText);
	SetSpeed(320.f);

	// Enemy_Follow 이펙트
	if (!m_Effect_EnemyFollow)
	{
		CEffect_Enemy_Follow* EnemyFollowEffect = m_Scene->CreateObject<CEffect_Enemy_Follow>("Enemy_Follow");
		EnemyFollowEffect->SetPos(m_Pos + Vector2{ 0,-80 });
		EnemyFollowEffect->SetOwner(this);
		m_Effect_EnemyFollow = EnemyFollowEffect;
	}

}

void CGangster::AttackStart()
{
	m_StateTime[(int)ObjState::Attack] = 0.f;

	m_AnimationName = "spr_gangsteraim_";
	ChangeAnimation(m_AnimationName + m_ChangeDirText);
	SetSpeed(0.f);

}

void CGangster::HurtGroundStart()
{

	// 피분출 애니메이션
	if (m_CurDir == ObjDir::Left)
	{
		CEffect_BloodAnimation2* NewBloodAnimation2 = m_Scene->CreateObject<CEffect_BloodAnimation2>("BloodAnimation2");
		NewBloodAnimation2->SetPos(m_Pos);
		NewBloodAnimation2->ChangeAnimation("effect_bloodanimation2_right");
		NewBloodAnimation2->SetDir(ObjDir::Right);
		NewBloodAnimation2->SetPivot({ 0.5f, 1.f });
		NewBloodAnimation2->SetOwner(this);
	}

	else if (m_CurDir == ObjDir::Right)
	{
		CEffect_BloodAnimation2* NewBloodAnimation2 = m_Scene->CreateObject<CEffect_BloodAnimation2>("BloodAnimation2");
		NewBloodAnimation2->SetPos(m_Pos);
		NewBloodAnimation2->ChangeAnimation("effect_bloodanimation2_left");
		NewBloodAnimation2->SetDir(ObjDir::Left);
		NewBloodAnimation2->SetPivot({ 0.5f, 1.f });
		NewBloodAnimation2->SetOwner(this);
	}

	m_StateTime[static_cast<int>(ObjState::HurtGround)] = 0.f;
	m_AnimationName = "spr_gangsterhurtground_";
	ChangeAnimation(m_AnimationName + m_ChangeDirText);

}

void CGangster::HurtFlyStart()
{
	// Blood Splat 사운드 재생
	{
		// 시드값을 얻기 위한 random_device 생성.
		std::random_device rd;
		// random_device 를 통해 난수 생성 엔진을 초기화 한다.
		std::mt19937 gen(rd());
		// 0 부터 99 까지 균등하게 나타나는 난수열을 생성하기 위해 균등 분포 정의.
		std::uniform_int_distribution<int> IntRange(0, 3);
		int Value = IntRange(gen);

		switch (Value)
		{
		case 0:
			m_Scene->GetSceneResource()->SoundPlay("sound_enemy_bloodsplat1");
			break;
		case 1:
			m_Scene->GetSceneResource()->SoundPlay("sound_enemy_bloodsplat2");
			break;
		case 2:
			m_Scene->GetSceneResource()->SoundPlay("sound_enemy_bloodsplat3");
			break;
		case 3:
			m_Scene->GetSceneResource()->SoundPlay("sound_enemy_bloodsplat4");
			break;
		default:
			break;
		}
	}

	// 플레이어의 공격방향에 따라 날아가는 좌우 모션을 정해준다.
	if (g_AttackDir.x >= 0.f)
	{
		m_CurDir = ObjDir::Left;
	}
	else if (g_AttackDir.x < 0.f)
	{
		m_CurDir = ObjDir::Right;
	}

	if (m_EnemyAttackDir == Vector2{ 0.f, 0.f })
	{
		// 맞은자리에 핏자국 생성
		CEffect_BloodRemain* BloodRemainEffect = m_Scene->CreateObject<CEffect_BloodRemain>("BloodRemain");
		BloodRemainEffect->SetPos(m_Pos + Vector2{ 0,-35 });
	}

	//// 피분출 애니메이션
	//NewBloodAnimation = CreateRenderer();
	//NewBloodAnimation->CreateAnimation("effect_bloodanimation_right.bmp", "BloodAnimation_right", 0, 5, 0.06, true);
	//NewBloodAnimation->CreateAnimation("effect_bloodanimation_left.bmp", "BloodAnimation_left", 0, 5, 0.06, true);

	//NewBloodAnimation->CreateAnimation("effect_bloodanimation2_right.bmp", "BloodAnimation2_right", 0, 9, 0.06, true);
	//NewBloodAnimation->CreateAnimation("effect_bloodanimation2_left.bmp", "BloodAnimation2_left", 0, 9, 0.06, true);


	if (m_EnemyAttackDir == Vector2{ 0.f, 0.f })
	{
		if (g_AttackDir.x >= 0.f)
		{
			CEffect_BloodAnimation* NewBloodAnimation = m_Scene->CreateObject<CEffect_BloodAnimation>("BloodAnimation");
			NewBloodAnimation->SetPos(m_Pos);
			NewBloodAnimation->SetDir(ObjDir::Right);
			NewBloodAnimation->ChangeAnimation("effect_bloodanimation_right");
			NewBloodAnimation->SetOwner(this);
		}
		else if (g_AttackDir.x < 0.f)
		{
			CEffect_BloodAnimation* NewBloodAnimation = m_Scene->CreateObject<CEffect_BloodAnimation>("BloodAnimation");
			NewBloodAnimation->SetPos(m_Pos);
			NewBloodAnimation->SetDir(ObjDir::Left);
			NewBloodAnimation->ChangeAnimation("effect_bloodanimation_left");
			NewBloodAnimation->SetOwner(this);
		}
	}

	//// 히트 레이저 이펙트
	//CEffect_Hit_Lazer* NewHitLazer = m_Scene->CreateObject<CEffect_Hit_Lazer>("HitLazer");
	//NewHitLazer->SetTexture("HitLazer", TEXT("effect_hit_lazer.bmp"));
	//NewHitLazer->SetColorKey(255, 0, 255);
	//NewHitLazer->SetOwner(this);
	//NewHitLazer->SetAngle(90.f);

	// 히트시 화면 흔들림
	m_Scene->SetCameraShakeOn(true);


	SetPos(m_Pos + Vector2{ 0,-2 });
	m_StateTime[static_cast<int>(ObjState::HurtGround)] = 0.f;
	m_AnimationName = "spr_gangsterhurtfly_";
	ChangeAnimation(m_AnimationName + m_ChangeDirText);
	SetSpeed(0.f);

	m_MoveDir = g_AttackDir * 800;	// 맞았을때 넉백

}

void CGangster::DeadStart()
{
}

void CGangster::IdleUpdate()
{
	// 정찰 행동
	m_StateTime[static_cast<int>(ObjState::Idle)] += DELTA_TIME;
	if (m_StateTime[static_cast<int>(ObjState::Idle)] >= 2 && m_bPatrol == true)
	{
		StateChange(ObjState::Turn);
		return;
	}


	// 플레이어 공격에 맞으면 사망
	CCollider* PlayerAttack = m_Scene->GetPlayer()->FindCollider("PlayerAttack");
	if (true == FindCollider("Body")->CheckCollisionList(PlayerAttack))
	{
		StateChange(ObjState::HurtFly);
		return;
	}

	// 플레이어 발견시 Run 상태로 쫓아온다.
	CCollider* PlayerBody = m_Scene->GetPlayer()->FindCollider("Body");
	if (true == FindCollider("View")->CheckCollisionList(PlayerBody) &&
		PlayerState::Dead != static_cast<CPlayer*>(m_Scene->GetPlayer())->CPlayer::GetState())
	{
		StateChange(ObjState::Run);
		return;
	}

}

void CGangster::WalkUpdate()
{
	m_StateTime[static_cast<int>(ObjState::Walk)] += DELTA_TIME;

	if (m_StateTime[static_cast<int>(ObjState::Walk)] >= 5)
	{
		StateChange(ObjState::Idle);
		return;
	}


	// 플레이어 공격에 맞으면 사망
	CCollider* PlayerAttack = m_Scene->GetPlayer()->FindCollider("PlayerAttack");
	if (true == FindCollider("Body")->CheckCollisionList(PlayerAttack))
	{
		StateChange(ObjState::HurtFly);
		return;
	}

	// 좌우 이동
	if (m_CurDir == ObjDir::Right)
	{
		m_MoveDir = Vector2{ 1.f, 0.f };
	}
	else if (m_CurDir == ObjDir::Left)
	{
		m_MoveDir = Vector2{ -1.f, 0.f };
	}

	// 플레이어 발견시 Run 상태로 쫓아온다.
	CCollider* PlayerBody = m_Scene->GetPlayer()->FindCollider("Body");
	if (true == FindCollider("View")->CheckCollisionList(PlayerBody))
	{
		StateChange(ObjState::Run);
		return;
	}

	MapCollisionCheckMoveGround();

}

void CGangster::TurnUpdate()
{
	if (true == m_Animation->IsEndAnimation())
	{
		StateChange(ObjState::Walk);
		if (m_CurDir == ObjDir::Right)
		{
			m_CurDir = ObjDir::Left;
		}
		else if (m_CurDir == ObjDir::Left)
		{
			m_CurDir = ObjDir::Right;
		}
		return;
	}

	CCollider* PlayerAttack = m_Scene->GetPlayer()->FindCollider("PlayerAttack");
	// 플레이어 공격에 맞으면 사망
	if (true == FindCollider("Body")->CheckCollisionList(PlayerAttack))
	{
		StateChange(ObjState::HurtFly);
		return;
	}
}


void CGangster::RunUpdate()
{
	// 플레이어 공격에 맞으면 사망
	CCollider* PlayerAttack = m_Scene->GetPlayer()->FindCollider("PlayerAttack");
	if (true == FindCollider("Body")->CheckCollisionList(PlayerAttack))
	{
		StateChange(ObjState::HurtFly);
		return;
	}

	// 플레이어를 바라보도록 좌우 방향 조정
	if (m_Scene->GetPlayer()->GetPos().x >= m_Pos.x)
		SetDir(ObjDir::Right);
	else if (m_Scene->GetPlayer()->GetPos().x < m_Pos.x)
		SetDir(ObjDir::Left);

	// 플레이어가 일정범위에 들어오면 공격
	CCollider* PlayerBody = m_Scene->GetPlayer()->FindCollider("Body");
	if (true == FindCollider("View")->CheckCollisionList(PlayerBody))
	{
		StateChange(ObjState::Attack);
		return;
	}


	// 좌우 이동
	if (m_CurDir == ObjDir::Right)
	{
		m_MoveDir = Vector2{ 1.f, 0.f };
	}

	else if (m_CurDir == ObjDir::Left)
	{
		m_MoveDir = Vector2{ -1.f, 0.f };
	}


	MapCollisionCheckMoveGround();



}

void CGangster::AttackUpdate()
{
	// 플레이어를 바라보도록 좌우 방향 조정
	if (m_Scene->GetPlayer()->GetPos().x >= m_Pos.x)
		SetDir(ObjDir::Right);
	else if (m_Scene->GetPlayer()->GetPos().x < m_Pos.x)
		SetDir(ObjDir::Left);


	// 플레이어 사망상태면 Idle 상태로
	if (PlayerState::Dead == static_cast<CPlayer*>(m_Scene->GetPlayer())->CPlayer::GetState())
	{
		StateChange(ObjState::Idle);
		return;
	}


	// 플레이어 공격에 맞으면 사망
	CCollider* PlayerAttack = m_Scene->GetPlayer()->FindCollider("PlayerAttack");
	if (true == FindCollider("Body")->CheckCollisionList(PlayerAttack))
	{
		StateChange(ObjState::HurtFly);
		return;
	}

	m_StateTime[(int)ObjState::Attack] += DELTA_TIME;
	if (m_StateTime[(int)ObjState::Attack] >= 0.7f)
	{
		// 총알 발사 이펙트
		CEffect_GunSpark* NewEffect = m_Scene->CreateObject<CEffect_GunSpark>("GunSpark");
		m_Scene->GetSceneResource()->SoundPlay("fire");
		if (m_CurDir == ObjDir::Right)
		{
			NewEffect->SetPos(m_Pos + Vector2{ 80.f, -44.f });
			NewEffect->AddAnimation("spr_gunspark_right", true, 0.15f);
		}

		else if (m_CurDir == ObjDir::Left)
		{
			NewEffect->SetPos(m_Pos + Vector2{ -80.f, -44.f });
			NewEffect->AddAnimation("spr_gunspark_left", true, 0.15f);
		}
		NewEffect->SetPivot(0.5f, 0.5f);

		m_StateTime[(int)ObjState::Attack] -= 0.7f;

		// 총알 생성
		CBullet* NewBullet = m_Scene->CreateObject<CBullet>("Bullet");
		if (m_CurDir == ObjDir::Right)
		{
			NewBullet->SetPos(m_Pos + Vector2{ 40.f, -44.f });

			Vector2 ToPlayerVector = (m_Scene->GetPlayer()->GetPos()) - m_Pos;
			ToPlayerVector.Normalize();
			NewBullet->SetMoveDir(ToPlayerVector);
		}

		else if (m_CurDir == ObjDir::Left)
		{
			NewBullet->SetPos(m_Pos + Vector2{ -40.f, -44.f });

			Vector2 ToPlayerVector = (m_Scene->GetPlayer()->GetPos()) - m_Pos;
			ToPlayerVector.Normalize();
			NewBullet->SetMoveDir(ToPlayerVector);
		}
		NewBullet->FindCollider("Body")->SetCollisionProfile("MonsterBullet");
		NewBullet->SetMapTexture(m_MapColTexture);
	}


	// 공격 모션이 끝나면 다시 Run 상태로
	if (true == m_Animation->IsEndAnimation())
	{
		StateChange(ObjState::Run);
		return;
	}

}

void CGangster::HurtGroundUpdate()
{
	// 피분출이 끝나면 BloodAnimation SetActive(false) 할것

	// 쓰러지는 모션이 끝나면, 사망 상태로
	if (true == m_Animation->IsEndAnimation())
	{
		//FindCollider("Box")->SetActive(false);
		//SetEnable(false);
		StateChange(ObjState::Dead);
		return;
	}

	m_MoveDir += -(m_MoveDir * DELTA_TIME * 3.4f);

	if (1.f >= m_MoveDir.Length())
	{
		m_MoveDir = Vector2{ 0,0 };
	}

	MapCollisionCheckMoveGroundDie();

}

void CGangster::HurtFlyUpdate()
{

	// 공중에 뜬 상태일경우 중력영향을 받는다.
	// 중력 가속도에 따른 낙하 속도.
	{
		// 내포지션에서 원하는 위치의 픽셀의 색상을 구할 수 있다.
		int RColor = m_MapColTexture->GetImagePixel(m_Pos + Vector2{ 0,1 });
		m_Gravity += m_GravityAccel * DELTA_TIME;
		if (m_MoveDir.y > 0.f)	// 떨어질때만
		{
			if (RGB(0, 0, 0) == RColor || RGB(255, 0, 0) == RColor ||
				m_Move.y == 0.f)	// 땅에 닿거나 y이동이 0일경우
			{
				StateChange(ObjState::HurtGround);
				return;
			}
		}
		m_MoveDir += Vector2{ 0.f, 1.f } *m_Gravity * DELTA_TIME;
	}

	MapCollisionCheckMoveAirDie();

}

void CGangster::DeadUpdate()
{
}
