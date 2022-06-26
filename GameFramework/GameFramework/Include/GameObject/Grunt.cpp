
#include "Grunt.h"
#include "../Collision/ColliderBox.h"
#include <random>
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "Effect_BloodRemain.h"

extern Vector2 g_AttackDir;

CGrunt::CGrunt()
{
	SetTypeID<CGrunt>();
}

CGrunt::CGrunt(const CGrunt& Obj) :
	CCharacter(Obj)
{
}

CGrunt::~CGrunt()
{
}

bool CGrunt::Init()
{
	CGameObject::Init();

	SetSize(36.f, 70.f);

	// �浹ü �߰�
	CColliderBox* Box = AddCollider<CColliderBox>("Body");
	Box->SetExtent(36.f, 70.f);
	Box->SetOffset(0.f, -35.f);
	Box->SetCollisionProfile("Monster");

	Box->SetCollisionBeginFunction<CGrunt>(this, &CGrunt::CollisionBegin);
	Box->SetCollisionEndFunction<CGrunt>(this, &CGrunt::CollisionEnd);

	m_AnimationName = "spr_grunt_idle_";
	m_CurState = ObjState::Idle;
	m_CurDir = ObjDir::Right;
	m_ChangeDirText = "right";

	// �浹�� ����
	SetMapTexture("room_factory_2_ColMap", TEXT("room_factory_2_ColMap.bmp"), "MapPath");

	return true;
}

void CGrunt::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	DirAnimationCheck();
	ObjStateUpdate();


}

void CGrunt::PostUpdate(float DeltaTime)
{
	CCharacter::PostUpdate(DeltaTime);

}

void CGrunt::Render(HDC hDC, float DeltaTime)
{
	CCharacter::Render(hDC, DeltaTime);

}

float CGrunt::InflictDamage(float Damage)
{
	return 0.0f;
}

void CGrunt::CollisionBegin(CCollider* Src, CCollider* Dest)
{
}

void CGrunt::CollisionEnd(CCollider* Src, CCollider* Dest)
{
}



//////////////////////////////	
////	FSM
void CGrunt::IdleStart()
{
	m_StateTime[static_cast<int>(ObjState::Idle)] = 0.f;
	m_AnimationName = "spr_grunt_idle_";
	ChangeAnimation(m_AnimationName + m_ChangeDirText);
	SetSpeed(0.f);
}

void CGrunt::WalkStart()
{
	m_StateTime[static_cast<int>(ObjState::Walk)] = 0.f;
	m_AnimationName = "spr_grunt_walk_";
	ChangeAnimation(m_AnimationName + m_ChangeDirText);
	SetSpeed(80.f);
}

void CGrunt::TurnStart()
{
	m_StateTime[static_cast<int>(ObjState::Turn)] = 0.f;
	m_AnimationName = "spr_grunt_turn_";
	ChangeAnimation(m_AnimationName + m_ChangeDirText);
	SetSpeed(0.f);
}

void CGrunt::RunStart()
{
}

void CGrunt::AttackStart()
{
}

void CGrunt::HurtGroundStart()
{

	//// �Ǻ��� �ִϸ��̼�
	//if (m_CurDir == ObjDir::Left)
	//{
	//	NewBloodAnimation->ChangeAnimation("BloodAnimation2_right");
	//	NewBloodAnimation->SetPivot({ 50.f, -45.f });
	//}
	//else if (CurDir_ == ActorDir::Right)
	//{
	//	NewBloodAnimation->ChangeAnimation("BloodAnimation2_left");
	//	NewBloodAnimation->SetPivot({ -50.f, -45.f });
	//}

	m_StateTime[static_cast<int>(ObjState::HurtGround)] = 0.f;
	m_AnimationName = "spr_grunt_hurtground_";
	ChangeAnimation(m_AnimationName + m_ChangeDirText);

}

