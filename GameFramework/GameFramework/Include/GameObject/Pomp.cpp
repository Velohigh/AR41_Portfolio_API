
#include "Pomp.h"
#include "../Collision/ColliderBox.h"
#include "../Collision/ColliderCircle.h"
#include <random>
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "Effect_BloodRemain.h"
#include "Effect_BloodAnimation.h"
#include "Effect_BloodAnimation2.h"
#include "Effect_Hit_Lazer.h"
#include "Effect_Enemy_Follow.h"
#include "../GameManager.h"
#include "../Collision/CollisionManager.h"
#include "../Resource/Texture/Texture.h"
#include "Player.h"
#include "../Scene/SceneCollision.h"

extern Vector2 g_AttackDir;
extern Vector2 g_EnemyAttackDir;

CPomp::CPomp()
{
	SetTypeID<CPomp>();
}

CPomp::CPomp(const CPomp& Obj) :
	CCharacter(Obj)
{
}

CPomp::~CPomp()
{
}

bool CPomp::Init()
{
	CGameObject::Init();

	CreateAnimation();

	SetSize(36.f, 70.f);
	SetRenderScale(2);
	SetPivot(0.5f, 1.f);

	// �浹ü �߰�
	CColliderBox* Box = AddCollider<CColliderBox>("Body");
	Box->SetExtent(36.f, 70.f);
	Box->SetOffset(0.f, -35.f);
	Box->SetCollisionProfile("MonsterHitBox");

	// �浹ü �þ� �߰�
	m_ViewCollider = AddCollider<CColliderBox>("View");
	m_ViewCollider->SetExtent(520.f, 160.f);
	m_ViewCollider->SetCollisionProfile("MonsterView");

	// �浹ü ���� ���� �߰�
	m_AttackRangeCollider = AddCollider<CColliderCircle>("AttackRange");
	m_AttackRangeCollider->SetRadius(70.f);
	m_AttackRangeCollider->SetOffset(0.f, -35.f);
	m_AttackRangeCollider->SetCollisionProfile("Monster");



	m_ViewCollider->SetCollisionBeginFunction<CPomp>(this, &CPomp::ViewCollisionBegin);
	m_ViewCollider->SetCollisionEndFunction<CPomp>(this, &CPomp::ViewCollisionEnd);

	m_AnimationName = "spr_pomp_idle_";
	m_CurState = ObjState::Idle;
	m_CurDir = ObjDir::Right;
	m_ChangeDirText = "right";

	// �ִϸ��̼�
	AddAnimation("spr_pomp_idle_left", true, 0.56f);
	AddAnimation("spr_pomp_idle_right", true, 0.56f);

	AddAnimation("spr_pomp_walk_left", true, 0.7f);
	AddAnimation("spr_pomp_walk_right", true, 0.7f);

	AddAnimation("spr_pomp_run_left", true, 0.7f);
	AddAnimation("spr_pomp_run_right", true, 0.7f);

	AddAnimation("spr_pomp_attack_left", true, 0.42f);
	AddAnimation("spr_pomp_attack_right", true, 0.42f);

	AddAnimation("spr_pomp_turn_left", true, 0.48f);
	AddAnimation("spr_pomp_turn_right", true, 0.48f);

	AddAnimation("spr_pomp_hurtground_left", false, 0.96f);
	AddAnimation("spr_pomp_hurtground_right", false, 0.96f);

	AddAnimation("spr_pomp_hurtfly_left", false, 0.8f);
	AddAnimation("spr_pomp_hurtfly_right", false, 0.8f);

	AddAnimation("spr_pomp_knockdown_left", false, 1.54f);
	AddAnimation("spr_pomp_knockdown_right", false, 1.54f);


	AddNotify<CPomp>("spr_pomp_attack_left", 4, this, &CPomp::CreateAttackCollision);
	AddNotify<CPomp>("spr_pomp_attack_right", 4, this, &CPomp::CreateAttackCollision);

	return true;
}

