
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
#include "../Resource/Texture/Texture.h"

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

	SetPos(200.f, 200.f);
	SetSize(36.f, 70.f);
	SetPivot(0.5f, 1.f);
	SetRenderScale(2);

	CreateAnimation();

	// 애니메이션 추가
	CreateAnimationSequence();

	//SetEndFunction<CPlayer>("PlayerRightAttack", this, &CPlayer::AttackEnd);
	//SetEndFunction<CPlayer>("PlayerLeftAttack", this, &CPlayer::AttackEnd);

	// 노티파이 추가
	AddNotify<CPlayer>("spr_run_left", 3, this, &CPlayer::RunningSound);
	AddNotify<CPlayer>("spr_run_left", 8, this, &CPlayer::RunningSound);
	AddNotify<CPlayer>("spr_run_right", 3, this, &CPlayer::RunningSound);
	AddNotify<CPlayer>("spr_run_right", 8, this, &CPlayer::RunningSound);

	// 사운드 로드
	m_Scene->GetSceneResource()->LoadSound("Effect", "sound_player_running_2", false, "sound_player_running_2.wav");

	// 방향
	m_CurDir = PlayerDir::Right;

	// 충돌체 추가
	CColliderBox* Box = AddCollider<CColliderBox>("Body");

	Box->SetExtent(36.f, 70.f);
	Box->SetOffset(0.f, -35.f);
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


	// 충돌맵 세팅
	SetMapTexture("room_factory_2_ColMap", TEXT("room_factory_2_ColMap.bmp"), "MapPath");

	ChangeAnimation("spr_idle_right");

	m_AnimationName = "Idle_";
	m_CurState = PlayerState::Idle;
	m_CurDir = PlayerDir::Right;


	return true;
}

void CPlayer::Update(float DeltaTime)
{
	CCharacter::Update(DeltaTime);
	DeltaTime *= m_TimeScale;

	// 공통 함수
	DirAnimationCheck();
	StateUpdate();


	int COLOR = m_MapColTexture->GetImagePixel((int)m_Pos.x, (int)m_Pos.y);
	if (RGB(0,0,0) == COLOR)
		MessageBoxA(nullptr, "충돌맵과 겹쳤음.", "ERROR", MB_OK);

}

