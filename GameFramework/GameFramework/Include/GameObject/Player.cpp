
#include "Player.h"
#include "../Scene/Scene.h"
#include "Bullet.h"
#include "../Input.h"
#include "../GameManager.h"
#include "../Scene/Camera.h"
#include "../Collision/ColliderBox.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Widget/CharacterHUD.h"
#include "../Widget/WidgetComponent.h"
#include "../Widget/Text.h"
#include "../Widget/ProgressBar.h"
#include "../Resource/ResourceManager.h"

CPlayer::CPlayer()
{
	SetTypeID<CPlayer>();
}

CPlayer::CPlayer(const CPlayer& Obj)	:
	CCharacter(Obj)
{
}

CPlayer::~CPlayer()
{
}

bool CPlayer::Init()
{
	CGameObject::Init();

	m_MoveSpeed = 400.f;

	SetPos(100.f, 100.f);
	SetSize(85.f, 75.f);
	SetPivot(0.5f, 1.f);

	//SetTexture("Player", TEXT("Player/Right/alert.bmp"));
	//SetColorKey(255, 0, 255);

	CreateAnimation();

	// 애니메이션 추가
	CreateAnimationSequence();


	//SetEndFunction<CPlayer>("PlayerRightAttack", this, &CPlayer::AttackEnd);
	//SetEndFunction<CPlayer>("PlayerLeftAttack", this, &CPlayer::AttackEnd);

	//AddNotify<CPlayer>("PlayerRightAttack", 2, this, &CPlayer::Attack);
	//AddNotify<CPlayer>("PlayerLeftAttack", 2, this, &CPlayer::Attack);


	// 오른쪽 보고 있음.
	m_PlayerDir = (int)PlayerDir::Right;

	// 공격중이 아닐때.
	m_Attack = false;


	// 충돌체 추가
	CColliderBox* Box = AddCollider<CColliderBox>("Body");

	Box->SetExtent(72.f, 70.f);
	Box->SetOffset(0.f, 0.f);
	Box->SetCollisionProfile("Player");

	Box->SetCollisionBeginFunction<CPlayer>(this, &CPlayer::CollisionBegin);
	Box->SetCollisionEndFunction<CPlayer>(this, &CPlayer::CollisionEnd);


	// 키 입력 함수 포인터
	CInput::GetInst()->AddBindFunction<CPlayer>("MoveUp", 
		Input_Type::Push, this, &CPlayer::MoveUp);

	CInput::GetInst()->AddBindFunction<CPlayer>("MoveDown",
		Input_Type::Push, this, &CPlayer::MoveDown);

	CInput::GetInst()->AddBindFunction<CPlayer>("MoveRight",
		Input_Type::Push, this, &CPlayer::MoveRight);

	CInput::GetInst()->AddBindFunction<CPlayer>("MoveLeft",
		Input_Type::Push, this, &CPlayer::MoveLeft);

	CInput::GetInst()->AddBindFunction<CPlayer>("LButton",
		Input_Type::Down, this, &CPlayer::Fire);

	CInput::GetInst()->AddBindFunction<CPlayer>("Space",
		Input_Type::Down, this, &CPlayer::JumpKey);


	//m_HP = 100;
	//m_HPMax = 100;


	//m_HPBar = CreateWidgetComponent<CProgressBar>("HPBar");

	//m_HPBar->GetWidget<CProgressBar>()->SetTexture(EProgressBar_Texture_Type::Bar,
	//	"HPBar", TEXT("CharacterHPBar.bmp"));
	//m_HPBar->GetWidget<CProgressBar>()->SetSize(50.f, 10.f);
	//m_HPBar->SetPos(-25.f, -90.f);

	//m_NameBar = CreateWidgetComponent<CText>("NameBar");

	//m_NameBar->GetWidget<CText>()->SetText(TEXT("Player"));
	//m_NameBar->GetWidget<CText>()->EnableShadow(true);
	//m_NameBar->GetWidget<CText>()->SetTextColor(255, 255, 255);
	//m_NameBar->GetWidget<CText>()->SetShadowOffset(2.f, 2.f);

	//m_NameBar->SetPos(-25.f, -110.f);

	//SetPhysicsSimulate(true);
	//SetJumpVelocity(60.f);
	//SetSideWallCheck(true);

	return true;
}

void CPlayer::Update(float DeltaTime)
{
	CCharacter::Update(DeltaTime);

	DeltaTime *= m_TimeScale;

	StateUpdate();

}

void CPlayer::PostUpdate(float DeltaTime)
{
	CCharacter::PostUpdate(DeltaTime);

	//if (m_PlayerDir == 1)
	//{
	//	// 0일 경우라면 오른쪽으로 이동중 멈췄다는 것이다.
	//	if (m_Move.x < 0.f)
	//		m_PlayerDir = -1;
	//}

	//else
	//{
	//	if (m_Move.x > 0.f)
	//		m_PlayerDir = 1;
	//}

	int	AnimDirIndex = 0;

	if (m_PlayerDir == -1)
		AnimDirIndex = 1;

	//if (m_Move.x != 0.f || m_Move.y != 0.f)
	//{
	//	// 이동을 할 경우 공격중이더라도 공격을 취소한다.
	//	m_Attack = false;
	//	ChangeAnimation(m_vecSequenceKey[AnimDirIndex][1]);
	//}

	//else if (!m_Attack)
	//	ChangeAnimation(m_vecSequenceKey[AnimDirIndex][0]);
}