void CPomp::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	if (static_cast<CPlayer*>(m_Scene->GetPlayer())->GetState() == PlayerState::Dead &&
		m_CurState != ObjState::Dead &&
		m_CurState != ObjState::HurtFly &&
		m_CurState != ObjState::HurtGround)
		StateChange(ObjState::Idle);
	else
	{
		DirAnimationCheck();
		ObjStateUpdate();
	}

	if (m_CurDir == ObjDir::Right)
	{
		m_ViewCollider->SetOffset(250.f, -35.f);
		m_MyAttackDir = Vector2{ 1.f, -0.5f } *800;
	}
	else if (m_CurDir == ObjDir::Left)
	{
		m_ViewCollider->SetOffset(-250.f, -35.f);
		m_MyAttackDir = Vector2{ -1.f, -0.5f } *800;
	}


}

void CPomp::PostUpdate(float DeltaTime)
{
	CCharacter::PostUpdate(DeltaTime);

}

void CPomp::Render(HDC hDC, float DeltaTime)
{
	CCharacter::Render(hDC, DeltaTime);

}

float CPomp::InflictDamage(float Damage)
{
	return 0.0f;
}

void CPomp::ViewCollisionBegin(CCollider* Src, CCollider* Dest)
{
	if (Dest->GetOwner() != m_Scene->GetPlayer())
	{
		if (m_CurState != ObjState::HurtFly &&
			m_CurState != ObjState::HurtGround &&
			m_CurState != ObjState::Dead &&
			m_CurState != ObjState::Run)
		{
			if (m_LastView == nullptr)
			{
				m_LastView = Dest;
			}


			if (Dest->GetOwner()->GetState() == ObjState::Dead ||
				Dest->GetOwner()->GetState() == ObjState::HurtFly ||
				Dest->GetOwner()->GetState() == ObjState::HurtGround)
				StateChange(ObjState::Run);
		}
	}

}

void CPomp::ViewCollisionEnd(CCollider* Src, CCollider* Dest)
{
	if (m_LastView != nullptr)
	{
		m_LastView = nullptr;
	}

}



//////////////////////////////	
////	FSM
void CPomp::IdleStart()
{
	m_StateTime[static_cast<int>(ObjState::Idle)] = 0.f;
	m_AnimationName = "spr_pomp_idle_";
	ChangeAnimation(m_AnimationName + m_ChangeDirText);
	SetSpeed(0.f);

	// ���� ���� ����
	if (m_AttackCollider != nullptr)
	{
		m_AttackCollider->SetActive(false);
		m_AttackCollider = nullptr;
	}
}

void CPomp::WalkStart()
{
	m_StateTime[static_cast<int>(ObjState::Walk)] = 0.f;
	m_AnimationName = "spr_pomp_walk_";
	ChangeAnimation(m_AnimationName + m_ChangeDirText);
	SetSpeed(80.f);
}

void CPomp::TurnStart()
{
	m_StateTime[static_cast<int>(ObjState::Turn)] = 0.f;
	m_AnimationName = "spr_pomp_turn_";
	ChangeAnimation(m_AnimationName + m_ChangeDirText);
	SetSpeed(0.f);
}

void CPomp::RunStart()
{
	m_StateTime[(int)ObjState::Run] = 0.f;

	m_AnimationName = "spr_pomp_idle_";
	ChangeAnimation(m_AnimationName + m_ChangeDirText);
	SetSpeed(0.f);

	// Enemy_Follow ����Ʈ
	if (!m_Effect_EnemyFollow)
	{
		CEffect_Enemy_Follow* EnemyFollowEffect = m_Scene->CreateObject<CEffect_Enemy_Follow>("Enemy_Follow");
		EnemyFollowEffect->SetPos(m_Pos + Vector2{ 0,-80 });
		EnemyFollowEffect->SetOwner(this);
		m_Effect_EnemyFollow = EnemyFollowEffect;
	}

}

