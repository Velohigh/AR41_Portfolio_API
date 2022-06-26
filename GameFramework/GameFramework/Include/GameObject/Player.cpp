
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
#include <random>

Vector2 g_AttackDir = Vector2{ 0.f , 0.f };

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

	// �ִϸ��̼� �߰�
	CreateAnimationSequence();

	// �ִϸ��̼� ����� ȣ���Լ�
	//SetEndFunction<CPlayer>("PlayerRightAttack", this, &CPlayer::AttackEnd);
	//SetEndFunction<CPlayer>("PlayerLeftAttack", this, &CPlayer::AttackEnd);

	// Notify �߰�
	AddNotify<CPlayer>("spr_run_left", 3, this, &CPlayer::RunningSound);
	AddNotify<CPlayer>("spr_run_left", 8, this, &CPlayer::RunningSound);
	AddNotify<CPlayer>("spr_run_right", 3, this, &CPlayer::RunningSound);
	AddNotify<CPlayer>("spr_run_right", 8, this, &CPlayer::RunningSound);

	// ���� �ε�
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



	// ����
	m_CurDir = PlayerDir::Right;

	// �浹ü �߰�
	CColliderBox* Box = AddCollider<CColliderBox>("Body");

	Box->SetExtent(36.f, 70.f);
	Box->SetOffset(0.f, -35.f);
	Box->SetCollisionProfile("Player");

	Box->SetCollisionBeginFunction<CPlayer>(this, &CPlayer::CollisionBegin);
	Box->SetCollisionEndFunction<CPlayer>(this, &CPlayer::CollisionEnd);


	//// Ű �Է� �Լ� ������
	//CInput::GetInst()->AddBindFunction<CPlayer>("MoveUp", 
	//	Input_Type::Push, this, &CPlayer::MoveUp);


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


	// �浹�� ����
	SetMapTexture("room_factory_2_ColMap", TEXT("room_factory_2_ColMap.bmp"), "MapPath");

	ChangeAnimation("spr_idle_right");

	// �ʱ� ����
	m_AnimationName = "spr_idle_";
	m_CurState = PlayerState::Idle;
	m_CurDir = PlayerDir::Right;


	return true;
}

