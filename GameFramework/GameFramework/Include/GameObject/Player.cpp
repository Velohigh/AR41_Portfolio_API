
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
#include "Effect_DustCloud.h"
#include "Effect_JumpCloud.h"
#include "Effect_LandCloud.h"
#include "Effect_Slash.h"
#include <random>
#include "../Scene/Stage_1.h"

Vector2 g_AttackDir = Vector2{ 0.f , 0.f };
Vector2 g_EnemyAttackDir = Vector2{ 0.f, 0.f };

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

	// 애니메이션 종료시 호출함수
	//SetEndFunction<CPlayer>("PlayerRightAttack", this, &CPlayer::AttackEnd);
	//SetEndFunction<CPlayer>("PlayerLeftAttack", this, &CPlayer::AttackEnd);

	// Notify 추가
	AddNotify<CPlayer>("spr_run_left", 3, this, &CPlayer::RunningSound);
	AddNotify<CPlayer>("spr_run_left", 8, this, &CPlayer::RunningSound);
	AddNotify<CPlayer>("spr_run_right", 3, this, &CPlayer::RunningSound);
	AddNotify<CPlayer>("spr_run_right", 8, this, &CPlayer::RunningSound);
	AddNotify<CPlayer>("spr_player_playsong", 4, this, &CPlayer::HeadphoneSound);
	AddNotify<CPlayer>("spr_player_playsong", 13, this, &CPlayer::CarsetteRewindSound);
	AddNotify<CPlayer>("spr_player_playsong", 27, this, &CPlayer::CarsettePlaySound);


	// 사운드 로드
	m_Scene->GetSceneResource()->LoadSound("Effect", "sound_player_running_2", false, "sound_player_running_2.wav");
	m_Scene->GetSceneResource()->LoadSound("Sound_Jump", "sound_player_jump", false, "sound_player_jump.wav");
	m_Scene->GetSceneResource()->SetVolume("Sound_Jump", 65);
	m_Scene->GetSceneResource()->LoadSound("Effect", "sound_player_land", false, "sound_player_land.wav");
	m_Scene->GetSceneResource()->LoadSound("Sound_Slash", "sound_player_slash_1", false, "sound_player_slash_1.wav");
	m_Scene->GetSceneResource()->LoadSound("Sound_Slash", "sound_player_slash_2", false, "sound_player_slash_2.wav");
	m_Scene->GetSceneResource()->LoadSound("Sound_Slash", "sound_player_slash_3", false, "sound_player_slash_3.wav");
	m_Scene->GetSceneResource()->SetVolume("Sound_Slash", 90);
	m_Scene->GetSceneResource()->LoadSound("Sound_Roll", "sound_player_roll", false, "sound_player_roll.wav");
	m_Scene->GetSceneResource()->SetVolume("Sound_Roll", 40);
	m_Scene->GetSceneResource()->LoadSound("Sound_Roll_Real", "sound_player_roll_real", false, "sound_player_roll_real.wav");
	m_Scene->GetSceneResource()->SetVolume("sound_player_roll_real", 74);
	m_Scene->GetSceneResource()->LoadSound("Effect", "sound_playerheadphones", false, "sound_playerheadphones.wav");
	m_Scene->GetSceneResource()->LoadSound("Effect", "sound_playercasette_rewind", false, "sound_playercasette_rewind.wav");
	m_Scene->GetSceneResource()->LoadSound("Effect", "sound_playercasette_play", false, "sound_playercasette_play.wav");
	m_Scene->GetSceneResource()->LoadSound("Sound_RunStart", "sound_player_prerun", false, "sound_player_prerun.wav");
	m_Scene->GetSceneResource()->SetVolume("Sound_RunStart", 35);
	m_Scene->GetSceneResource()->LoadSound("Sound_Slomo_In", "slow_in", false, "slow_in.mp3");
	m_Scene->GetSceneResource()->SetVolume("Sound_Slomo_In", 100);

	m_Scene->GetSceneResource()->LoadSound("Effect", "slow_out", false, "slow_out.mp3");


	// 방향
	m_CurDir = PlayerDir::Right;

	// 충돌체 추가
	CColliderBox* Box = AddCollider<CColliderBox>("Body");
	Box->SetExtent(36.f, 70.f);
	Box->SetOffset(0.f, -35.f);
	Box->SetCollisionProfile("Player");

	CColliderBox* HitBox = AddCollider<CColliderBox>("HitBox");
	HitBox->SetExtent(36.f, 70.f);
	HitBox->SetOffset(0.f, -35.f);
	HitBox->SetCollisionProfile("PlayerHitBox");


	HitBox->SetCollisionBeginFunction<CPlayer>(this, &CPlayer::HitBoxCollisionBegin);
	HitBox->SetCollisionEndFunction<CPlayer>(this, &CPlayer::HitBoxCollisionEnd);


	// 키 입력 함수 포인터
	CInput::GetInst()->AddBindFunction<CPlayer>("Q", 
		Input_Type::Push, this, &CPlayer::SlowModeKeyPush);

	CInput::GetInst()->AddBindFunction<CPlayer>("Q",
		Input_Type::Up, this, &CPlayer::SlowModeKeyUp);

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

	//ChangeAnimation("spr_idle_right");
	ChangeAnimation("spr_player_playsong");

	// 초기 세팅
	//m_AnimationName = "spr_idle_";
	m_CurState = PlayerState::Idle;
	m_CurDir = PlayerDir::Right;


	return true;
}