void CPomp::AttackStart()
{
	m_AnimationName = "spr_pomp_attack_";
	ChangeAnimation(m_AnimationName + m_ChangeDirText);
	SetSpeed(0.f);

}

void CPomp::HurtGroundStart()
{

	// �Ǻ��� �ִϸ��̼�
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
	m_AnimationName = "spr_pomp_hurtground_";
	ChangeAnimation(m_AnimationName + m_ChangeDirText);

}

void CPomp::HurtFlyStart()
{
	// Blood Splat ���� ���
	{
		// �õ尪�� ��� ���� random_device ����.
		std::random_device rd;
		// random_device �� ���� ���� ���� ������ �ʱ�ȭ �Ѵ�.
		std::mt19937 gen(rd());
		// 0 ���� 99 ���� �յ��ϰ� ��Ÿ���� �������� �����ϱ� ���� �յ� ���� ����.
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

	// �÷��̾��� ���ݹ��⿡ ���� ���ư��� �¿� ����� �����ش�.
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
		// �����ڸ��� ���ڱ� ����
		CEffect_BloodRemain* BloodRemainEffect = m_Scene->CreateObject<CEffect_BloodRemain>("BloodRemain");
		BloodRemainEffect->SetPos(m_Pos + Vector2{ 0,-35 });
	}

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

	//// ��Ʈ ������ ����Ʈ
	//CEffect_Hit_Lazer* NewHitLazer = m_Scene->CreateObject<CEffect_Hit_Lazer>("HitLazer");
	//NewHitLazer->SetTexture("HitLazer", TEXT("effect_hit_lazer.bmp"));
	//NewHitLazer->SetColorKey(255, 0, 255);
	//NewHitLazer->SetOwner(this);
	//NewHitLazer->SetAngle(90.f);

	// SlashHit ����Ʈ
	CEffect* NewSlashHitEffect = m_Scene->CreateObject<CEffect>("SlashHit");
	NewSlashHitEffect->SetPos(m_Pos + Vector2{ 0, -35 });
	NewSlashHitEffect->SetDir(ObjDir::Left);
	NewSlashHitEffect->SetPivot(0.5f, 0.5f);
	NewSlashHitEffect->AddAnimation("effect_slash_hit", false, 0.1f);
	NewSlashHitEffect->SetOwner(this);


	// ��Ʈ�� ȭ�� ��鸲
	m_Scene->SetCameraShakeOn(true);


	SetPos(m_Pos + Vector2{ 0,-2 });
	m_StateTime[static_cast<int>(ObjState::HurtGround)] = 0.f;
	m_AnimationName = "spr_pomp_hurtfly_";
	ChangeAnimation(m_AnimationName + m_ChangeDirText);
	SetSpeed(0.f);

	m_MoveDir = g_AttackDir * 800;	// �¾����� �˹�

}

void CPomp::KnockDownStart()
{
	m_StateTime[static_cast<int>(ObjState::KnockDown)] = 0.f;
	m_AnimationName = "spr_pomp_knockdown_";
	ChangeAnimation(m_AnimationName + m_ChangeDirText);

}

void CPomp::DeadStart()
{
	m_Scene->AddKillCount(1);
}

void CPomp::IdleUpdate()
{
	// ���� �ൿ
	m_StateTime[static_cast<int>(ObjState::Idle)] += DELTA_TIME;
	if (m_StateTime[static_cast<int>(ObjState::Idle)] >= 2 && m_bPatrol == true)
	{
		StateChange(ObjState::Turn);
		return;
	}


	// �÷��̾� ���ݿ� ������ ���
	CCollider* PlayerAttack = m_Scene->GetPlayer()->FindCollider("PlayerAttack");
	if (true == FindCollider("Body")->CheckCollisionList(PlayerAttack))
	{
		StateChange(ObjState::HurtFly);
		return;
	}

	// �÷��̾� �߽߰� Run ���·� �Ѿư���.
	CCollider* PlayerBody = m_Scene->GetPlayer()->FindCollider("Body");
	if (true == FindCollider("View")->CheckCollisionList(PlayerBody) &&
		PlayerState::Dead != static_cast<CPlayer*>(m_Scene->GetPlayer())->CPlayer::GetState())
	{
		StateChange(ObjState::Run);
		return;
	}

	// �þ߿� ���ᰡ Run�����̸� �÷��̾ �Ѿƿ´�..
	if (true == FindCollider("View")->CheckCollisionList(m_LastView) &&
		m_LastView->GetOwner()->GetState() == ObjState::Run)
	{
		StateChange(ObjState::Run);
		return;
	}
}