void CPlayer::Render(HDC hDC, float DeltaTime)
{
	CCharacter::Render(hDC, DeltaTime);

	Vector2	Pos = m_Pos - m_Scene->GetCamera()->GetPos();

}

float CPlayer::InflictDamage(float Damage)
{
	return 0.0f;
}

void CPlayer::CreateAnimationSequence()
{
	// Idle_Right
	{
		std::vector<std::wstring>	vecFileName;

		for (int i = 0; i <= 10; ++i)
		{
			TCHAR	FileName[MAX_PATH] = {};
			// %d에 i의 값이 대입되어 문자열이 만들어지게 된다.
			wsprintf(FileName, TEXT("Player/spr_idle_right/%d.bmp"), i);
			vecFileName.push_back(FileName);
		}

		CResourceManager::GetInst()->CreateAnimationSequence("spr_idle_right",
			"spr_idle_right", vecFileName, TEXTURE_PATH);

		for (int i = 0; i < 11; ++i)
		{
			CResourceManager::GetInst()->AddAnimationFrame("spr_idle_right", 0.f, 0.f,
				36.f, 35.f);
		}

		CResourceManager::GetInst()->SetColorKey("spr_idle_right", 255, 255, 255);

		AddAnimation("spr_idle_right", true);
	}

	// Idle_Left
	{
		std::vector<std::wstring>	vecFileName;

		for (int i = 0; i <= 10; ++i)
		{
			TCHAR	FileName[MAX_PATH] = {};
			// %d에 i의 값이 대입되어 문자열이 만들어지게 된다.
			wsprintf(FileName, TEXT("Player/spr_idle_left/%d.bmp"), i);
			vecFileName.push_back(FileName);
		}

		CResourceManager::GetInst()->CreateAnimationSequence("spr_idle_left",
			"spr_idle_left", vecFileName, TEXTURE_PATH);

		for (int i = 0; i < 11; ++i)
		{
			CResourceManager::GetInst()->AddAnimationFrame("spr_idle_left", 0.f, 0.f,
				36.f, 35.f);
		}

		CResourceManager::GetInst()->SetColorKey("spr_idle_left", 255, 255, 255);

		AddAnimation("spr_idle_left", true);
	}

}

void CPlayer::StateChange(ActorState State)
{
	if (m_eCurState != State)	// 상태가 바뀔때 한번만 실행시켜준다.
	{
		switch (State)
		{
		case ActorState::Idle:
			IdleStart();
			break;
		case ActorState::Run:
			RunStart();
			break;
		case ActorState::Attack:
			AttackStart();
			break;
		}

		m_eCurState = State;
	}
}

void CPlayer::StateUpdate()
{
	switch (m_eCurState)
	{
	case ActorState::Idle:
		IdleUpdate();
		break;
	case ActorState::Run:
		RunUpdate();
		break;
	case ActorState::Attack:
		AttackUpdate();
		break;
	}
}

void CPlayer::MoveUp()
{
	MoveDir(Vector2(0.f, -1.f));
}

void CPlayer::MoveDown()
{
	MoveDir(Vector2(0.f, 1.f));
}

void CPlayer::MoveRight()
{
	MoveDir(Vector2(1.f, 0.f));
	m_PlayerDir = (int)PlayerDir::Right;
}

void CPlayer::MoveLeft()
{
	MoveDir(Vector2(-1.f, 0.f));
	m_PlayerDir = (int)PlayerDir::Left;
}

void CPlayer::Fire()
{

}

void CPlayer::JumpKey()
{
	Jump();
}

void CPlayer::AttackEnd()
{
	m_Attack = false;
}

void CPlayer::Attack()
{
	
}

void CPlayer::CollisionBegin(CCollider* Src, CCollider* Dest)
{
	//m_Scene->GetSceneResource()->SoundPlay("Gabung");

	//m_HP -= 10;

	//m_Scene->FindWidget<CCharacterHUD>("CharacterHUD")->SetHP(m_HP / (float)m_HPMax);
	//m_HPBar->GetWidget<CProgressBar>()->SetValue(m_HP / (float)m_HPMax);
}

void CPlayer::CollisionEnd(CCollider* Src, CCollider* Dest)
{
}

void CPlayer::IdleUpdate()
{
}

void CPlayer::RunUpdate()
{
}

void CPlayer::AttackUpdate()
{
}

void CPlayer::IdleStart()
{
}

void CPlayer::RunStart()
{
}

void CPlayer::AttackStart()
{
}
