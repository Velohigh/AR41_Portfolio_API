
#include "Stage_1.h"
#include "../GameObject/Player.h"
#include "../GameObject/Monster.h"
#include "../GameObject/BackObj.h"
#include "SceneResource.h"
#include "Camera.h"
#include "../Input.h"
#include "../Widget/CharacterHUD.h"
#include "../GameObject/TileMap.h"
#include "../Resource/ResourceManager.h"
#include "../GameObject/Grunt.h"
#include "../GameObject/Gangster.h"
#include "../Resource/Texture/Texture.h"

CStage_1::CStage_1()	:
	Back(nullptr)
{
}

CStage_1::~CStage_1()
{
}

bool CStage_1::Init()
{
	CScene::Init();

	CreateAnimationSequence();

	GetSceneResource()->LoadSound("BGM", "song_youwillneverknow", true, "song_youwillneverknow.ogg");
	GetSceneResource()->LoadSound("Effect", "sound_enemy_bloodsplat1", false, "sound_enemy_bloodsplat1.wav");
	GetSceneResource()->LoadSound("Effect", "sound_enemy_bloodsplat2", false, "sound_enemy_bloodsplat2.wav");
	GetSceneResource()->LoadSound("Effect", "sound_enemy_bloodsplat3", false, "sound_enemy_bloodsplat3.wav");
	GetSceneResource()->LoadSound("Effect", "sound_enemy_bloodsplat4", false, "sound_enemy_bloodsplat4.wav");
	GetSceneResource()->SetVolume(100);

	GetCamera()->SetResolution(1280.f, 720.f);
	GetCamera()->SetWorldResolution(1800.f, 784.f);
	GetCamera()->SetTargetPivot(0.5f, 0.5f);

	Back = CreateObject<CBackObj>("BackObj");
	Back->SetTexture("room_factory_2", TEXT("room_factory_2.bmp"), "MapPath");


	// 플레이어
	CPlayer* Player = CreateObject<CPlayer>("Player");
	Player->SetPos({ 230.f, 671.f });
	Player->StateChange(PlayerState::PlaySong);

	SetPlayer(Player);
	GetCamera()->SetTarget(Player);


	{
	// 그런트
		CGrunt* NewGrunt = CreateObject<CGrunt>("Grunt");
		NewGrunt->SetPos({ 1054.f, 383.f });
		NewGrunt->SetDir(ObjDir::Right);
		NewGrunt->SetState(ObjState::Walk);
		NewGrunt->SetPatrol(true);
		NewGrunt = CreateObject<CGrunt>("Grunt");
		NewGrunt->SetPos({ 338, 383 });
		NewGrunt->SetDir(ObjDir::Right);

		//NewGrunt->SetPosition({ 913, 505 });
		NewGrunt = CreateObject<CGrunt>("Grunt");
		NewGrunt->SetPos({ 530, 671 });
		NewGrunt = CreateObject<CGrunt>("Grunt");
		NewGrunt->SetPos({ 338, 671 });

		// 갱스터
		CGangster* NewGangster = CreateObject<CGangster>("Gangster");
		NewGangster->SetPos({ 545, 383 });
		NewGangster->SetDir(ObjDir::Left);
		NewGangster->SetState(ObjState::Idle);

	}


	//CreateWidgetWindow<CCharacterHUD>("CharacterHUD");

	return true;
}

void CStage_1::Update(float DeltaTime)
{
	CScene::Update(DeltaTime);

	if (m_BgmOn == true)
	{
		m_BgmOn = !m_BgmOn;

		GetSceneResource()->SoundPlay("song_youwillneverknow");
	}

}