void CPomp::WalkUpdate()
{
	m_StateTime[static_cast<int>(ObjState::Walk)] += DELTA_TIME;

	if (m_StateTime[static_cast<int>(ObjState::Walk)] >= m_PatrolTime)
	{
		StateChange(ObjState::Idle);
		return;
	}


	// �÷��̾� ���ݿ� ������ ���
	CCollider* PlayerAttack = m_Scene->GetPlayer()->FindCollider("PlayerAttack");
	if (true == FindCollider("Body")->CheckCollisionList(PlayerAttack))
	{
		StateChange(ObjState::HurtFly);
		return;
	}

	// �¿� �̵�
	if (m_CurDir == ObjDir::Right)
	{
		m_MoveDir = Vector2{ 1.f, 0.f };
	}
	else if (m_CurDir == ObjDir::Left)
	{
		m_MoveDir = Vector2{ -1.f, 0.f };
	}

	// �÷��̾� �߽߰� Run ���·� �Ѿƿ´�.
	CCollider* PlayerBody = m_Scene->GetPlayer()->FindCollider("Body");
	if (true == FindCollider("View")->CheckCollisionList(PlayerBody))
	{
		StateChange(ObjState::Run);
		return;
	}

	// �þ߿� ���ᰡ Run�����̸� �÷��̾ �Ѿƿ´�..
	if (true == FindCollider("View")->CheckCollisionList(m_LastView) &&
		m_LastView->GetOwner()->GetState() == ObjState::Run)
	{
		StateChange(ObjState::Run);
		return;
	}


	MapCollisionCheckMoveGround();

}

void CPomp::TurnUpdate()
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
	// �÷��̾� ���ݿ� ������ ���
	if (true == FindCollider("Body")->CheckCollisionList(PlayerAttack))
	{
		StateChange(ObjState::HurtFly);
		return;
	}
}


void CPomp::RunUpdate()
{
	m_StateTime[(int)ObjState::Run] += DELTA_TIME;

	if (m_StateTime[(int)ObjState::Run] >= 0.22f)
	{
		m_AnimationName = "spr_pomp_run_";
		ChangeAnimation(m_AnimationName + m_ChangeDirText);
		SetSpeed(340.f);


		// �÷��̾ �Ѿư����� �¿� ���� ����
		if (m_Scene->GetPlayer()->GetPos().x >= m_Pos.x)
			SetDir(ObjDir::Right);
		else if (m_Scene->GetPlayer()->GetPos().x < m_Pos.x)
			SetDir(ObjDir::Left);

		// �÷��̾ ���������� ������ ����
		CCollider* PlayerBody = m_Scene->GetPlayer()->FindCollider("Body");
		if (true == FindCollider("AttackRange")->CheckCollisionList(PlayerBody))
		{
			StateChange(ObjState::Attack);
			return;
		}

		//// �÷��̾ �Ʒ����� ��� y��ġ �̵�
		//if (m_Scene->GetPlayer()->GetPos().y > m_Pos.y)
		//	SetPos(Vector2{ m_Pos.x, m_Pos.y + 1.5f });

		// �¿� �̵�
		if (m_CurDir == ObjDir::Right)
		{
			m_MoveDir = Vector2{ 1.f, 0.f };
		}

		else if (m_CurDir == ObjDir::Left)
		{
			m_MoveDir = Vector2{ -1.f, 0.f };
		}

	}

	// �÷��̾� ���ݿ� ������ ���
	CCollider* PlayerAttack = m_Scene->GetPlayer()->FindCollider("PlayerAttack");
	if (true == FindCollider("Body")->CheckCollisionList(PlayerAttack))
	{
		StateChange(ObjState::HurtFly);
		return;
	}


	MapCollisionCheckMoveGround();

}