void CPlayer::PostUpdate(float DeltaTime)
{
	CCharacter::PostUpdate(DeltaTime);


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

		for (int i = 0; i <= 10; ++i)
		{
			CResourceManager::GetInst()->AddAnimationFrame("spr_idle_left", 0.f, 0.f,
				36.f, 35.f);
		}

		CResourceManager::GetInst()->SetColorKey("spr_idle_left", 255, 255, 255);

		AddAnimation("spr_idle_left", true, 1.1f);
	}

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

		for (int i = 0; i <= 10; ++i)
		{
			CResourceManager::GetInst()->AddAnimationFrame("spr_idle_right", 0.f, 0.f,
				36.f, 35.f);
		}

		CResourceManager::GetInst()->SetColorKey("spr_idle_right", 255, 255, 255);

		AddAnimation("spr_idle_right", true, 1.1f);
	}

	// Idle_to_Run_Left
	{
		std::vector<std::wstring>	vecFileName;

		for (int i = 0; i <= 3; ++i)
		{
			TCHAR	FileName[MAX_PATH] = {};
			// %d에 i의 값이 대입되어 문자열이 만들어지게 된다.
			wsprintf(FileName, TEXT("Player/spr_idle_to_run_left/%d.bmp"), i);
			vecFileName.push_back(FileName);
		}

		CResourceManager::GetInst()->CreateAnimationSequence("spr_idle_to_run_left",
			"spr_idle_to_run_left", vecFileName, TEXTURE_PATH);

		for (int i = 0; i <= 3; ++i)
		{
			CResourceManager::GetInst()->AddAnimationFrame("spr_idle_to_run_left", 0.f, 0.f,
				44.f, 32.f);
		}

		CResourceManager::GetInst()->SetColorKey("spr_idle_to_run_left", 255, 255, 255);

		AddAnimation("spr_idle_to_run_left", true, 0.16f);
	}

	// Idle_to_Run_Right
	{
		std::vector<std::wstring>	vecFileName;

		for (int i = 0; i <= 3; ++i)
		{
			TCHAR	FileName[MAX_PATH] = {};
			// %d에 i의 값이 대입되어 문자열이 만들어지게 된다.
			wsprintf(FileName, TEXT("Player/spr_idle_to_run_right/%d.bmp"), i);
			vecFileName.push_back(FileName);
		}

		CResourceManager::GetInst()->CreateAnimationSequence("spr_idle_to_run_right",
			"spr_idle_to_run_right", vecFileName, TEXTURE_PATH);

		for (int i = 0; i <= 3; ++i)
		{
			CResourceManager::GetInst()->AddAnimationFrame("spr_idle_to_run_right", 0.f, 0.f,
				44.f, 32.f);
		}

		CResourceManager::GetInst()->SetColorKey("spr_idle_to_run_right", 255, 255, 255);

		AddAnimation("spr_idle_to_run_right", true, 0.16f);
	}

	// Run_Left
	{
		std::vector<std::wstring>	vecFileName;

		for (int i = 0; i <= 9; ++i)
		{
			TCHAR	FileName[MAX_PATH] = {};
			// %d에 i의 값이 대입되어 문자열이 만들어지게 된다.
			wsprintf(FileName, TEXT("Player/spr_run_left/%d.bmp"), i);
			vecFileName.push_back(FileName);
		}

		CResourceManager::GetInst()->CreateAnimationSequence("spr_run_left",
			"spr_run_left", vecFileName, TEXTURE_PATH);

		for (int i = 0; i <= 9; ++i)
		{
			CResourceManager::GetInst()->AddAnimationFrame("spr_run_left", 0.f, 0.f,
				44.f, 32.f);
		}

		CResourceManager::GetInst()->SetColorKey("spr_run_left", 255, 255, 255);

		AddAnimation("spr_run_left", true, 0.7f);
	}

	// Run_Right
	{
		std::vector<std::wstring>	vecFileName;

		for (int i = 0; i <= 9; ++i)
		{
			TCHAR	FileName[MAX_PATH] = {};
			// %d에 i의 값이 대입되어 문자열이 만들어지게 된다.
			wsprintf(FileName, TEXT("Player/spr_run_right/%d.bmp"), i);
			vecFileName.push_back(FileName);
		}

		CResourceManager::GetInst()->CreateAnimationSequence("spr_run_right",
			"spr_run_right", vecFileName, TEXTURE_PATH);

		for (int i = 0; i <= 9; ++i)
		{
			CResourceManager::GetInst()->AddAnimationFrame("spr_run_right", 0.f, 0.f,
				44.f, 32.f);
		}

		CResourceManager::GetInst()->SetColorKey("spr_run_right", 255, 255, 255);

		AddAnimation("spr_run_right", true, 0.7f);
	}




}

void CPlayer::DirAnimationCheck()
{
	PlayerDir CheckDir = m_CurDir;

	if (m_CurDir == PlayerDir::Right)
	{
		m_ChangeDirText = "right";
	}
	else if (m_CurDir == PlayerDir::Left)
	{
		m_ChangeDirText = "left";
	}

	if (m_CurState != PlayerState::Attack && m_CurState != PlayerState::Dodge)
	{

		if (true == CInput::GetInst()->IsPress('D'))
		{
			CheckDir = PlayerDir::Right;
			m_ChangeDirText = "right";
		}

		else if (true == CInput::GetInst()->IsPress('A'))
		{
			CheckDir = PlayerDir::Left;
			m_ChangeDirText = "left";
		}

		if (CheckDir != m_CurDir)
		{
			ChangeAnimation(m_AnimationName + m_ChangeDirText);
			m_CurDir = CheckDir;
		}
	}

}

void CPlayer::StateChange(PlayerState State)
{
	if (m_CurState != State)	// 상태가 바뀔때 한번만 실행시켜준다.
	{
		switch (State)
		{
		case PlayerState::Idle:
			IdleStart();
			break;
		case PlayerState::IdleToRun:
			IdleToRunStart();
			break;
		case PlayerState::Run:
			RunStart();
			break;
		case PlayerState::RunToIdle:
			RunToIdleStart();
			break;
		case PlayerState::Jump:
			JumpStart();
			break;
		case PlayerState::Landing:
			LandingStart();
			break;
		case PlayerState::Attack:
			AttackStart();
			break;
		case PlayerState::Fall:
			FallStart();
			break;
		case PlayerState::Dodge:
			DodgeStart();
			break;
		case PlayerState::PlaySong:
			PlaySongStart();
			break;
		}
	m_CurState = State;
	}
}