void CStage_1::CreateAnimationSequence()
{
	// ## Grunt Animation ##
	// Grunt Idle_Left
	{
		std::vector<std::wstring>	vecFileName;

		for (int i = 0; i <= 7; ++i)
		{
			TCHAR	FileName[MAX_PATH] = {};
			// %d에 i의 값이 대입되어 문자열이 만들어지게 된다.
			wsprintf(FileName, TEXT("Enemy/spr_grunt_idle_left/%d.bmp"), i);
			vecFileName.push_back(FileName);
		}

		CResourceManager::GetInst()->CreateAnimationSequence("spr_grunt_idle_left",
			"spr_grunt_idle_left", vecFileName, TEXTURE_PATH);

		for (int i = 0; i <= 7; ++i)
		{
			CResourceManager::GetInst()->AddAnimationFrame("spr_grunt_idle_left", 0.f, 0.f,
				30.f, 36.f);
		}

		CResourceManager::GetInst()->SetColorKey("spr_grunt_idle_left", 255, 255, 255);
	}

	// Grunt Idle_Right
	{
		std::vector<std::wstring>	vecFileName;

		for (int i = 0; i <= 7; ++i)
		{
			TCHAR	FileName[MAX_PATH] = {};
			// %d에 i의 값이 대입되어 문자열이 만들어지게 된다.
			wsprintf(FileName, TEXT("Enemy/spr_grunt_idle_right/%d.bmp"), i);
			vecFileName.push_back(FileName);
		}

		CResourceManager::GetInst()->CreateAnimationSequence("spr_grunt_idle_right",
			"spr_grunt_idle_right", vecFileName, TEXTURE_PATH);

		for (int i = 0; i <= 7; ++i)
		{
			CResourceManager::GetInst()->AddAnimationFrame("spr_grunt_idle_right", 0.f, 0.f,
				30.f, 36.f);
		}

		CResourceManager::GetInst()->SetColorKey("spr_grunt_idle_right", 255, 255, 255);
	}

	// Grunt Run_Left
	{
		std::vector<std::wstring>	vecFileName;

		for (int i = 0; i <= 9; ++i)
		{
			TCHAR	FileName[MAX_PATH] = {};
			// %d에 i의 값이 대입되어 문자열이 만들어지게 된다.
			wsprintf(FileName, TEXT("Enemy/spr_grunt_run_left/%d.bmp"), i);
			vecFileName.push_back(FileName);
		}

		CResourceManager::GetInst()->CreateAnimationSequence("spr_grunt_run_left",
			"spr_grunt_run_left", vecFileName, TEXTURE_PATH);

		for (int i = 0; i <= 9; ++i)
		{
			CResourceManager::GetInst()->AddAnimationFrame("spr_grunt_run_left", 0.f, 0.f,
				36.f, 39.f);
		}

		CResourceManager::GetInst()->SetColorKey("spr_grunt_run_left", 255, 255, 255);
	}

	// Grunt Run_Right
	{
		std::vector<std::wstring>	vecFileName;

		for (int i = 0; i <= 9; ++i)
		{
			TCHAR	FileName[MAX_PATH] = {};
			// %d에 i의 값이 대입되어 문자열이 만들어지게 된다.
			wsprintf(FileName, TEXT("Enemy/spr_grunt_run_right/%d.bmp"), i);
			vecFileName.push_back(FileName);
		}

		CResourceManager::GetInst()->CreateAnimationSequence("spr_grunt_run_right",
			"spr_grunt_run_right", vecFileName, TEXTURE_PATH);

		for (int i = 0; i <= 9; ++i)
		{
			CResourceManager::GetInst()->AddAnimationFrame("spr_grunt_run_right", 0.f, 0.f,
				36.f, 39.f);
		}

		CResourceManager::GetInst()->SetColorKey("spr_grunt_run_right", 255, 255, 255);
	}

	// Grunt Turn_Left
	{
		std::vector<std::wstring>	vecFileName;

		for (int i = 0; i <= 7; ++i)
		{
			TCHAR	FileName[MAX_PATH] = {};
			// %d에 i의 값이 대입되어 문자열이 만들어지게 된다.
			wsprintf(FileName, TEXT("Enemy/spr_grunt_turn_left/%d.bmp"), i);
			vecFileName.push_back(FileName);
		}

		CResourceManager::GetInst()->CreateAnimationSequence("spr_grunt_turn_left",
			"spr_grunt_turn_left", vecFileName, TEXTURE_PATH);

		for (int i = 0; i <= 7; ++i)
		{
			CResourceManager::GetInst()->AddAnimationFrame("spr_grunt_turn_left", 0.f, 0.f,
				36.f, 35.f);
		}

		CResourceManager::GetInst()->SetColorKey("spr_grunt_turn_left", 255, 255, 255);
	}

	// Grunt Turn_Right
	{
		std::vector<std::wstring>	vecFileName;

		for (int i = 0; i <= 7; ++i)
		{
			TCHAR	FileName[MAX_PATH] = {};
			// %d에 i의 값이 대입되어 문자열이 만들어지게 된다.
			wsprintf(FileName, TEXT("Enemy/spr_grunt_turn_right/%d.bmp"), i);
			vecFileName.push_back(FileName);
		}

		CResourceManager::GetInst()->CreateAnimationSequence("spr_grunt_turn_right",
			"spr_grunt_turn_right", vecFileName, TEXTURE_PATH);

		for (int i = 0; i <= 7; ++i)
		{
			CResourceManager::GetInst()->AddAnimationFrame("spr_grunt_turn_right", 0.f, 0.f,
				36.f, 35.f);
		}

		CResourceManager::GetInst()->SetColorKey("spr_grunt_turn_right", 255, 255, 255);
	}

	// Grunt Walk_Left
	{
		std::vector<std::wstring>	vecFileName;

		for (int i = 0; i <= 9; ++i)
		{
			TCHAR	FileName[MAX_PATH] = {};
			// %d에 i의 값이 대입되어 문자열이 만들어지게 된다.
			wsprintf(FileName, TEXT("Enemy/spr_grunt_walk_left/%d.bmp"), i);
			vecFileName.push_back(FileName);
		}

		CResourceManager::GetInst()->CreateAnimationSequence("spr_grunt_walk_left",
			"spr_grunt_walk_left", vecFileName, TEXTURE_PATH);

		for (int i = 0; i <= 9; ++i)
		{
			CResourceManager::GetInst()->AddAnimationFrame("spr_grunt_walk_left", 0.f, 0.f,
				32.f, 40.f);
		}

		CResourceManager::GetInst()->SetColorKey("spr_grunt_walk_left", 255, 255, 255);
	}

	// Grunt Walk_Right
	{
		std::vector<std::wstring>	vecFileName;

		for (int i = 0; i <= 9; ++i)
		{
			TCHAR	FileName[MAX_PATH] = {};
			// %d에 i의 값이 대입되어 문자열이 만들어지게 된다.
			wsprintf(FileName, TEXT("Enemy/spr_grunt_walk_right/%d.bmp"), i);
			vecFileName.push_back(FileName);
		}

		CResourceManager::GetInst()->CreateAnimationSequence("spr_grunt_walk_right",
			"spr_grunt_walk_right", vecFileName, TEXTURE_PATH);

		for (int i = 0; i <= 9; ++i)
		{
			CResourceManager::GetInst()->AddAnimationFrame("spr_grunt_walk_right", 0.f, 0.f,
				32.f, 40.f);
		}

		CResourceManager::GetInst()->SetColorKey("spr_grunt_walk_right", 255, 255, 255);
	}

	// Grunt Attack_Left
	{
		std::vector<std::wstring>	vecFileName;

		for (int i = 0; i <= 7; ++i)
		{
			TCHAR	FileName[MAX_PATH] = {};
			// %d에 i의 값이 대입되어 문자열이 만들어지게 된다.
			wsprintf(FileName, TEXT("Enemy/spr_grunt_attack_left/%d.bmp"), i);
			vecFileName.push_back(FileName);
		}

		CResourceManager::GetInst()->CreateAnimationSequence("spr_grunt_attack_left",
			"spr_grunt_attack_left", vecFileName, TEXTURE_PATH);

		for (int i = 0; i <= 7; ++i)
		{
			CResourceManager::GetInst()->AddAnimationFrame("spr_grunt_attack_left", 0.f, 0.f,
				44.f, 42.f);
		}

		CResourceManager::GetInst()->SetColorKey("spr_grunt_attack_left", 255, 255, 255);
	}

	// Grunt Attack_Right
	{
		std::vector<std::wstring>	vecFileName;

		for (int i = 0; i <= 7; ++i)
		{
			TCHAR	FileName[MAX_PATH] = {};
			// %d에 i의 값이 대입되어 문자열이 만들어지게 된다.
			wsprintf(FileName, TEXT("Enemy/spr_grunt_attack_right/%d.bmp"), i);
			vecFileName.push_back(FileName);
		}

		CResourceManager::GetInst()->CreateAnimationSequence("spr_grunt_attack_right",
			"spr_grunt_attack_right", vecFileName, TEXTURE_PATH);

		for (int i = 0; i <= 7; ++i)
		{
			CResourceManager::GetInst()->AddAnimationFrame("spr_grunt_attack_right", 0.f, 0.f,
				44.f, 42.f);
		}

		CResourceManager::GetInst()->SetColorKey("spr_grunt_attack_right", 255, 255, 255);
	}

	// Grunt HurtFly_Left
	{
		std::vector<std::wstring>	vecFileName;

		for (int i = 0; i <= 1; ++i)
		{
			TCHAR	FileName[MAX_PATH] = {};
			// %d에 i의 값이 대입되어 문자열이 만들어지게 된다.
			wsprintf(FileName, TEXT("Enemy/spr_grunt_hurtfly_left/%d.bmp"), i);
			vecFileName.push_back(FileName);
		}

		CResourceManager::GetInst()->CreateAnimationSequence("spr_grunt_hurtfly_left",
			"spr_grunt_hurtfly_left", vecFileName, TEXTURE_PATH);

		for (int i = 0; i <= 1; ++i)
		{
			CResourceManager::GetInst()->AddAnimationFrame("spr_grunt_hurtfly_left", 0.f, 0.f,
				43.f, 37.f);
		}

		CResourceManager::GetInst()->SetColorKey("spr_grunt_hurtfly_left", 255, 255, 255);
	}

	// Grunt HurtFly_Right
	{
		std::vector<std::wstring>	vecFileName;

		for (int i = 0; i <= 1; ++i)
		{
			TCHAR	FileName[MAX_PATH] = {};
			// %d에 i의 값이 대입되어 문자열이 만들어지게 된다.
			wsprintf(FileName, TEXT("Enemy/spr_grunt_hurtfly_right/%d.bmp"), i);
			vecFileName.push_back(FileName);
		}

		CResourceManager::GetInst()->CreateAnimationSequence("spr_grunt_hurtfly_right",
			"spr_grunt_hurtfly_right", vecFileName, TEXTURE_PATH);

		for (int i = 0; i <= 1; ++i)
		{
			CResourceManager::GetInst()->AddAnimationFrame("spr_grunt_hurtfly_right", 0.f, 0.f,
				43.f, 37.f);
		}

		CResourceManager::GetInst()->SetColorKey("spr_grunt_hurtfly_right", 255, 255, 255);
	}

	// Grunt HurtGround_Left
	{
		std::vector<std::wstring>	vecFileName;

		for (int i = 0; i <= 15; ++i)
		{
			TCHAR	FileName[MAX_PATH] = {};
			// %d에 i의 값이 대입되어 문자열이 만들어지게 된다.
			wsprintf(FileName, TEXT("Enemy/spr_grunt_hurtground_left/%d.bmp"), i);
			vecFileName.push_back(FileName);
		}

		CResourceManager::GetInst()->CreateAnimationSequence("spr_grunt_hurtground_left",
			"spr_grunt_hurtground_left", vecFileName, TEXTURE_PATH);

		for (int i = 0; i <= 15; ++i)
		{
			CResourceManager::GetInst()->AddAnimationFrame("spr_grunt_hurtground_left", 0.f, 0.f,
				56.f, 41.f);
		}

		CResourceManager::GetInst()->SetColorKey("spr_grunt_hurtground_left", 255, 255, 255);
	}

	// Grunt HurtGround_Right
	{
		std::vector<std::wstring>	vecFileName;

		for (int i = 0; i <= 15; ++i)
		{
			TCHAR	FileName[MAX_PATH] = {};
			// %d에 i의 값이 대입되어 문자열이 만들어지게 된다.
			wsprintf(FileName, TEXT("Enemy/spr_grunt_hurtground_right/%d.bmp"), i);
			vecFileName.push_back(FileName);
		}

		CResourceManager::GetInst()->CreateAnimationSequence("spr_grunt_hurtground_right",
			"spr_grunt_hurtground_right", vecFileName, TEXTURE_PATH);

		for (int i = 0; i <= 15; ++i)
		{
			CResourceManager::GetInst()->AddAnimationFrame("spr_grunt_hurtground_right", 0.f, 0.f,
				56.f, 41.f);
		}

		CResourceManager::GetInst()->SetColorKey("spr_grunt_hurtground_right", 255, 255, 255);
	}


	// Gangster Idle_Left
	{
		std::vector<std::wstring>	vecFileName;

		for (int i = 0; i <= 7; ++i)
		{
			TCHAR	FileName[MAX_PATH] = {};
			// %d에 i의 값이 대입되어 문자열이 만들어지게 된다.
			wsprintf(FileName, TEXT("Enemy/spr_gangster_idle_left/%d.bmp"), i);
			vecFileName.push_back(FileName);
		}

		CResourceManager::GetInst()->CreateAnimationSequence("spr_gangster_idle_left",
			"spr_gangster_idle_left", vecFileName, TEXTURE_PATH);

		for (int i = 0; i <= 7; ++i)
		{
			CTexture* Texture = CResourceManager::GetInst()->FindTexture("spr_gangster_idle_left");
			int NewWidth = Texture->GetWidth(i);
			int NewHeight = Texture->GetHeight(i);


			CResourceManager::GetInst()->AddAnimationFrame("spr_gangster_idle_left", 0.f, 0.f,
				(float)NewWidth, (float)NewHeight);
		}

		CResourceManager::GetInst()->SetColorKey("spr_gangster_idle_left", 255, 255, 255);
	}

	// Gangster Idle_Right
	{
		std::vector<std::wstring>	vecFileName;

		for (int i = 0; i <= 7; ++i)
		{
			TCHAR	FileName[MAX_PATH] = {};
			// %d에 i의 값이 대입되어 문자열이 만들어지게 된다.
			wsprintf(FileName, TEXT("Enemy/spr_gangster_idle_right/%d.bmp"), i);
			vecFileName.push_back(FileName);
		}

		CResourceManager::GetInst()->CreateAnimationSequence("spr_gangster_idle_right",
			"spr_gangster_idle_right", vecFileName, TEXTURE_PATH);

		for (int i = 0; i <= 7; ++i)
		{
			CTexture* Texture = CResourceManager::GetInst()->FindTexture("spr_gangster_idle_right");
			int NewWidth = Texture->GetWidth(i);
			int NewHeight = Texture->GetHeight(i);


			CResourceManager::GetInst()->AddAnimationFrame("spr_gangster_idle_right", 0.f, 0.f,
				(float)NewWidth, (float)NewHeight);
		}

		CResourceManager::GetInst()->SetColorKey("spr_gangster_idle_right", 255, 255, 255);
	}



	// ## EFFECT
	// BloodAnimation_Left 한장짜리 이미지 방식
	GetSceneResource()->CreateAnimationSequence("effect_bloodanimation_left",
		"effect_bloodanimation_left", TEXT("Effect/effect_bloodanimation_left.bmp"), TEXTURE_PATH);

	for (int i = 0; i < 5; ++i)
	{
		GetSceneResource()->AddAnimationFrame("effect_bloodanimation_left", 80.f * i, 0.f,
			80.f, 79.f);
	}

	GetSceneResource()->SetColorKey("effect_bloodanimation_left", 255, 0, 255);


	// BloodAnimation_Right 한장짜리 이미지 방식
	GetSceneResource()->CreateAnimationSequence("effect_bloodanimation_right",
		"effect_bloodanimation_right", TEXT("Effect/effect_bloodanimation_right.bmp"), TEXTURE_PATH);

	for (int i = 0; i < 5; ++i)
	{
		GetSceneResource()->AddAnimationFrame("effect_bloodanimation_right", 80.f * i, 0.f,
			80.f, 79.f);
	}

	GetSceneResource()->SetColorKey("effect_bloodanimation_right", 255, 0, 255);


	// BloodAnimation2_Left 한장짜리 이미지 방식
	GetSceneResource()->CreateAnimationSequence("effect_bloodanimation2_left",
		"effect_bloodanimation2_left", TEXT("Effect/effect_bloodanimation2_left.bmp"), TEXTURE_PATH);

	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrame("effect_bloodanimation2_left", 80.f * i, 0.f,
			80.f, 79.f);
	}

	GetSceneResource()->SetColorKey("effect_bloodanimation2_left", 255, 0, 255);

	// BloodAnimation2_Right 한장짜리 이미지 방식
	GetSceneResource()->CreateAnimationSequence("effect_bloodanimation2_right",
		"effect_bloodanimation2_right", TEXT("Effect/effect_bloodanimation2_right.bmp"), TEXTURE_PATH);

	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrame("effect_bloodanimation2_right", 80.f * i, 0.f,
			80.f, 79.f);
	}

	GetSceneResource()->SetColorKey("effect_bloodanimation2_right", 255, 0, 255);


}