void CPlayer::Update(float DeltaTime)
{
	CCharacter::Update(DeltaTime);
	DeltaTime *= m_TimeScale;
	m_GameTime += DeltaTime;

	// 공통 함수
	DirAnimationCheck();
	StateUpdate();

	m_Scene->FindWidgetWindow<CCharacterHUD>("CharacterHUD")->SetTimeBar((100.f - m_GameTime)/100.f);

	// if( 시간이 100초 지나면 스타트 씬으로)

	m_Scene->FindWidgetWindow<CCharacterHUD>("CharacterHUD")->SetBatteryBar( m_Battery / 11.f);

	if (m_Battery < 11)
	{
		m_BatteryRechargeTime += DELTA_TIME;
		if (m_BatteryRechargeTime >= 1.f)
		{
			m_BatteryRechargeTime -= 1.f;
			m_Battery += 1;
		}
	}


}

void CPlayer::PostUpdate(float DeltaTime)
{
	CCharacter::PostUpdate(DeltaTime);
}

void CPlayer::Render(HDC hDC, float DeltaTime)
{
	CCharacter::Render(hDC, DeltaTime);

	Vector2	Pos = m_Pos - m_Scene->GetCamera()->GetPos();

	TCHAR StateBuff[64] = L"";
	TCHAR PosBuff[64] = L"";

	swprintf_s(PosBuff, L"X : %d, Y : %d", (int)m_Pos.x, (int)m_Pos.y);
	TextOut(hDC, (int)Pos.x, (int)Pos.y - 100, PosBuff, lstrlen(PosBuff));

}

float CPlayer::InflictDamage(float Damage)
{
	return 0.0f;
}