void CPlayer::StateUpdate()
{
	switch (m_CurState)
	{
	case PlayerState::Idle:
		IdleUpdate();
		break;
	case PlayerState::IdleToRun:
		IdleToRunUpdate();
		break;
	case PlayerState::Run:
		RunUpdate();
		break;
	case PlayerState::RunToIdle:
		RunToIdleUpdate();
		break;
	case PlayerState::Jump:
		JumpUpdate();
		break;
	case PlayerState::Landing:
		LandingUpdate();
		break;
	case PlayerState::Attack:
		AttackUpdate();
		break;
	case PlayerState::Fall:
		FallUpdate();
		break;
	case PlayerState::Dodge:
		DodgeUpdate();
		break;
	case PlayerState::PlaySong:
		PlaySongUpdate();
		break;
	}
}

void CPlayer::MoveUp()
{
	Vector2 NextPos = m_Pos + (Vector2{ 0.f, -1.f } * m_MoveSpeed * DELTA_TIME * m_TimeScale);

	int COLOR = m_MapColTexture->GetImagePixel((int)NextPos.x, (int)NextPos.y);

	if (COLOR != RGB(0,0,0))
	MoveDir(Vector2(0.f, -1.f));
}

void CPlayer::MoveDown()
{
	Vector2 NextPos = m_Pos + (Vector2{ 0.f, 1.f } *m_MoveSpeed * DELTA_TIME * m_TimeScale);

	int COLOR = m_MapColTexture->GetImagePixel((int)NextPos.x, (int)NextPos.y);

	if (COLOR != RGB(0, 0, 0))
	MoveDir(Vector2(0.f, 1.f));
}

void CPlayer::MoveRight()
{
	Vector2 NextPos = m_Pos + (Vector2{ 1.f, 0.f } *m_MoveSpeed * DELTA_TIME * m_TimeScale);

	int COLOR = m_MapColTexture->GetImagePixel((int)NextPos.x, (int)NextPos.y);

	if (COLOR != RGB(0, 0, 0))
	{
		MoveDir(Vector2(1.f, 0.f));
	}
}

void CPlayer::MoveLeft()
{
	Vector2 NextPos = m_Pos + (Vector2{ -1.f, 0.f } *m_MoveSpeed * DELTA_TIME * m_TimeScale);

	int COLOR = m_MapColTexture->GetImagePixel((int)NextPos.x, (int)NextPos.y);

	if (COLOR != RGB(0, 0, 0))
	{
		MoveDir(Vector2(-1.f, 0.f));
	}
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
}

bool CPlayer::IsMoveKey()
{
	// 아무키도 눌리지 않았다면 false, 눌렀다면 true 리턴
	if (false == CInput::GetInst()->IsPress('A') &&
		false == CInput::GetInst()->IsPress('D'))
	{
		return false;
	}
	return true;
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

	//## Update
void CPlayer::IdleUpdate()
{
	if (true == IsMoveKey())
	{
		StateChange(PlayerState::IdleToRun);
		return;
	}
}

void CPlayer::IdleToRunUpdate()
{
	// 애니메이션 종료후 Run 모션으로
	if (true == m_Animation->IsEndAnimation())
	{
		StateChange(PlayerState::Run);
		return;
	}

	// 이동키를 안눌렀다면 Idle 상태로
	if (false == IsMoveKey())				// 이동키를 안눌렀다면
	{
		StateChange(PlayerState::Idle);
		return;
	}


}

void CPlayer::RunUpdate()
{
}

void CPlayer::RunToIdleUpdate()
{
}

void CPlayer::JumpUpdate()
{
}


void CPlayer::AttackUpdate()
{
}

void CPlayer::LandingUpdate()
{
}

void CPlayer::FallUpdate()
{
}

void CPlayer::DodgeUpdate()
{
}

void CPlayer::PlaySongUpdate()
{
}


	//## Start
void CPlayer::IdleStart()
{
	// 애니메이션 체인지
	m_AnimationName = "spr_idle_";
	ChangeAnimation(m_AnimationName + m_ChangeDirText);
	SetSpeed(0.f);

}

void CPlayer::IdleToRunStart()
{
	m_AnimationName = "spr_idle_to_run_";
	ChangeAnimation(m_AnimationName + m_ChangeDirText);
	SetSpeed(200.f);

}


void CPlayer::RunStart()
{
	m_AnimationName = "spr_run_";
	ChangeAnimation(m_AnimationName + m_ChangeDirText);
	SetSpeed(450.f);


}

void CPlayer::RunToIdleStart()
{
}

void CPlayer::JumpStart()
{
}

void CPlayer::LandingStart()
{
}

void CPlayer::AttackStart()
{
}

void CPlayer::FallStart()
{
}

void CPlayer::DodgeStart()
{
}

void CPlayer::PlaySongStart()
{
}


void CPlayer::RunningSound()
{
	m_Scene->GetSceneResource()->SoundPlay("sound_player_running_2");

}