void CPomp::AttackUpdate()
{
	// �÷��̾� ������¸� Idle ���·�
	if (PlayerState::Dead == static_cast<CPlayer*>(m_Scene->GetPlayer())->CPlayer::GetState())
	{
		StateChange(ObjState::Idle);
		return;
	}


	// �÷��̾� ���ݿ� ������ ���
	CCollider* PlayerAttack = m_Scene->GetPlayer()->FindCollider("PlayerAttack");
	if (true == FindCollider("Body")->CheckCollisionList(PlayerAttack))
	{
		if (m_AttackCollider != nullptr)
		{
			m_AttackCollider->SetActive(false);
			m_AttackCollider = nullptr;
		}

		StateChange(ObjState::HurtFly);
		return;
	}

	// ���� ����� ������ �ٽ� Run ���·�
	if (true == m_Animation->IsEndAnimation())
	{
		if (m_AttackCollider != nullptr)
		{
			m_AttackCollider->SetActive(false);
			m_AttackCollider = nullptr;
		}

		StateChange(ObjState::Run);
		return;
	}

}

void CPomp::HurtGroundUpdate()
{
	// �Ǻ����� ������ BloodAnimation SetActive(false) �Ұ�

	// �������� ����� ������, ��� ���·�
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

void CPomp::HurtFlyUpdate()
{

	// ���߿� �� �����ϰ�� �߷¿����� �޴´�.
	// �߷� ���ӵ��� ���� ���� �ӵ�.
	{
		// �������ǿ��� ���ϴ� ��ġ�� �ȼ��� ������ ���� �� �ִ�.
		int RColor = m_MapColTexture->GetImagePixel(m_Pos + Vector2{ 0,1 });
		m_Gravity += m_GravityAccel * DELTA_TIME;
		if (m_MoveDir.y > 0.f)	// ����������
		{
			if (RGB(0, 0, 0) == RColor || RGB(255, 0, 0) == RColor ||
				m_Move.y == 0.f)	// ���� ��ų� y�̵��� 0�ϰ��
			{
				StateChange(ObjState::HurtGround);
				return;
			}
		}
		m_MoveDir += Vector2{ 0.f, 1.f } *m_Gravity * DELTA_TIME;
	}

	MapCollisionCheckMoveAirDie();

}

void CPomp::KnockDownUpdate()
{
}

void CPomp::DeadUpdate()
{
}


// Notify
void CPomp::CreateAttackCollision()
{
	// ���� ���� �浹ü �߰�
	CColliderBox* Box = AddCollider<CColliderBox>("PompAttack");
	Box->SetExtent(50.f, 50.f);

	if (m_CurDir == ObjDir::Right)
	{
		Box->SetOffset(Vector2{ 0.f, -35.f } + Vector2{ 1.f, 0.f } *50.f);
		static_cast<CPlayer*>(m_Scene->GetPlayer())->SetEnemyAttackDir(Vector2{ 1.f , -0.5f } *800);
	}
	else if (m_CurDir == ObjDir::Left)
	{
		Box->SetOffset(Vector2{ 0.f, -35.f } + Vector2{ -1.f, 0.f } *50.f);
		static_cast<CPlayer*>(m_Scene->GetPlayer())->SetEnemyAttackDir(Vector2{ -1.f , -0.5f } *800);
	}
	Box->SetCollisionProfile("MonsterAttack");
	m_AttackCollider = Box;

	m_Scene->GetSceneResource()->SoundPlay("swing");

}