void CPlayer::Update(float DeltaTime)
{
	CCharacter::Update(DeltaTime);
	DeltaTime *= m_TimeScale;

	// ���� �Լ�
	DirAnimationCheck();
	StateUpdate();


	//int COLOR = m_MapColTexture->GetImagePixel((int)m_Pos.x, (int)m_Pos.y);
	//if (RGB(0,0,0) == COLOR)
	//	MessageBoxA(nullptr, "�浹�ʰ� ������.", "ERROR", MB_OK);

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
			// %d�� i�� ���� ���ԵǾ� ���ڿ��� ��������� �ȴ�.
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
			// %d�� i�� ���� ���ԵǾ� ���ڿ��� ��������� �ȴ�.
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
			// %d�� i�� ���� ���ԵǾ� ���ڿ��� ��������� �ȴ�.
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
			// %d�� i�� ���� ���ԵǾ� ���ڿ��� ��������� �ȴ�.
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
			// %d�� i�� ���� ���ԵǾ� ���ڿ��� ��������� �ȴ�.
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
			// %d�� i�� ���� ���ԵǾ� ���ڿ��� ��������� �ȴ�.
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

	// Run_To_Idle_Left
	{
		std::vector<std::wstring>	vecFileName;

		for (int i = 0; i <= 4; ++i)
		{
			TCHAR	FileName[MAX_PATH] = {};
			// %d�� i�� ���� ���ԵǾ� ���ڿ��� ��������� �ȴ�.
			wsprintf(FileName, TEXT("Player/spr_run_to_idle_left/%d.bmp"), i);
			vecFileName.push_back(FileName);
		}

		CResourceManager::GetInst()->CreateAnimationSequence("spr_run_to_idle_left",
			"spr_run_to_idle_left", vecFileName, TEXTURE_PATH);

		for (int i = 0; i <= 4; ++i)
		{
			CResourceManager::GetInst()->AddAnimationFrame("spr_run_to_idle_left", 0.f, 0.f,
				52.f, 36.f);
		}

		CResourceManager::GetInst()->SetColorKey("spr_run_to_idle_left", 255, 255, 255);

		AddAnimation("spr_run_to_idle_left", true, 0.35f);
	}

	// Run_To_Idle_Right
	{
		std::vector<std::wstring>	vecFileName;

		for (int i = 0; i <= 4; ++i)
		{
			TCHAR	FileName[MAX_PATH] = {};
			// %d�� i�� ���� ���ԵǾ� ���ڿ��� ��������� �ȴ�.
			wsprintf(FileName, TEXT("Player/spr_run_to_idle_right/%d.bmp"), i);
			vecFileName.push_back(FileName);
		}

		CResourceManager::GetInst()->CreateAnimationSequence("spr_run_to_idle_right",
			"spr_run_to_idle_right", vecFileName, TEXTURE_PATH);

		for (int i = 0; i <= 4; ++i)
		{
			CResourceManager::GetInst()->AddAnimationFrame("spr_run_to_idle_right", 0.f, 0.f,
				52.f, 36.f);
		}

		CResourceManager::GetInst()->SetColorKey("spr_run_to_idle_right", 255, 255, 255);

		AddAnimation("spr_run_to_idle_right", true, 0.35f);
	}

	// spr_jump_left
	{
		std::vector<std::wstring>	vecFileName;

		for (int i = 0; i <= 3; ++i)
		{
			TCHAR	FileName[MAX_PATH] = {};
			// %d�� i�� ���� ���ԵǾ� ���ڿ��� ��������� �ȴ�.
			wsprintf(FileName, TEXT("Player/spr_jump_left/%d.bmp"), i);
			vecFileName.push_back(FileName);
		}

		CResourceManager::GetInst()->CreateAnimationSequence("spr_jump_left",
			"spr_jump_left", vecFileName, TEXTURE_PATH);

		for (int i = 0; i <= 3; ++i)
		{
			CResourceManager::GetInst()->AddAnimationFrame("spr_jump_left", 0.f, 0.f,
				32.f, 42.f);
		}

		CResourceManager::GetInst()->SetColorKey("spr_jump_left", 255, 255, 255);

		AddAnimation("spr_jump_left", true, 0.28f);
	}

	// spr_jump_right
	{
		std::vector<std::wstring>	vecFileName;

		for (int i = 0; i <= 3; ++i)
		{
			TCHAR	FileName[MAX_PATH] = {};
			// %d�� i�� ���� ���ԵǾ� ���ڿ��� ��������� �ȴ�.
			wsprintf(FileName, TEXT("Player/spr_jump_right/%d.bmp"), i);
			vecFileName.push_back(FileName);
		}

		CResourceManager::GetInst()->CreateAnimationSequence("spr_jump_right",
			"spr_jump_right", vecFileName, TEXTURE_PATH);

		for (int i = 0; i <= 3; ++i)
		{
			CResourceManager::GetInst()->AddAnimationFrame("spr_jump_right", 0.f, 0.f,
				32.f, 42.f);
		}

		CResourceManager::GetInst()->SetColorKey("spr_jump_right", 255, 255, 255);

		AddAnimation("spr_jump_right", true, 0.28f);
	}

	// spr_fall_left
	{
		std::vector<std::wstring>	vecFileName;

		for (int i = 0; i <= 3; ++i)
		{
			TCHAR	FileName[MAX_PATH] = {};
			// %d�� i�� ���� ���ԵǾ� ���ڿ��� ��������� �ȴ�.
			wsprintf(FileName, TEXT("Player/spr_fall_left/%d.bmp"), i);
			vecFileName.push_back(FileName);
		}

		CResourceManager::GetInst()->CreateAnimationSequence("spr_fall_left",
			"spr_fall_left", vecFileName, TEXTURE_PATH);

		for (int i = 0; i <= 3; ++i)
		{
			CResourceManager::GetInst()->AddAnimationFrame("spr_fall_left", 0.f, 0.f,
				42.f, 48.f);
		}

		CResourceManager::GetInst()->SetColorKey("spr_fall_left", 255, 255, 255);

		AddAnimation("spr_fall_left", true, 0.28f);
	}

	// spr_fall_right
	{
		std::vector<std::wstring>	vecFileName;

		for (int i = 0; i <= 3; ++i)
		{
			TCHAR	FileName[MAX_PATH] = {};
			// %d�� i�� ���� ���ԵǾ� ���ڿ��� ��������� �ȴ�.
			wsprintf(FileName, TEXT("Player/spr_fall_right/%d.bmp"), i);
			vecFileName.push_back(FileName);
		}

		CResourceManager::GetInst()->CreateAnimationSequence("spr_fall_right",
			"spr_fall_right", vecFileName, TEXTURE_PATH);

		for (int i = 0; i <= 3; ++i)
		{
			CResourceManager::GetInst()->AddAnimationFrame("spr_fall_right", 0.f, 0.f,
				42.f, 48.f);
		}

		CResourceManager::GetInst()->SetColorKey("spr_fall_right", 255, 255, 255);

		AddAnimation("spr_fall_right", true, 0.28f);
	}

	// spr_attack_left
	{
		std::vector<std::wstring>	vecFileName;

		for (int i = 0; i <= 6; ++i)
		{
			TCHAR	FileName[MAX_PATH] = {};
			// %d�� i�� ���� ���ԵǾ� ���ڿ��� ��������� �ȴ�.
			wsprintf(FileName, TEXT("Player/spr_attack_left/%d.bmp"), i);
			vecFileName.push_back(FileName);
		}

		CResourceManager::GetInst()->CreateAnimationSequence("spr_attack_left",
			"spr_attack_left", vecFileName, TEXTURE_PATH);

		for (int i = 0; i <= 6; ++i)
		{
			CResourceManager::GetInst()->AddAnimationFrame("spr_attack_left", 0.f, 0.f,
				62.f, 42.f);
		}

		CResourceManager::GetInst()->SetColorKey("spr_attack_left", 255, 255, 255);

		AddAnimation("spr_attack_left", true, 0.196f);
	}

	// spr_attack_right
	{
		std::vector<std::wstring>	vecFileName;

		for (int i = 0; i <= 6; ++i)
		{
			TCHAR	FileName[MAX_PATH] = {};
			// %d�� i�� ���� ���ԵǾ� ���ڿ��� ��������� �ȴ�.
			wsprintf(FileName, TEXT("Player/spr_attack_right/%d.bmp"), i);
			vecFileName.push_back(FileName);
		}

		CResourceManager::GetInst()->CreateAnimationSequence("spr_attack_right",
			"spr_attack_right", vecFileName, TEXTURE_PATH);

		for (int i = 0; i <= 6; ++i)
		{
			CResourceManager::GetInst()->AddAnimationFrame("spr_attack_right", 0.f, 0.f,
				62.f, 42.f);
		}

		CResourceManager::GetInst()->SetColorKey("spr_attack_right", 255, 255, 255);

		AddAnimation("spr_attack_right", true, 0.196f);
	}

	// spr_landing_left
	{
		std::vector<std::wstring>	vecFileName;

		for (int i = 0; i <= 4; ++i)
		{
			TCHAR	FileName[MAX_PATH] = {};
			// %d�� i�� ���� ���ԵǾ� ���ڿ��� ��������� �ȴ�.
			wsprintf(FileName, TEXT("Player/spr_landing_left/%d.bmp"), i);
			vecFileName.push_back(FileName);
		}

		CResourceManager::GetInst()->CreateAnimationSequence("spr_landing_left",
			"spr_landing_left", vecFileName, TEXTURE_PATH);

		for (int i = 0; i <= 4; ++i)
		{
			CResourceManager::GetInst()->AddAnimationFrame("spr_landing_left", 0.f, 0.f,
				52.f, 36.f);
		}

		CResourceManager::GetInst()->SetColorKey("spr_landing_left", 255, 255, 255);

		AddAnimation("spr_landing_left", true, 0.3f);
	}

	// spr_landing_right
	{
		std::vector<std::wstring>	vecFileName;

		for (int i = 0; i <= 4; ++i)
		{
			TCHAR	FileName[MAX_PATH] = {};
			// %d�� i�� ���� ���ԵǾ� ���ڿ��� ��������� �ȴ�.
			wsprintf(FileName, TEXT("Player/spr_landing_right/%d.bmp"), i);
			vecFileName.push_back(FileName);
		}

		CResourceManager::GetInst()->CreateAnimationSequence("spr_landing_right",
			"spr_landing_right", vecFileName, TEXTURE_PATH);

		for (int i = 0; i <= 4; ++i)
		{
			CResourceManager::GetInst()->AddAnimationFrame("spr_landing_right", 0.f, 0.f,
				52.f, 36.f);
		}

		CResourceManager::GetInst()->SetColorKey("spr_landing_right", 255, 255, 255);

		AddAnimation("spr_landing_right", true, 0.3f);
	}

	// spr_roll_left
	{
		std::vector<std::wstring>	vecFileName;

		for (int i = 0; i <= 6; ++i)
		{
			TCHAR	FileName[MAX_PATH] = {};
			// %d�� i�� ���� ���ԵǾ� ���ڿ��� ��������� �ȴ�.
			wsprintf(FileName, TEXT("Player/spr_roll_left/%d.bmp"), i);
			vecFileName.push_back(FileName);
		}

		CResourceManager::GetInst()->CreateAnimationSequence("spr_roll_left",
			"spr_roll_left", vecFileName, TEXTURE_PATH);

		for (int i = 0; i <= 6; ++i)
		{
			CResourceManager::GetInst()->AddAnimationFrame("spr_roll_left", 0.f, 0.f,
				48.f, 33.f);
		}

		CResourceManager::GetInst()->SetColorKey("spr_roll_left", 255, 255, 255);

		AddAnimation("spr_roll_left", true, 0.315f);
	}

	// spr_roll_right
	{
		std::vector<std::wstring>	vecFileName;

		for (int i = 0; i <= 6; ++i)
		{
			TCHAR	FileName[MAX_PATH] = {};
			// %d�� i�� ���� ���ԵǾ� ���ڿ��� ��������� �ȴ�.
			wsprintf(FileName, TEXT("Player/spr_roll_right/%d.bmp"), i);
			vecFileName.push_back(FileName);
		}

		CResourceManager::GetInst()->CreateAnimationSequence("spr_roll_right",
			"spr_roll_right", vecFileName, TEXTURE_PATH);

		for (int i = 0; i <= 6; ++i)
		{
			CResourceManager::GetInst()->AddAnimationFrame("spr_roll_right", 0.f, 0.f,
				48.f, 33.f);
		}

		CResourceManager::GetInst()->SetColorKey("spr_roll_right", 255, 255, 255);

		AddAnimation("spr_roll_right", true, 0.315f);
	}

	// spr_player_playsong
	{
		std::vector<std::wstring>	vecFileName;

		for (int i = 0; i <= 30; ++i)
		{
			TCHAR	FileName[MAX_PATH] = {};
			// %d�� i�� ���� ���ԵǾ� ���ڿ��� ��������� �ȴ�.
			wsprintf(FileName, TEXT("Player/spr_player_playsong/%d.bmp"), i);
			vecFileName.push_back(FileName);
		}

		CResourceManager::GetInst()->CreateAnimationSequence("spr_player_playsong",
			"spr_player_playsong", vecFileName, TEXTURE_PATH);

		for (int i = 0; i <= 30; ++i)
		{
			CResourceManager::GetInst()->AddAnimationFrame("spr_player_playsong", 0.f, 0.f,
				34.f, 36.f);
		}

		CResourceManager::GetInst()->SetColorKey("spr_player_playsong", 255, 255, 255);

		AddAnimation("spr_player_playsong", true, 3.41f);
	}

	// #################### EFFECT ####################
	// Dust_Cloud Animation
	{
		std::vector<std::wstring>	vecFileName;

		for (int i = 0; i <= 6; ++i)
		{
			TCHAR	FileName[MAX_PATH] = {};
			// %d�� i�� ���� ���ԵǾ� ���ڿ��� ��������� �ȴ�.
			wsprintf(FileName, TEXT("Effect/spr_dustcloud/%d.bmp"), i);
			vecFileName.push_back(FileName);
		}

		CResourceManager::GetInst()->CreateAnimationSequence("spr_dustcloud",
			"spr_dustcloud", vecFileName, TEXTURE_PATH);

		for (int i = 0; i <= 6; ++i)
		{
			CResourceManager::GetInst()->AddAnimationFrame("spr_dustcloud", 0.f, 0.f,
				19.f, 19.f);
		}

		CResourceManager::GetInst()->SetColorKey("spr_dustcloud", 255, 255, 255);

		AddAnimation("spr_dustcloud", true, 0.42f);
	}

	// Jump_Cloud
	{
		std::vector<std::wstring>	vecFileName;

		for (int i = 0; i <= 3; ++i)
		{
			TCHAR	FileName[MAX_PATH] = {};
			// %d�� i�� ���� ���ԵǾ� ���ڿ��� ��������� �ȴ�.
			wsprintf(FileName, TEXT("Effect/spr_jumpcloud/%d.bmp"), i);
			vecFileName.push_back(FileName);
		}

		CResourceManager::GetInst()->CreateAnimationSequence("spr_jumpcloud",
			"spr_jumpcloud", vecFileName, TEXTURE_PATH);

		for (int i = 0; i <= 3; ++i)
		{
			CResourceManager::GetInst()->AddAnimationFrame("spr_jumpcloud", 0.f, 0.f,
				32.f, 51.f);
		}

		CResourceManager::GetInst()->SetColorKey("spr_jumpcloud", 255, 255, 255);

		AddAnimation("spr_jumpcloud", true, 0.24f);
	}


	// Land_Cloud
	{
		std::vector<std::wstring>	vecFileName;

		for (int i = 0; i <= 6; ++i)
		{
			TCHAR	FileName[MAX_PATH] = {};
			// %d�� i�� ���� ���ԵǾ� ���ڿ��� ��������� �ȴ�.
			wsprintf(FileName, TEXT("Effect/spr_landcloud/%d.bmp"), i);
			vecFileName.push_back(FileName);
		}

		CResourceManager::GetInst()->CreateAnimationSequence("spr_landcloud",
			"spr_landcloud", vecFileName, TEXTURE_PATH);

		for (int i = 0; i <= 6; ++i)
		{
			CResourceManager::GetInst()->AddAnimationFrame("spr_landcloud", 0.f, 0.f,
				50.f, 14.f);
		}

		CResourceManager::GetInst()->SetColorKey("spr_landcloud", 255, 0, 255);

		AddAnimation("spr_landcloud", true, 0.42f);
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
	if (m_CurState != State)	// ���°� �ٲ� �ѹ��� ��������ش�.
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
	// �ƹ�Ű�� ������ �ʾҴٸ� false, �����ٸ� true ����
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
	// �̵�Ű�� ������ IdleToRun ���·�
	if (true == IsMoveKey())
	{
		StateChange(PlayerState::IdleToRun);
		return;
	}

	// �Ʒ��ʿ� ������ ���ٸ� Fall���·�
	int color = m_MapColTexture->GetImagePixel(m_Pos + Vector2{ 0,10 });
	int Rcolor = m_MapColTexture->GetImagePixel(m_Pos + Vector2{ 0,1 });
	if (color != RGB(0, 0, 0) && m_CurState != PlayerState::Jump &&
		Rcolor != RGB(255, 0, 0) &&
		Rcolor != RGB(0, 0, 0))
	{
		StateChange(PlayerState::Fall);
		return;
	}

	// �浹�� �������̸� �Ʒ��� �̵� ����
	if (Rcolor == RGB(255, 0, 0) &&
		true == CInput::GetInst()->IsDown('S'))
	{
		SetPos(m_Pos + Vector2{ 0, 2 });
	}

	// ����Ű�� ������ Jump ���·�
	if (true == CInput::GetInst()->IsDown(VK_SPACE))		// @@@ ���� �߰�.
	{
		StateChange(PlayerState::Jump);
		return;
	}

	// ����Ű�� ������ ���ݻ��·�
	if (true == CInput::GetInst()->IsDown(VK_LBUTTON))
	{
		StateChange(PlayerState::Attack);
		return;
	}

	// ȸ��
	if (true == CInput::GetInst()->IsDown(VK_SHIFT))	// @@@ ȸ�� �߰�.
	{
		StateChange(PlayerState::Dodge);
		return;
	}



}

void CPlayer::IdleToRunUpdate()
{
	// �ִϸ��̼� ������ Run �������
	if (true == m_Animation->IsEndAnimation())
	{
		StateChange(PlayerState::Run);
		return;
	}

	// �̵�Ű�� �ȴ����ٸ� Idle ���·�
	if (false == IsMoveKey())				// �̵�Ű�� �ȴ����ٸ�
	{
		StateChange(PlayerState::Idle);
		return;
	}

	// ����Ű�� ������ Jump ���·�
	if (true == CInput::GetInst()->IsDown(VK_SPACE))		// @@@ ���� �߰�.
	{
		StateChange(PlayerState::Jump);
		return;
	}

	// ȸ��Ű�� ������ Dodge ���·�
	if (true == CInput::GetInst()->IsDown(VK_SHIFT))	// @@@ ȸ�� �߰�.
	{
		StateChange(PlayerState::Dodge);
		return;
	}

	// ����
	if (true == CInput::GetInst()->IsDown(VK_LBUTTON))
	{
		StateChange(PlayerState::Attack);
		return;
	}

	// �Ʒ��ʿ� ������ ���ٸ� Fall���·�
	int color = m_MapColTexture->GetImagePixel(m_Pos + Vector2{ 0,10 });
	int Rcolor = m_MapColTexture->GetImagePixel(m_Pos + Vector2{ 0,1 });
	if (color != RGB(0, 0, 0) && m_CurState != PlayerState::Jump &&
		Rcolor != RGB(255, 0, 0) &&
		Rcolor != RGB(0, 0, 0))
	{
		StateChange(PlayerState::Fall);
		return;
	}

	// �浹�� �������̸� �Ʒ��� �̵� ����
	if (Rcolor == RGB(255, 0, 0) &&
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

	// �̵�Ű�� �ȴ����� Idle ���·�
	if (false == IsMoveKey())
	{
		StateChange(PlayerState::RunToIdle);
		return;
	}

	// ����Ű�� ������ Jump ���·�
	if (true == CInput::GetInst()->IsDown(VK_SPACE))		// @@@ ���� �߰�.
	{
		StateChange(PlayerState::Jump);
		return;
	}

	// �Ʒ��ʿ� ������ ���ٸ� Fall���·�
	int color = m_MapColTexture->GetImagePixel(m_Pos + Vector2{ 0,10 });
	int Rcolor = m_MapColTexture->GetImagePixel(m_Pos + Vector2{ 0,1 });
	if (color != RGB(0, 0, 0) && m_CurState != PlayerState::Jump &&
		Rcolor != RGB(255, 0, 0) &&
		Rcolor != RGB(0, 0, 0))
	{
		StateChange(PlayerState::Fall);
		return;
	}

	// �浹�� �������̸� �Ʒ��� �̵� ����
	if (Rcolor == RGB(255, 0, 0) &&
		true == CInput::GetInst()->IsDown('S'))
	{
		SetPos(m_Pos + Vector2{ 0, 2 });
	}

	// ȸ��Ű�� ������ Dodge ���·�
	if (true == CInput::GetInst()->IsDown(VK_SHIFT))	// @@@ ȸ�� �߰�.
	{
		StateChange(PlayerState::Dodge);
		return;
	}

	// ����
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
	// �̵�Ű�� ������ Run ���·�
	if (true == IsMoveKey())
	{
		StateChange(PlayerState::IdleToRun);
		return;
	}

	// ����Ű�� ������ Jump ���·�
	if (true == CInput::GetInst()->IsDown(VK_SPACE))		// @@@ ���� �߰�.
	{
		StateChange(PlayerState::Jump);
		return;
	}

	// �Ʒ��ʿ� ������ ���ٸ� Fall���·�
	int color = m_MapColTexture->GetImagePixel(m_Pos + Vector2{ 0,10 });
	int Rcolor = m_MapColTexture->GetImagePixel(m_Pos + Vector2{ 0,1 });
	if (color != RGB(0, 0, 0) && m_CurState != PlayerState::Jump &&
		Rcolor != RGB(255, 0, 0) &&
		Rcolor != RGB(0, 0, 0))
	{
		StateChange(PlayerState::Fall);
		return;
	}


	// �浹�� �������̸� �Ʒ��� �̵� ����
	if (Rcolor == RGB(255, 0, 0) &&
		true == CInput::GetInst()->IsDown('S'))
	{
		SetPos(m_Pos + Vector2{ 0, 2 });
	}

	// ȸ��Ű�� ������ Dodge ���·�
	if (true == CInput::GetInst()->IsDown(VK_SHIFT))	// @@@ ȸ�� �߰�.
	{
		StateChange(PlayerState::Dodge);
		return;
	}

	// ����
	if (true == CInput::GetInst()->IsDown(VK_LBUTTON))
	{
		StateChange(PlayerState::Attack);
		return;
	}

	// �̵�Ű�� �ȴ�����, �ִϸ��̼��� ������ ����Ǹ� Idle ���·�
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

	// ���ߴ��߿� �ٽ� �̵�Ű�� ������
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

	// ����
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

	// ���� ���� ���� ��� 
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
	//if (true == m_Animation->IsEndAnimation() &&
	//	PlayerAttackCollision_ != nullptr)
	//{
	//	PlayerAttackCollision_->Death();
	//}

	// ���� ������ Fall ���·�
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

	// �̵�Ű�� ������ IdleToRun ���·�
	if (true == IsMoveKey())
	{
		StateChange(PlayerState::IdleToRun);
		return;
	}

	//// �Ʒ��ʿ� ������ ���ٸ� Fall���·�
	int color = m_MapColTexture->GetImagePixel(m_Pos + Vector2{ 0.f,10.f });
	int Rcolor = m_MapColTexture->GetImagePixel(m_Pos + Vector2{ 0.f,1.f });
	if (color != RGB(0, 0, 0) && m_CurState != PlayerState::Jump &&
		Rcolor != RGB(255, 0, 0) &&
		Rcolor != RGB(0, 0, 0))
	{
		StateChange(PlayerState::Fall);
		return;
	}

	// ȸ��Ű�� ������ Dodge ���·�
	if (true == CInput::GetInst()->IsDown(VK_SHIFT))	// @@@ ȸ�� �߰�.
	{
		StateChange(PlayerState::Dodge);
		return;
	}

	// ����
	if (true == CInput::GetInst()->IsDown(VK_LBUTTON))
	{
		StateChange(PlayerState::Attack);
		return;
	}


	// �浹�� �������̸� �Ʒ��� �̵� ����
	if (Rcolor == RGB(255, 0, 0) &&
		true == CInput::GetInst()->IsDown('S'))
	{
		SetPos(m_Pos + Vector2{ 0, 2 });
	}

	// ����Ű�� ������ Jump ���·�
	if (true == CInput::GetInst()->IsDown(VK_SPACE))		// @@@ ���� �߰�.
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
	// ���߿� �� �����ϰ�� �߷¿����� �޴´�.
	// �߷� ���ӵ��� ���� ���� �ӵ�.
	{
		// �������ǿ��� ���ϴ� ��ġ�� �ȼ��� ������ ���� �� �ִ�.
		int Color = m_MapColTexture->GetImagePixel(m_Pos + Vector2{ 0.f,1.f });
		m_Gravity += m_GravityAccel * DELTA_TIME;
		if (RGB(0, 0, 0) == Color || RGB(255, 0, 0) == Color)	// ���� ���� ��� 
		{
			m_Gravity = 10.0f;
			m_MoveDir.Normalize();


			StateChange(PlayerState::Landing);
			return;
		}
		Move(Vector2{ 0.f, 1.f } *m_Gravity * DELTA_TIME);
	}


	// ����
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
	// ���� ���� ����Ʈ ����
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

	// ���� ����� RunToIdle ���·�
	if (true == m_Animation->IsEndAnimation())
	{
		StateChange(PlayerState::RunToIdle);
		return;
	}



	// ����Ű�� ������ Jump ���·�
	if (true == CInput::GetInst()->IsDown(VK_SPACE))		// @@@ ���� �߰�.
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
}


	//## Start
void CPlayer::IdleStart()
{
	// �ִϸ��̼� ü����
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
	m_AnimationName = "spr_run_to_idle_";
	ChangeAnimation(m_AnimationName + m_ChangeDirText);
	SetSpeed(100.f);

}

void CPlayer::JumpStart()
{
	// ���� ����Ʈ
	CEffect_JumpCloud* NewEffect = m_Scene->CreateObject<CEffect_JumpCloud>("JumpCloud");
	NewEffect->SetPos(m_Pos);
	NewEffect->SetPivot(0.5f, 1.f);
	NewEffect->AddAnimation("spr_jumpcloud", false, 0.24f);

	// ���� ����
	m_Scene->GetSceneResource()->SoundPlay("sound_player_jump");

	SetPos(m_Pos + Vector2{ 0, -3 });
	m_AnimationName = "spr_jump_";
	ChangeAnimation(m_AnimationName + m_ChangeDirText);
	m_MoveDir *= m_MoveSpeed;
	m_MoveDir += Vector2{ 0.f, -1.f } * m_JumpPower;	// ���� �Ŀ�

	m_StateTime[static_cast<int>(PlayerState::Jump)] = 0.f;
	m_IsLongJump = false;
}

void CPlayer::LandingStart()
{
	//// ���� ����Ʈ
	CEffect_LandCloud* NewEffect = m_Scene->CreateObject<CEffect_LandCloud>("LandCloud");
	NewEffect->SetPos(m_Pos);
	NewEffect->SetPivot(0.5f, 1.f);
	NewEffect->AddAnimation("spr_landcloud", false, 0.42f);


	// ���� ����
	m_Scene->GetSceneResource()->SoundPlay("sound_player_land");

	m_AnimationName = "spr_landing_";
	ChangeAnimation(m_AnimationName + m_ChangeDirText);
	m_MoveDir = Vector2{ 0.f, 0.f };
	SetSpeed(0.f);
	m_AttackCount = 0;


}

void CPlayer::AttackStart()
{
	// �õ尪�� ��� ���� random_device ����.
	std::random_device rd;

	// random_device �� ���� ���� ���� ������ �ʱ�ȭ �Ѵ�.
	std::mt19937 gen(rd());

	// 0 ���� 99 ���� �յ��ϰ� ��Ÿ���� �������� �����ϱ� ���� �յ� ���� ����.
	std::uniform_int_distribution<int> IntRange(0, 2);

	int Num = IntRange(gen);

	// ���� ���� ���� ���
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

	//	// ���� ����Ʈ
	//	Effect_Slash* NewEffect = GetLevel()->CreateActor<Effect_Slash>((int)ORDER::Effect);
	//NewEffect->SetPosition(GetPosition());

	// ���� ������ ���콺 ���� ����
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

	// �÷��̾�->���콺 ���� ���� ȹ��
	Vector2 AttackDir = CInput::GetInst()->GetMouseWorldPos() - (m_Pos + Vector2{0,-35});
	AttackDir.Normalize();

	// ���� ������ ���ݹ��� ����.
	g_AttackDir = AttackDir;

	//// �������� �ݸ��� ����
	//PlayerAttackCollision_ = CreateCollision("PlayerAttack", { 76, 76 }, AttackDir * 66 + float4{ 0,-35 });

	m_MoveDir = Vector2{ 0.f, 0.f };
	// ���߿��� ���� �ѹ��� �����϶��� y�� �������� �ο��Ѵ�.
	if (m_AttackCount <= 0)
	{
		m_MoveDir = AttackDir * 480.f;
		++m_AttackCount;
	}
	else if (m_AttackCount >= 1)
	{
		// �÷��̾�� 2ȸ �������� y�� �̵� ����, ���� ���� ���� ������
		if (AttackDir.y < 0)
		{
			m_MoveDir = Vector2{ AttackDir.x, 0 } *480.f;
		}
		else
		{
			m_MoveDir = Vector2{ AttackDir.x, AttackDir.y } *480.f;
		}
	}
	m_Gravity = 10.f;	// ���� �� �߷� �ʱ�ȭ

}

void CPlayer::FallStart()
{
	m_AnimationName = "spr_fall_";
	ChangeAnimation(m_AnimationName + m_ChangeDirText);
}

void CPlayer::DodgeStart()
{

	// ���� ����
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

}

void CPlayer::PlaySongStart()
{
}

void CPlayer::MapCollisionCheckMoveGround()
{
	{
		// �̷��� ��ġ�� ����Ͽ� �װ��� RGB���� üũ�ϰ�, �̵� ������ ���̸� �̵��Ѵ�.
		Vector2 NextPos = m_Pos + (Vector2{ 0,m_MoveDir.y } * DELTA_TIME * m_MoveSpeed);
		Vector2 CheckPos = NextPos + Vector2{ 0,0 };	// �̷� ��ġ�� �߱��� ����
		Vector2 CheckPosTopRight = NextPos + Vector2{ 18,-80 };	// �̷� ��ġ�� �Ӹ����� ����
		Vector2 CheckPosTopLeft = NextPos + Vector2{ -18,-80 };	// �̷� ��ġ�� �Ӹ����� ����

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
		// �̷��� ��ġ�� ����Ͽ� �װ��� RGB���� üũ�ϰ�, �̵� ������ ���̸� �̵��Ѵ�.
		Vector2 NextPos = m_Pos + (Vector2{ m_MoveDir.x,0 } * DELTA_TIME * m_MoveSpeed);
		Vector2 CheckPos = NextPos + Vector2{ 0,0 };	// �̷� ��ġ�� �߱��� ����
		Vector2 CheckPosTopRight = NextPos + Vector2{ 18,-80 };	// �̷� ��ġ�� �Ӹ����� ����
		Vector2 CheckPosTopLeft = NextPos + Vector2{ -18,-80 };	// �̷� ��ġ�� �Ӹ����� ����
		Vector2 ForDownPos = m_Pos + Vector2{ 0,1.f };	// �� �Ʒ� ����

		int CurColor = m_MapColTexture->GetImagePixel(m_Pos);
		int ForDownColor = m_MapColTexture->GetImagePixel(ForDownPos);
		int Color = m_MapColTexture->GetImagePixel(CheckPos);
		int TopRightColor = m_MapColTexture->GetImagePixel(CheckPosTopRight);
		int TopLeftColor = m_MapColTexture->GetImagePixel(CheckPosTopLeft);


		// �׻� ���� �پ��ֱ�
		if (RGB(0, 0, 0) != ForDownColor && RGB(255, 0, 0) != ForDownColor)
		{
			SetPos(Vector2{ m_Pos.x, m_Pos.y + 1.5f });
		}

		// ��� �ö󰡱�
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
		// �̷��� ��ġ�� ����Ͽ� �װ��� RGB���� üũ�ϰ�, �̵� ������ ���̸� �̵��Ѵ�.
		Vector2 NextPos = m_Pos + (Vector2{ 0,m_MoveDir.y } * DELTA_TIME);
		Vector2 CheckPos = NextPos + Vector2{ 0,0 };	// �̷� ��ġ�� �߱��� ����
		Vector2 CheckPosTopRight = NextPos + Vector2{ 18,-80 };	// �̷� ��ġ�� �Ӹ����� ����
		Vector2 CheckPosTopLeft = NextPos + Vector2{ -18,-80 };	// �̷� ��ġ�� �Ӹ����� ����

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
		// �̷��� ��ġ�� ����Ͽ� �װ��� RGB���� üũ�ϰ�, �̵� ������ ���̸� �̵��Ѵ�.
		Vector2 NextPos = m_Pos + (Vector2{ m_MoveDir.x,0.f } * DELTA_TIME);
		Vector2 CheckPos = NextPos + Vector2{ 0.f, 0.f };	// �̷� ��ġ�� �߱��� ����
		Vector2 CheckPosTopRight = NextPos + Vector2{ 18,-80 };	// �̷� ��ġ�� �Ӹ����� ����
		Vector2 CheckPosTopLeft = NextPos + Vector2{ -18,-80 };	// �̷� ��ġ�� �Ӹ����� ����

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


void CPlayer::RunningSound()
{
	m_Scene->GetSceneResource()->SoundPlay("sound_player_running_2");

}