void CGrunt::HurtFlyStart()
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

	// �����ڸ��� ���ڱ� ����
	CEffect_BloodRemain* BloodRemainEffect = m_Scene->CreateObject<CEffect_BloodRemain>("BloodRemain");
	BloodRemainEffect->SetPos(m_Pos + Vector2{ 0,-35 });

	// �Ǻ��� �ִϸ��̼�
	NewBloodAnimation = CreateRenderer();
	NewBloodAnimation->CreateAnimation("effect_bloodanimation_right.bmp", "BloodAnimation_right", 0, 5, 0.06, true);
	NewBloodAnimation->CreateAnimation("effect_bloodanimation_left.bmp", "BloodAnimation_left", 0, 5, 0.06, true);

	NewBloodAnimation->CreateAnimation("effect_bloodanimation2_right.bmp", "BloodAnimation2_right", 0, 9, 0.06, true);
	NewBloodAnimation->CreateAnimation("effect_bloodanimation2_left.bmp", "BloodAnimation2_left", 0, 9, 0.06, true);

	if (g_AttackDir.x >= 0.f)
	{
		NewBloodAnimation->SetPivot({ 40.f, -50.f });
		NewBloodAnimation->ChangeAnimation("BloodAnimation_right");
	}
	else if (g_AttackDir.x < 0.f)
	{
		NewBloodAnimation->SetPivot({ -40.f, -50.f });
		NewBloodAnimation->ChangeAnimation("BloodAnimation_left");
	}
	NewBloodAnimation->SetPivotType(RenderPivot::BOT);

	SetPosition(GetPosition() + float4{ 0,-2 });
	StateTime[static_cast<int>(ActorState::HurtGround)] = 0.f;
	AnimationName_ = "Grunt_HurtFly_";
	ActorAnimationRenderer->ChangeAnimation(AnimationName_ + ChangeDirText);
	SetSpeed(0.f);

	MoveDir = g_AttackDir * 800;	// �¾����� �˹�

}

void Grunt::IdleUpdate()
{
	// ���� �ൿ
	StateTime[static_cast<int>(ActorState::Idle)] += GameEngineTime::GetDeltaTime();
	if (StateTime[static_cast<int>(ActorState::Idle)] >= 2 && bPatrol_ == true)
	{
		ChangeState(ActorState::Turn);
		return;
	}

	// �÷��̾� ���ݿ� ������ ���
	if (true == IsHit())
	{
		ChangeState(ActorState::HurtFly);
		return;
	}
}

void Grunt::WalkUpdate()
{
	StateTime[static_cast<int>(ActorState::Walk)] += GameEngineTime::GetDeltaTime();

	if (StateTime[static_cast<int>(ActorState::Walk)] >= 5)
	{
		ChangeState(ActorState::Idle);
		return;
	}

	// �÷��̾� ���ݿ� ������ ���
	if (true == IsHit())
	{
		ChangeState(ActorState::HurtFly);
		return;
	}

	// �¿� �̵�
	if (CurDir_ == ActorDir::Right)
	{
		MoveDir = float4::RIGHT;
	}

	else if (CurDir_ == ActorDir::Left)
	{
		MoveDir = float4::LEFT;
	}

	MapCollisionCheckMoveGround();

}

void Grunt::TurnUpdate()
{
	if (true == ActorAnimationRenderer->IsEndAnimation())
	{
		ChangeState(ActorState::Walk);
		if (CurDir_ == ActorDir::Right)
		{
			CurDir_ = ActorDir::Left;
		}
		else if (CurDir_ == ActorDir::Left)
		{
			CurDir_ = ActorDir::Right;
		}
		return;
	}

	// �÷��̾� ���ݿ� ������ ���
	if (true == IsHit())
	{
		ChangeState(ActorState::HurtFly);
		return;
	}
}


void Grunt::RunUpdate()
{
	// �÷��̾� ���ݿ� ������ ���
	if (true == IsHit())
	{
		ChangeState(ActorState::HurtFly);
		return;
	}
}

void Grunt::AttackUpdate()
{
	// �÷��̾� ���ݿ� ������ ���
	if (true == IsHit())
	{
		ChangeState(ActorState::HurtFly);
		return;
	}
}

void Grunt::HurtGroundUpdate()
{
	// �Ǻ����� ������ ������ Death
	if (true == NewBloodAnimation->IsEndAnimation())
	{
		NewBloodAnimation->Off();
	}

	// �������� ����� ������, �浹ü Death
	if (true == ActorAnimationRenderer->IsEndAnimation())
	{
		ActorCollision_->Death();
	}

	MoveDir += -MoveDir * GameEngineTime::GetDeltaTime() * 3.4;

	if (1.f >= MoveDir.Len2D())
	{
		MoveDir = float4::ZERO;
	}

	MapCollisionCheckMoveGroundDie();

}

void Grunt::HurtFlyUpdate()
{

	// ���߿� �� �����ϰ�� �߷¿����� �޴´�.
	// �߷� ���ӵ��� ���� ���� �ӵ�.
	{
		// �������ǿ��� ���ϴ� ��ġ�� �ȼ��� ������ ���� �� �ִ�.
		int RColor = MapColImage_->GetImagePixel(GetPosition() + float4{ 0,1 });
		Gravity_ += AccGravity_ * GameEngineTime::GetDeltaTime();
		if (MoveDir.y > 0.f)	// ����������
		{
			if (RGB(0, 0, 0) == RColor || RGB(255, 0, 0) == RColor)	// ���� ���� ��� 
			{
				ChangeState(ActorState::HurtGround);
				return;
			}
		}
		MoveDir += float4::DOWN * Gravity_ * GameEngineTime::GetDeltaTime();
	}

	MapCollisionCheckMoveAirDie();

}