void CPlayer::CreateAnimationSequence()
{
	AddAnimation("spr_idle_left", true, 1.1f);
	AddAnimation("spr_idle_right", true, 1.1f);
	AddAnimation("spr_idle_to_run_left", true, 0.16f);
	AddAnimation("spr_idle_to_run_right", true, 0.16f);
	AddAnimation("spr_run_left", true, 0.7f);
	AddAnimation("spr_run_right", true, 0.7f);
	AddAnimation("spr_run_to_idle_left", true, 0.35f);
	AddAnimation("spr_run_to_idle_right", true, 0.35f);
	AddAnimation("spr_jump_left", true, 0.28f);
	AddAnimation("spr_jump_right", true, 0.28f);
	AddAnimation("spr_fall_left", true, 0.28f);
	AddAnimation("spr_fall_right", true, 0.28f);
	AddAnimation("spr_attack_left", true, 0.196f);
	AddAnimation("spr_attack_right", true, 0.196f);
	AddAnimation("spr_landing_left", true, 0.3f);
	AddAnimation("spr_landing_right", true, 0.3f);
	AddAnimation("spr_roll_left", true, 0.315f);
	AddAnimation("spr_roll_right", true, 0.315f);
	AddAnimation("spr_player_playsong", true, 3.5f);
	AddAnimation("spr_hurtfly_begin_left", true, 0.14f);
	AddAnimation("spr_hurtfly_begin_right", true, 0.28f);
	AddAnimation("spr_hurtfly_loop_left", true, 0.28f);
	AddAnimation("spr_hurtfly_loop_right", true, 0.28f);
	AddAnimation("spr_hurtground_left", false, 0.55f);
	AddAnimation("spr_hurtground_right", false, 0.55f);

	// ## Effect
	AddAnimation("spr_dustcloud", true, 0.42f);
	AddAnimation("spr_jumpcloud", true, 0.24f);
	AddAnimation("spr_landcloud", true, 0.42f);
	AddAnimation("spr_slash", true, 0.196f);
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

	if (m_CurState != PlayerState::Attack && m_CurState != PlayerState::Dodge &&
		m_CurState != PlayerState::Dead && m_CurState != PlayerState::HurtFlyLoop &&
		m_CurState != PlayerState::HurtGround)
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
		case PlayerState::HurtFlyLoop:
			HurtFlyLoopStart();
			break;
		case PlayerState::HurtGround:
			HurtGroundStart();
			break;
		case PlayerState::WallGrab:
			WallGrabStart();
			break;
		case PlayerState::Flip:
			FlipStart();
			break;
		case PlayerState::Dead:
			DeadStart();
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
	case PlayerState::HurtFlyLoop:
		HurtFlyLoopUpdate();
		break;
	case PlayerState::HurtGround:
		HurtGroundUpdate();
		break;
	case PlayerState::WallGrab:
		WallGrabUpdate();
		break;
	case PlayerState::Flip:
		FlipUpdate();
		break;
	case PlayerState::Dead:
		DeadUpdate();
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

void CPlayer::HeadphoneSound()
{
	m_Scene->GetSceneResource()->SoundPlay("sound_playerheadphones");
}

void CPlayer::CarsetteRewindSound()
{
	m_Scene->GetSceneResource()->SoundPlay("sound_playercasette_rewind");
}

void CPlayer::CarsettePlaySound()
{
	m_Scene->GetSceneResource()->SoundPlay("sound_playercasette_play");
}

void CPlayer::SlowModeKeyPush()
{
	if (m_Battery <= 0)
		SlowModeKeyUp();

	if (m_Battery >= 1)
	{
		m_BatteryRechargeTime = 0.f;
		m_Scene->SetSlowMap();
		CGameManager::GetInst()->SetTimeScale(0.2f);
		m_BatteryPushTime += DELTA_TIME;

		if (!m_SlowModeSound)
		{
			m_Scene->GetSceneResource()->SoundPlay("slow_in");
			m_SlowModeSound = true;
		}

		if (m_BatteryPushTime >= 0.1f)
		{
			m_BatteryPushTime -= 0.1f;
			m_Battery -= 1;
		}
	}
}

void CPlayer::SlowModeKeyUp()
{
	if (m_BatteryPushTime != 0.f)
	{
		m_BatteryPushTime = 0.f;
		m_Scene->SetNormalMap();
		CGameManager::GetInst()->SetTimeScale(1.f);
		m_Scene->GetSceneResource()->SoundPlay("slow_out");
		m_SlowModeSound = false;
	}

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

void CPlayer::HitBoxCollisionBegin(CCollider* Src, CCollider* Dest)
{

	// 사망상태가 아니고, 구르기판정이 아닐때 히트판정
	if (m_CurState != PlayerState::Dead &&
		m_CurState != PlayerState::HurtFlyLoop &&
		m_CurState != PlayerState::HurtGround &&
		m_CurState != PlayerState::Dodge)
	{
		m_EnemyAttackDir = Dest->GetOwner()->GetMyAttackDir();
		StateChange(PlayerState::HurtFlyLoop);
		return;
	}
}

void CPlayer::HitBoxCollisionEnd(CCollider* Src, CCollider* Dest)
{
}

	//## Update
void CPlayer::IdleUpdate()
{
	// 이동키를 누르면 IdleToRun 상태로
	if (true == IsMoveKey())
	{
		StateChange(PlayerState::IdleToRun);
		return;
	}

	// 아래쪽에 지형이 없다면 Fall상태로
	int color = m_MapColTexture->GetImagePixel(m_Pos + Vector2{ 0,10 });
	int Rcolor = m_MapColTexture->GetImagePixel(m_Pos + Vector2{ 0,1 });
	if (color != RGB(0, 0, 0) && m_CurState != PlayerState::Jump &&
		Rcolor != RGB(255, 0, 0) &&
		Rcolor != RGB(0, 0, 0))
	{
		StateChange(PlayerState::Fall);
		return;
	}

	// 충돌맵 빨간색이면 아래로 이동 가능
	if (Rcolor == RGB(255, 0, 0) &&
		true == CInput::GetInst()->IsDown('S'))
	{
		SetPos(m_Pos + Vector2{ 0, 2 });
	}

	// 점프키를 누르면 Jump 상태로
	if (true == CInput::GetInst()->IsDown(VK_SPACE))		// @@@ 점프 추가.
	{
		StateChange(PlayerState::Jump);
		return;
	}

	// 공격키를 누르면 공격상태로
	if (true == CInput::GetInst()->IsDown(VK_LBUTTON))
	{
		StateChange(PlayerState::Attack);
		return;
	}

	// 회피
	if (true == CInput::GetInst()->IsDown(VK_SHIFT))	// @@@ 회피 추가.
	{
		StateChange(PlayerState::Dodge);
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

	// 점프키를 누르면 Jump 상태로
	if (true == CInput::GetInst()->IsDown(VK_SPACE))		// @@@ 점프 추가.
	{
		StateChange(PlayerState::Jump);
		return;
	}

	// 회피키를 누르면 Dodge 상태로
	if (true == CInput::GetInst()->IsDown(VK_SHIFT))	// @@@ 회피 추가.
	{
		StateChange(PlayerState::Dodge);
		return;
	}

	// 공격
	if (true == CInput::GetInst()->IsDown(VK_LBUTTON))
	{
		StateChange(PlayerState::Attack);
		return;
	}

	// 아래쪽에 지형이 없다면 Fall상태로
	int color[5] = {};
	for (int i = 1; i <= 5; ++i)
	{
	color[i-1] = m_MapColTexture->GetImagePixel(m_Pos + Vector2{0.f,(float)i});
	}
	if (color[0] != RGB(0, 0, 0) && color[0] != RGB(255,0, 0) &&
		color[1] != RGB(0, 0, 0) &&
		color[2] != RGB(0, 0, 0) &&
		color[3] != RGB(0, 0, 0) &&
		color[4] != RGB(0, 0, 0) &&
		m_CurState != PlayerState::Jump)
	{
		StateChange(PlayerState::Fall);
		return;
	}

	// 충돌맵 빨간색이면 아래로 이동 가능
	if (color[0] == RGB(255, 0, 0) &&
		true == CInput::GetInst()->IsDown('S'))
	{
		SetPos(m_Pos + Vector2{ 0, 2 });
	}

	m_MoveDir = Vector2{ 0,0 };

	if (true == CInput::GetInst()->IsPress('A'))
	{
		m_MoveDir = Vector2{ -1.f, 0.f };
	}

	if (true == CInput::GetInst()->IsPress('D'))
	{
		m_MoveDir = Vector2{ 1.f, 0.f };
	}

	MapCollisionCheckMoveGround();



}

void CPlayer::RunUpdate()
{
	m_StateTime[static_cast<int>(PlayerState::Run)] += DELTA_TIME;

	// 이동키를 안누르면 Idle 상태로
	if (false == IsMoveKey())
	{
		StateChange(PlayerState::RunToIdle);
		return;
	}

	// 점프키를 누르면 Jump 상태로
	if (true == CInput::GetInst()->IsDown(VK_SPACE))		// @@@ 점프 추가.
	{
		StateChange(PlayerState::Jump);
		return;
	}

	// 아래쪽에 지형이 없다면 Fall상태로
	int color[5] = {};
	for (int i = 1; i <= 5; ++i)
	{
		color[i - 1] = m_MapColTexture->GetImagePixel(m_Pos + Vector2{ 0.f,(float)i });
	}
	if (color[0] != RGB(0, 0, 0) && color[0] != RGB(255, 0, 0) &&
		color[1] != RGB(0, 0, 0) &&
		color[2] != RGB(0, 0, 0) &&
		color[3] != RGB(0, 0, 0) &&
		color[4] != RGB(0, 0, 0) &&
		m_CurState != PlayerState::Jump)
	{
		StateChange(PlayerState::Fall);
		return;
	}

	// 충돌맵 빨간색이면 아래로 이동 가능
	if (color[0] == RGB(255, 0, 0) &&
		true == CInput::GetInst()->IsDown('S'))
	{
		SetPos(m_Pos + Vector2{ 0, 2 });
	}

	// 회피키를 누르면 Dodge 상태로
	if (true == CInput::GetInst()->IsDown(VK_SHIFT))	// @@@ 회피 추가.
	{
		StateChange(PlayerState::Dodge);
		return;
	}

	// 공격
	if (true == CInput::GetInst()->IsDown(VK_LBUTTON))
	{
		StateChange(PlayerState::Attack);
		return;
	}


	m_MoveDir = Vector2{0.f, 0.f};

	if (true == CInput::GetInst()->IsPress('A'))
	{
		m_MoveDir = Vector2{ -1.f, 0.f };
	}

	if (true == CInput::GetInst()->IsPress('D'))
	{
		m_MoveDir = Vector2{ 1.f, 0.f };
	}

	MapCollisionCheckMoveGround();

}

void CPlayer::RunToIdleUpdate()
{
	// 이동키를 누르면 Run 상태로
	if (true == IsMoveKey())
	{
		StateChange(PlayerState::IdleToRun);
		return;
	}

	// 점프키를 누르면 Jump 상태로
	if (true == CInput::GetInst()->IsDown(VK_SPACE))		// @@@ 점프 추가.
	{
		StateChange(PlayerState::Jump);
		return;
	}

	// 아래쪽에 지형이 없다면 Fall상태로
	int color[5] = {};
	for (int i = 1; i <= 5; ++i)
	{
		color[i - 1] = m_MapColTexture->GetImagePixel(m_Pos + Vector2{ 0.f,(float)i });
	}
	if (color[0] != RGB(0, 0, 0) && color[0] != RGB(255, 0, 0) &&
		color[1] != RGB(0, 0, 0) &&
		color[2] != RGB(0, 0, 0) &&
		color[3] != RGB(0, 0, 0) &&
		color[4] != RGB(0, 0, 0) &&
		m_CurState != PlayerState::Jump)
	{
		StateChange(PlayerState::Fall);
		return;
	}


	// 충돌맵 빨간색이면 아래로 이동 가능
	if (color[0] == RGB(255, 0, 0) &&
		true == CInput::GetInst()->IsDown('S'))
	{
		SetPos(m_Pos + Vector2{ 0, 2 });
	}

	// 회피키를 누르면 Dodge 상태로
	if (true == CInput::GetInst()->IsDown(VK_SHIFT))	// @@@ 회피 추가.
	{
		StateChange(PlayerState::Dodge);
		return;
	}

	// 공격
	if (true == CInput::GetInst()->IsDown(VK_LBUTTON))
	{
		StateChange(PlayerState::Attack);
		return;
	}

	// 이동키를 안누르고, 애니메이션이 끝까지 재생되면 Idle 상태로
	if (false == IsMoveKey() &&
		true == m_Animation->IsEndAnimation())
	{
		StateChange(PlayerState::Idle);
		return;
	}
	else if (false == IsMoveKey() &&
		false == m_Animation->IsEndAnimation())
	{
		Vector2 MoveDir = Vector2{ 0.f,0.f };

		if (m_CurDir == PlayerDir::Left)
		{
			MoveDir = Vector2{ -1.f,0.f };
		}

		else if (m_CurDir == PlayerDir::Right)
		{
			MoveDir = Vector2{ 1.f,0.f };
		}

		MapCollisionCheckMoveGround();
	}

	// 멈추는중에 다시 이동키를 누르면
	if (true == IsMoveKey())
	{
		StateChange(PlayerState::IdleToRun);
		return;
	}
}

void CPlayer::JumpUpdate()
{
	m_StateTime[static_cast<int>(PlayerState::Jump)] += DELTA_TIME;

	if (m_StateTime[static_cast<int>(PlayerState::Jump)] > 0.f &&
		m_StateTime[static_cast<int>(PlayerState::Jump)] <= 0.15f &&
		true == CInput::GetInst()->IsPress(VK_SPACE))
	{
		m_MoveDir += Vector2{ 0.f,-1.f } *DELTA_TIME * m_LongJumpPower;
	}



	m_MoveDir += Vector2{ 0.f, 1.f } * DELTA_TIME * 1500.f;

	Vector2 TempY = { 0.f ,m_MoveDir.y };

	if (30.0f >= TempY.Length())
	{
		m_MoveDir.y = 0;
		//MoveDir.Normal2D();
		StateChange(PlayerState::Fall);
		return;
	}

	// 공격
	if (true == CInput::GetInst()->IsDown(VK_LBUTTON))
	{
		StateChange(PlayerState::Attack);
		return;
	}

	if (true == CInput::GetInst()->IsDown('S'))
	{
		StateChange(PlayerState::Fall);
		return;
	}


	if (true == CInput::GetInst()->IsPress('A'))
	{
		m_MoveDir += Vector2{ -1.f, 0 } * DELTA_TIME * 2000.f;
		Vector2 TempX = { m_MoveDir.x,0.f };

		if (TempX.Length() >= 450.f)
		{
			TempX.Normalize();
			TempX *= 450.f;
			m_MoveDir.x = TempX.x;
		}
	}
	if (true == CInput::GetInst()->IsPress('D'))
	{
		m_MoveDir += Vector2{ 1.f, 0.f } * DELTA_TIME * 2000.f;
		Vector2 TempX = { m_MoveDir.x,0.f };

		if (TempX.Length() >= 450.f)
		{
			TempX.Normalize();
			TempX *= 450.f;
			m_MoveDir.x = TempX.x;
		}
	}

	// 검은 땅에 닿을 경우 
	int Color = m_MapColTexture->GetImagePixel(m_Pos + Vector2{ 0,1 });
	if (RGB(0, 0, 0) == Color)
	{
		m_Gravity = 10.0f;
		m_MoveDir.Normalize();

		//Effect_LandCloud* NewEffect = GetLevel()->CreateActor<Effect_LandCloud>((int)ORDER::UI);
		//NewEffect->SetPosition(GetPosition());

		StateChange(PlayerState::Landing);
		return;
	}


	MapCollisionCheckMoveAir();

}


void CPlayer::AttackUpdate()
{
	
	if (true == m_Animation->IsEndAnimation() &&
		m_PlayerAttackCollision != nullptr)
	{
		m_PlayerAttackCollision->SetActive(false);
		m_PlayerAttackCollision = nullptr;
	}

	// 공격 끝날시 Fall 상태로
	if (true == m_Animation->IsEndAnimation())
	{
		StateChange(PlayerState::Fall);
		return;
	}

	MapCollisionCheckMoveAir();

}

void CPlayer::LandingUpdate()
{
	if (true == m_Animation->IsEndAnimation())
	{
		StateChange(PlayerState::Idle);
		return;
	}

	// 이동키를 누르면 IdleToRun 상태로
	if (true == IsMoveKey())
	{
		StateChange(PlayerState::IdleToRun);
		return;
	}

	// 아래쪽에 지형이 없다면 Fall상태로
	int color[5] = {};
	for (int i = 1; i <= 5; ++i)
	{
		color[i - 1] = m_MapColTexture->GetImagePixel(m_Pos + Vector2{ 0.f,(float)i });
	}
	if (color[0] != RGB(0, 0, 0) && color[0] != RGB(255, 0, 0) &&
		color[1] != RGB(0, 0, 0) &&
		color[2] != RGB(0, 0, 0) &&
		color[3] != RGB(0, 0, 0) &&
		color[4] != RGB(0, 0, 0) &&
		m_CurState != PlayerState::Jump)
	{
		StateChange(PlayerState::Fall);
		return;
	}

	// 충돌맵 빨간색이면 아래로 이동 가능
	if (color[0] == RGB(255, 0, 0) &&
		true == CInput::GetInst()->IsDown('S'))
	{
		SetPos(m_Pos + Vector2{ 0, 2 });
	}

	// 회피키를 누르면 Dodge 상태로
	if (true == CInput::GetInst()->IsDown(VK_SHIFT))	// @@@ 회피 추가.
	{
		StateChange(PlayerState::Dodge);
		return;
	}

	// 공격
	if (true == CInput::GetInst()->IsDown(VK_LBUTTON))
	{
		StateChange(PlayerState::Attack);
		return;
	}



	// 점프키를 누르면 Jump 상태로
	if (true == CInput::GetInst()->IsDown(VK_SPACE))		// @@@ 점프 추가.
	{
		StateChange(PlayerState::Jump);
		return;
	}

	if (true == CInput::GetInst()->IsDown(VK_LBUTTON))
	{
		StateChange(PlayerState::Attack);
		return;
	}

}

void CPlayer::FallUpdate()
{
	// 공중에 뜬 상태일경우 중력영향을 받는다.
	// 중력 가속도에 따른 낙하 속도.
	{
		// 내포지션에서 원하는 위치의 픽셀의 색상을 구할 수 있다.
		int Color = m_MapColTexture->GetImagePixel(m_Pos + Vector2{ 0.f,1.f });
		m_Gravity += m_GravityAccel * DELTA_TIME;
		if (RGB(0, 0, 0) == Color || RGB(255, 0, 0) == Color)	// 땅에 닿을 경우 
		{
			m_Gravity = 10.0f;
			m_MoveDir.Normalize();


			StateChange(PlayerState::Landing);
			return;
		}
		Move(Vector2{ 0.f, 1.f } *m_Gravity * DELTA_TIME);
	}



	// 공격
	if (true == CInput::GetInst()->IsDown(VK_LBUTTON))
	{
		StateChange(PlayerState::Attack);
		return;
	}

	if (true == CInput::GetInst()->IsPress('A'))
	{
		m_MoveDir += Vector2{ -1.f, 0.f } * DELTA_TIME * 2000.f;
		Vector2 TempX = { m_MoveDir.x, 0.f };

		if (TempX.Length() >= 450.f)
		{
			TempX.Normalize();
			TempX *= 450.f;
			m_MoveDir.x = TempX.x;
		}
	}
	if (true == CInput::GetInst()->IsPress('D'))
	{
		m_MoveDir += Vector2{ 1.f, 0.f } * DELTA_TIME * 2000.f;
		Vector2 TempX = { m_MoveDir.x, 0.f };

		if (TempX.Length() >= 450.f)
		{
			TempX.Normalize();
			TempX *= 450.f;
			m_MoveDir.x = TempX.x;
		}
	}

	if (true == CInput::GetInst()->IsPress('S'))
	{
		m_MoveDir += Vector2{ 0.f , 1.f } * DELTA_TIME * 4000;
	}

	MapCollisionCheckMoveAir();

}

void CPlayer::DodgeUpdate()
{
	// 닷지 구름 이펙트 생성
	m_StateTime[static_cast<int>(PlayerState::Dodge)] += DELTA_TIME;
	if (0.02f <= m_StateTime[static_cast<int>(PlayerState::Dodge)])
	{
		CEffect_DustCloud* NewEffect = m_Scene->CreateObject<CEffect_DustCloud>("DustCloud");

		NewEffect->SetPivot(0.5f, 0.5f);
		NewEffect->SetPos(m_Pos);

		if (m_CurDir == PlayerDir::Right)
			NewEffect->SetDir(ObjDir::Left);
		else if (m_CurDir == PlayerDir::Left)
			NewEffect->SetDir(ObjDir::Right);
		m_StateTime[static_cast<int>(PlayerState::Dodge)] = 0.f;

		NewEffect->AddAnimation("spr_dustcloud", false, 0.36f);

	}

	// 닷지 종료시 RunToIdle 상태로
	if (true == m_Animation->IsEndAnimation())
	{
		StateChange(PlayerState::RunToIdle);
		return;
	}


	// 아래쪽에 지형이 없다면 Fall상태로
	int color[10] = {};
	for (int i = 1; i <= 10; ++i)
	{
		color[i - 1] = m_MapColTexture->GetImagePixel(m_Pos + Vector2{ 0.f,(float)i });
	}
	if (color[0] != RGB(0, 0, 0) && color[0] != RGB(255, 0, 0) &&
		color[1] != RGB(0, 0, 0) &&
		color[2] != RGB(0, 0, 0) &&
		color[3] != RGB(0, 0, 0) &&
		color[4] != RGB(0, 0, 0) &&
		color[5] != RGB(0, 0, 0) &&
		color[6] != RGB(0, 0, 0) &&
		color[7] != RGB(0, 0, 0) &&
		color[8] != RGB(0, 0, 0) &&
		color[9] != RGB(0, 0, 0) &&
		m_CurState != PlayerState::Jump)
	{
		StateChange(PlayerState::Fall);
		return;
	}


	// 점프키를 누르면 Jump 상태로
	if (true == CInput::GetInst()->IsDown(VK_SPACE))		// @@@ 점프 추가.
	{
		StateChange(PlayerState::Jump);
		return;
	}

	if (true == CInput::GetInst()->IsDown(VK_LBUTTON))
	{
		StateChange(PlayerState::Attack);
		return;
	}

	MapCollisionCheckMoveGround();

}

void CPlayer::PlaySongUpdate()
{
	// 애니메이션이 끝나면 Idle 상태로
	if (true == m_Animation->IsEndAnimation())
	{
		StateChange(PlayerState::Idle);
		m_Scene->SetBgmOn(true);
		return;
	}
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

	// 런 스타트 구름 이펙트
	for (int i = 0; i < 5; ++i)
	{
		CEffect_DustCloud* NewEffect = m_Scene->CreateObject<CEffect_DustCloud>("DustCloud");
		NewEffect->SetPivot(0.5f, 0.5f);
		NewEffect->SetPos(m_Pos);

		if (m_CurDir == PlayerDir::Right)
			NewEffect->SetDir(ObjDir::Left);
		else if (m_CurDir == PlayerDir::Left)
			NewEffect->SetDir(ObjDir::Right);

		NewEffect->AddAnimation("spr_dustcloud", false, 0.36f);

	}

	// 런 스타트 사운드
	m_Scene->GetSceneResource()->SoundPlay("sound_player_prerun");


}

void CPlayer::RunToIdleStart()
{
	m_AnimationName = "spr_run_to_idle_";
	ChangeAnimation(m_AnimationName + m_ChangeDirText);
	SetSpeed(100.f);

}

void CPlayer::JumpStart()
{
	// 점프 이펙트
	CEffect_JumpCloud* NewEffect = m_Scene->CreateObject<CEffect_JumpCloud>("JumpCloud");
	NewEffect->SetPos(m_Pos);
	NewEffect->SetPivot(0.5f, 1.f);
	NewEffect->AddAnimation("spr_jumpcloud", false, 0.24f);

	// 점프 사운드
	m_Scene->GetSceneResource()->SoundPlay("sound_player_jump");

	SetPos(m_Pos + Vector2{ 0, -4 });
	m_AnimationName = "spr_jump_";
	ChangeAnimation(m_AnimationName + m_ChangeDirText);
	m_MoveDir *= m_MoveSpeed;
	m_MoveDir += Vector2{ 0.f, -1.f } * m_JumpPower;	// 점프 파워

	m_StateTime[static_cast<int>(PlayerState::Jump)] = 0.f;
	m_IsLongJump = false;
}

void CPlayer::LandingStart()
{
	//// 착지 이펙트
	CEffect_LandCloud* NewEffect = m_Scene->CreateObject<CEffect_LandCloud>("LandCloud");
	NewEffect->SetPos(m_Pos);
	NewEffect->SetPivot(0.5f, 1.f);
	NewEffect->AddAnimation("spr_landcloud", false, 0.42f);


	// 착지 사운드
	m_Scene->GetSceneResource()->SoundPlay("sound_player_land");

	m_AnimationName = "spr_landing_";
	ChangeAnimation(m_AnimationName + m_ChangeDirText);
	m_MoveDir = Vector2{ 0.f, 0.f };
	SetSpeed(0.f);
	m_AttackCount = 0;


}

void CPlayer::AttackStart()
{
	// 시드값을 얻기 위한 random_device 생성.
	std::random_device rd;
	// random_device 를 통해 난수 생성 엔진을 초기화 한다.
	std::mt19937 gen(rd());
	// 0 부터 99 까지 균등하게 나타나는 난수열을 생성하기 위해 균등 분포 정의.
	std::uniform_int_distribution<int> IntRange(0, 2);
	int Num = IntRange(gen);

	// 어택 사운드 랜덤 재생
	if (Num == 0)
	{
		m_Scene->GetSceneResource()->SoundPlay("sound_player_slash_1");
	}
	else if (Num == 1)
	{
		m_Scene->GetSceneResource()->SoundPlay("sound_player_slash_2");
	}
	else if (Num == 2)
	{
		m_Scene->GetSceneResource()->SoundPlay("sound_player_slash_3");
	}

	// 어택 이펙트
	CEffect_Slash* NewEffect = m_Scene->CreateObject<CEffect_Slash>("Slash");
	NewEffect->SetPos(m_Pos);
	NewEffect->SetPivot(0.5f, 1.f);
	NewEffect->AddAnimation("spr_slash", false, 0.196f);


	// 공격 방향은 마우스 방향 고정
	m_AnimationName = "spr_attack_";
	if (CInput::GetInst()->GetMouseWorldPos().x >= (m_Pos + Vector2{0.f, -35}).x)
	{
		m_CurDir = PlayerDir::Right;
		m_ChangeDirText = "right";
	}
	else if (CInput::GetInst()->GetMouseWorldPos().x < (m_Pos + Vector2{ 0.f, -35 }).x)
	{
		m_CurDir = PlayerDir::Left;
		m_ChangeDirText = "left";
	}
	ChangeAnimation(m_AnimationName + m_ChangeDirText);

	// 플레이어->마우스 방향 벡터 획득
	Vector2 AttackDir = CInput::GetInst()->GetMouseWorldPos() - (m_Pos + Vector2{0,-35});
	AttackDir.Normalize();

	// 전역 변수에 공격방향 저장.
	g_AttackDir = AttackDir;

	// 공격 판정 충돌체 추가
	CColliderBox* Box = AddCollider<CColliderBox>("PlayerAttack");
	Box->SetExtent(76.f, 76.f);
	Box->SetOffset(Vector2{ 0.f, -35.f } + AttackDir * 66.f);
	Box->SetCollisionProfile("PlayerAttack");
	m_PlayerAttackCollision = Box;


	m_MoveDir = Vector2{ 0.f, 0.f };
	// 공중에서 최초 한번의 공격일때만 y축 전진성을 부여한다.
	if (m_AttackCount <= 0)
	{
		m_MoveDir = AttackDir * 540.f;
		++m_AttackCount;
	}
	else if (m_AttackCount >= 1)
	{
		// 플레이어는 2회 공격이후 y축 이동 제한, 공중 무한 날기 방지용
		if (AttackDir.y < 0)
		{
			m_MoveDir = Vector2{ AttackDir.x, 0 } * 540.f;
		}
		else
		{
			m_MoveDir = Vector2{ AttackDir.x, AttackDir.y } * 540.f;
		}
	}
	m_Gravity = 10.f;	// 공격 후 중력 초기화

}

void CPlayer::WallGrabUpdate()
{
}

void CPlayer::HurtFlyLoopStart()
{
	m_MoveDir = m_EnemyAttackDir;

	if (m_EnemyAttackDir.x > 0)
	{
		m_CurDir = PlayerDir::Left;
	}
	else if (m_EnemyAttackDir.x < 0)
	{
		m_CurDir = PlayerDir::Right;
	}
	m_AnimationName = "spr_hurtfly_begin_";
	ChangeAnimation(m_AnimationName + m_ChangeDirText);
	
	SetPos(m_Pos + Vector2{ 0.f, -3.f });

	// 공격 판정이 남아있으면 사망시 삭제
	if (m_PlayerAttackCollision != nullptr)
	{
		m_PlayerAttackCollision->SetActive(false);
		m_PlayerAttackCollision = nullptr;
	}

	// 히트시 화면 흔들림
	m_Scene->SetCameraShakeOn(true);

	

}

void CPlayer::HurtGroundStart()
{
	m_AnimationName = "spr_hurtground_";
	ChangeAnimation(m_AnimationName + m_ChangeDirText);
	SetSpeed(0.f);

}

void CPlayer::DeadStart()
{
}


void CPlayer::FallStart()
{
	m_AnimationName = "spr_fall_";
	ChangeAnimation(m_AnimationName + m_ChangeDirText);
}

void CPlayer::FlipUpdate()
{
}

void CPlayer::HurtFlyLoopUpdate()
{
	if (true == m_Animation->CheckCurrentAnimation("spr_hurtfly_begin_left") &&
		true == m_Animation->IsEndAnimation())
	{
		m_AnimationName = "spr_hurtfly_loop_left";
		ChangeAnimation(m_AnimationName);
	}

	else if (true == m_Animation->CheckCurrentAnimation("spr_hurtfly_begin_right") &&
		true == m_Animation->IsEndAnimation())
	{
		m_AnimationName = "spr_hurtfly_loop_right";
		ChangeAnimation(m_AnimationName);
	}

	// 공중에 뜬 상태일경우 중력영향을 받는다.
	// 중력 가속도에 따른 낙하 속도.
	{
		// 내포지션에서 원하는 위치의 픽셀의 색상을 구할 수 있다.
		int Color = m_MapColTexture->GetImagePixel(m_Pos + Vector2{ 0.f,1.f });
		m_Gravity += m_GravityAccel * DELTA_TIME;
		if (RGB(0, 0, 0) == Color || RGB(255, 0, 0) == Color)	// 땅에 닿을 경우 
		{
			m_Gravity = 10.0f;
			m_MoveDir.Normalize();


			StateChange(PlayerState::HurtGround);
			return;
		}
		Move(Vector2{ 0.f, 1.f } *m_Gravity * DELTA_TIME);
	}

	MapCollisionCheckMoveAirDie();
}


void CPlayer::DodgeStart()
{
	// 닷지 사운드
	{
		m_Scene->GetSceneResource()->SoundPlay("sound_player_roll");
	}
	{
		m_Scene->GetSceneResource()->SoundPlay("sound_player_roll_real");
	}

	m_StateTime[static_cast<int>(PlayerState::Dodge)] = 0.f;

	m_AnimationName = "spr_roll_";
	ChangeAnimation(m_AnimationName + m_ChangeDirText);
	SetSpeed(680.f);

	// 점프 후 착지시 방향벡터가 0이 되는순간에 구르기할시 제자리에서 구르기 방지.
	if (m_CurDir == PlayerDir::Right)
		m_MoveDir = { 1.f, 0.f };
	else if (m_CurDir == PlayerDir::Left)
		m_MoveDir = { -1.f, 0.f };


}

void CPlayer::PlaySongStart()
{
	m_StateTime[static_cast<int>(PlayerState::PlaySong)] = 0.f;

	m_AnimationName = "spr_player_playsong";
	ChangeAnimation(m_AnimationName);

}

void CPlayer::HurtGroundUpdate()
{
	if (true == m_Animation->IsEndAnimation())
	{
		StateChange(PlayerState::Dead);
		return;
	}
}

void CPlayer::DeadUpdate()
{
}

void CPlayer::MapCollisionCheckMoveGround()
{
	{
		// 미래의 위치를 계산하여 그곳의 RGB값을 체크하고, 이동 가능한 곳이면 이동한다.
		Vector2 NextPos = m_Pos + (Vector2{ 0,m_MoveDir.y } * DELTA_TIME * m_MoveSpeed);
		Vector2 CheckPos = NextPos + Vector2{ 0,0 };	// 미래 위치의 발기준 색상
		Vector2 CheckPosTopRight = NextPos + Vector2{ 18,-80 };	// 미래 위치의 머리기준 색상
		Vector2 CheckPosTopLeft = NextPos + Vector2{ -18,-80 };	// 미래 위치의 머리기준 색상

		int Color = m_MapColTexture->GetImagePixel(CheckPos);
		int TopRightColor = m_MapColTexture->GetImagePixel(CheckPosTopRight);
		int TopLeftColor = m_MapColTexture->GetImagePixel(CheckPosTopLeft);



		if (RGB(0, 0, 0) != Color &&
			RGB(0, 0, 0) != TopRightColor &&
			RGB(0, 0, 0) != TopLeftColor)
		{
			MoveDir(Vector2{ 0.f, m_MoveDir.y });
		}
	}

	{
		// 미래의 위치를 계산하여 그곳의 RGB값을 체크하고, 이동 가능한 곳이면 이동한다.
		Vector2 NextPos = m_Pos + (Vector2{ m_MoveDir.x,0 } * DELTA_TIME * m_MoveSpeed);
		Vector2 CheckPos = NextPos + Vector2{ 0,0 };	// 미래 위치의 발기준 색상
		Vector2 CheckPosTopRight = NextPos + Vector2{ 18,-80 };	// 미래 위치의 머리기준 색상
		Vector2 CheckPosTopLeft = NextPos + Vector2{ -18,-80 };	// 미래 위치의 머리기준 색상
		Vector2 ForDownPos = m_Pos + Vector2{ 0,1.f };	// 발 아래 색상

		int CurColor = m_MapColTexture->GetImagePixel(m_Pos);
		int ForDownColor = m_MapColTexture->GetImagePixel(ForDownPos);
		int Color = m_MapColTexture->GetImagePixel(CheckPos);
		int TopRightColor = m_MapColTexture->GetImagePixel(CheckPosTopRight);
		int TopLeftColor = m_MapColTexture->GetImagePixel(CheckPosTopLeft);


		// 항상 땅에 붙어있기
		if (RGB(0, 0, 0) != ForDownColor && RGB(255, 0, 0) != ForDownColor)
		{
			SetPos(Vector2{ m_Pos.x, m_Pos.y + 2.f });
		}

		// 계단 올라가기
		while (RGB(0, 0, 0) == Color &&
			TopRightColor != RGB(0, 0, 0) && TopLeftColor != RGB(0, 0, 0))
		{
			CheckPos.y -= 1.0f;
			Color = m_MapColTexture->GetImagePixel(CheckPos);
			SetPos(Vector2{ m_Pos.x, m_Pos.y -1.0f });
		}


		if (RGB(0, 0, 0) != Color &&
			RGB(0, 0, 0) != TopRightColor &&
			RGB(0, 0, 0) != TopLeftColor)
		{
			MoveDir(Vector2{ m_MoveDir.x,0 });
		}

	}


}

void CPlayer::MapCollisionCheckMoveAir()
{
	{
		// 미래의 위치를 계산하여 그곳의 RGB값을 체크하고, 이동 가능한 곳이면 이동한다.
		Vector2 NextPos = m_Pos + (Vector2{ 0,m_MoveDir.y } * DELTA_TIME);
		Vector2 CheckPos = NextPos + Vector2{ 0,0 };	// 미래 위치의 발기준 색상
		Vector2 CheckPosTopRight = NextPos + Vector2{ 18,-80 };	// 미래 위치의 머리기준 색상
		Vector2 CheckPosTopLeft = NextPos + Vector2{ -18,-80 };	// 미래 위치의 머리기준 색상

		int Color = m_MapColTexture->GetImagePixel(CheckPos);
		int TopRightColor = m_MapColTexture->GetImagePixel(CheckPosTopRight);
		int TopLeftColor = m_MapColTexture->GetImagePixel(CheckPosTopLeft);


		if (RGB(0, 0, 0) != Color &&
			RGB(0, 0, 0) != TopRightColor &&
			RGB(0, 0, 0) != TopLeftColor)
		{
			Move(Vector2{ 0.f , m_MoveDir.y } * DELTA_TIME);
		}
	}

	{
		// 미래의 위치를 계산하여 그곳의 RGB값을 체크하고, 이동 가능한 곳이면 이동한다.
		Vector2 NextPos = m_Pos + (Vector2{ m_MoveDir.x,0.f } * DELTA_TIME);
		Vector2 CheckPos = NextPos + Vector2{ 0.f, 0.f };	// 미래 위치의 발기준 색상
		Vector2 CheckPosTopRight = NextPos + Vector2{ 18,-80 };	// 미래 위치의 머리기준 색상
		Vector2 CheckPosTopLeft = NextPos + Vector2{ -18,-80 };	// 미래 위치의 머리기준 색상

		int Color = m_MapColTexture->GetImagePixel(CheckPos);
		int TopRightColor = m_MapColTexture->GetImagePixel(CheckPosTopRight);
		int TopLeftColor = m_MapColTexture->GetImagePixel(CheckPosTopLeft);

		if (RGB(0, 0, 0) != Color &&
			RGB(0, 0, 0) != TopRightColor &&
			RGB(0, 0, 0) != TopLeftColor)
		{
			Move(Vector2{ m_MoveDir.x,0 } * DELTA_TIME);
		}
	}

}

void CPlayer::WallGrabStart()
{
}

void CPlayer::FlipStart()
{
}


void CPlayer::RunningSound()
{
	m_Scene->GetSceneResource()->SoundPlay("sound_player_running_2");

}