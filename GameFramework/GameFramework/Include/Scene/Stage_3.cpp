
#include "Stage_3.h"
#include "Stage_1.h"
#include "../GameObject/Player.h"
#include "../GameObject/Monster.h"
#include "../GameObject/BackObj.h"
#include "SceneResource.h"
#include "SceneManager.h"
#include "Camera.h"
#include "../Input.h"
#include "../Widget/CharacterHUD.h"
#include "../GameObject/TileMap.h"
#include "../Resource/ResourceManager.h"
#include "../GameObject/Grunt.h"
#include "../GameObject/Gangster.h"
#include "../GameObject/Pomp.h"
#include "../GameObject/Cursor.h"
#include "../Resource/Texture/Texture.h"
#include "../GameObject/Effect.h"
#include "../Resource/ResourceManager.h"
#include "../Resource/Animation/AnimationManager.h"

bool g_3BgmOn = false;

CStage_3::CStage_3() :
	Back(nullptr)
{
}

CStage_3::~CStage_3()
{
}

bool CStage_3::Init()
{
	CScene::Init();

	CreateAnimationSequencePlayer();
	CreateAnimationSequencePlayer2();
	CreateAnimationSequenceGrunt();
	CreateAnimationSequenceGangster();
	CreateAnimationSequenceEffect_Frame();
	CreateAnimationSequenceEffect_Sprite();

	GetSceneResource()->LoadSound("BGM", "song_sneaky_driver", true, "song_sneaky_driver.ogg");
	GetSceneResource()->LoadSound("Effect", "sound_enemy_bloodsplat1", false, "sound_enemy_bloodsplat1.wav");
	GetSceneResource()->LoadSound("Effect", "sound_enemy_bloodsplat2", false, "sound_enemy_bloodsplat2.wav");
	GetSceneResource()->LoadSound("Effect", "sound_enemy_bloodsplat3", false, "sound_enemy_bloodsplat3.wav");
	GetSceneResource()->LoadSound("Effect", "sound_enemy_bloodsplat4", false, "sound_enemy_bloodsplat4.wav");
	GetSceneResource()->SetVolume(100);
	GetSceneResource()->LoadSound("Effect", "fire", false, "fire.wav");
	GetSceneResource()->LoadSound("Effect", "swing", false, "swing.wav");
	GetSceneResource()->LoadSound("Effect", "punch", false, "punch.wav");
	GetSceneResource()->LoadSound("Effect", "death_bullet", false, "death_bullet.wav");
	GetSceneResource()->LoadSound("Effect", "death_sword1", false, "death_sword1.wav");
	GetSceneResource()->LoadSound("Effect", "death_sword2", false, "death_sword2.wav");
	GetSceneResource()->LoadSound("Effect", "swordcrash", false, "swordcrash.wav");
	GetSceneResource()->LoadSound("Effect", "reflect", false, "reflect.wav");
	GetSceneResource()->LoadSound("Effect", "walljump", false, "walljump.wav");
	GetSceneResource()->LoadSound("Effect", "grabwall", false, "grabwall.wav");
	GetSceneResource()->LoadSound("Effect", "dead", false, "dead.wav");
	GetSceneResource()->LoadSound("Effect", "go", false, "go.wav");

	GetSceneResource()->SoundStop("song_youwillneverknow");
	GetSceneResource()->SoundStop("bgm_bunker");


	GetCamera()->SetResolution(1280.f, 720.f);
	GetCamera()->SetWorldResolution(4288.f, 1200.f);
	GetCamera()->SetTargetPivot(0.5f, 0.5f);

	Back = CreateObject<CBackObj>("BackObj");
	Back->SetTexture("stage3_bg_render", TEXT("stage3_bg_render.bmp"), "MapPath");

	auto iter = m_ObjList[(int)ERender_Layer::Default].begin();
	auto iterEnd = m_ObjList[(int)ERender_Layer::Default].end();

	// ¸¶¿ì½º
	CCursor* Cursor = CreateObject<CCursor>("Cursor");
	Cursor->SetPos(CInput::GetInst()->GetMouseWorldPos());
	Cursor->SetColorKey(255, 0, 255);

	// ÇÃ·¹ÀÌ¾î
	CPlayer* Player = CreateObject<CPlayer>("Player");
	Player->SetPos({ 60.f, 755.f });
	Player->StateChange(PlayerState::Idle);
	Player->SetMapTexture("stage3_bg_collision", TEXT("stage3_bg_collision.bmp"), "MapPath");

	SetPlayer(Player);
	GetCamera()->SetTarget(Player);


	{
		// ±×·±Æ®
		CGrunt* NewGrunt = CreateObject<CGrunt>("Grunt");	// ÁÂ 2Ãþ ÁÂÃø
		NewGrunt->SetPos({ 611, 387.f });
		NewGrunt->SetDir(ObjDir::Right);
		NewGrunt->SetState(ObjState::Idle);
		NewGrunt->SetPatrol(false);
		NewGrunt->SetPatrolTime(3.f);
		NewGrunt->SetMapTexture("stage3_bg_collision", TEXT("stage3_bg_collision.bmp"), "MapPath");

		NewGrunt = CreateObject<CGrunt>("Grunt");	// ÁÂ 2Ãþ »¡°£¶¥
		NewGrunt->SetPos({ 737, 387.f });
		NewGrunt->SetDir(ObjDir::Left);
		NewGrunt->SetState(ObjState::Idle);
		NewGrunt->SetPatrol(false);
		NewGrunt->SetPatrolTime(3.f);
		NewGrunt->SetMapTexture("stage3_bg_collision", TEXT("stage3_bg_collision.bmp"), "MapPath");

		NewGrunt = CreateObject<CGrunt>("Grunt");	// Áß¾Ó Á¤Âû
		NewGrunt->SetPos({ 2272, 515 });
		NewGrunt->SetDir(ObjDir::Right);
		NewGrunt->SetState(ObjState::Walk);
		NewGrunt->SetPatrol(true);
		NewGrunt->SetPatrolTime(3.f);
		NewGrunt->SetMapTexture("stage3_bg_collision", TEXT("stage3_bg_collision.bmp"), "MapPath");

		NewGrunt = CreateObject<CGrunt>("Grunt");	// Áß¾Ó ¿ìÃø
		NewGrunt->SetPos({ 3422, 515 });
		NewGrunt->SetDir(ObjDir::Left);
		NewGrunt->SetState(ObjState::Idle);
		NewGrunt->SetMapTexture("stage3_bg_collision", TEXT("stage3_bg_collision.bmp"), "MapPath");

		NewGrunt = CreateObject<CGrunt>("Grunt");	// ÁÂ 1Ãþ
		NewGrunt->SetPos({ 1155, 771 });
		NewGrunt->SetDir(ObjDir::Right);
		NewGrunt->SetState(ObjState::Idle);
		NewGrunt->SetMapTexture("stage3_bg_collision", TEXT("stage3_bg_collision.bmp"), "MapPath");

		NewGrunt = CreateObject<CGrunt>("Grunt");	// ÁÂ 1Ãþ
		NewGrunt->SetPos({ 3110, 771 });
		NewGrunt->SetDir(ObjDir::Right);
		NewGrunt->SetState(ObjState::Walk);
		NewGrunt->SetPatrol(true);
		NewGrunt->SetPatrolTime(3.f);
		NewGrunt->SetMapTexture("stage3_bg_collision", TEXT("stage3_bg_collision.bmp"), "MapPath");




		// °»½ºÅÍ
		CGangster* NewGangster = CreateObject<CGangster>("Gangster");	// ÁÂ 2Ãþ ¿ìÃø³¡
		NewGangster->SetPos({ 1483, 387.f });
		NewGangster->SetDir(ObjDir::Left);
		NewGangster->SetState(ObjState::Idle);
		NewGangster->SetMapTexture("stage3_bg_collision", TEXT("stage3_bg_collision.bmp"), "MapPath");

		NewGangster = CreateObject<CGangster>("Gangster");	// Áß¾Ó ÁÂÃø³¡
		NewGangster->SetPos({ 1840, 515.f });
		NewGangster->SetDir(ObjDir::Right);
		NewGangster->SetState(ObjState::Idle);
		NewGangster->SetMapTexture("stage3_bg_collision", TEXT("stage3_bg_collision.bmp"), "MapPath");

		NewGangster = CreateObject<CGangster>("Gangster");	// Áß¾Ó Á¤Âû
		NewGangster->SetPos({ 2788, 515.f });
		NewGangster->SetDir(ObjDir::Left);
		NewGangster->SetState(ObjState::Walk);
		NewGangster->SetPatrol(true);
		NewGangster->SetPatrolTime(3.f);
		NewGangster->SetMapTexture("stage3_bg_collision", TEXT("stage3_bg_collision.bmp"), "MapPath");
		
		NewGangster = CreateObject<CGangster>("Gangster");	// Áß¾Ó Á¤Âû
		NewGangster->SetPos({ 3567, 515.f });
		NewGangster->SetDir(ObjDir::Left);
		NewGangster->SetState(ObjState::Walk);
		NewGangster->SetPatrol(true);
		NewGangster->SetPatrolTime(3.f);
		NewGangster->SetMapTexture("stage3_bg_collision", TEXT("stage3_bg_collision.bmp"), "MapPath");

		NewGangster = CreateObject<CGangster>("Gangster");	// Áß¾Ó ¿ìÃø ³¡
		NewGangster->SetPos({ 3684, 515.f });
		NewGangster->SetDir(ObjDir::Left);
		NewGangster->SetState(ObjState::Idle);
		NewGangster->SetMapTexture("stage3_bg_collision", TEXT("stage3_bg_collision.bmp"), "MapPath");

		NewGangster = CreateObject<CGangster>("Gangster");	// ÁÂ 1Ãþ ¿ìÃø ³¡
		NewGangster->SetPos({ 1600, 771.f });
		NewGangster->SetDir(ObjDir::Left);
		NewGangster->SetState(ObjState::Idle);
		NewGangster->SetMapTexture("stage3_bg_collision", TEXT("stage3_bg_collision.bmp"), "MapPath");

		NewGangster = CreateObject<CGangster>("Gangster");	// ¿ì 1Ãþ ¿ìÃø ³¡
		NewGangster->SetPos({ 4000, 771.f });
		NewGangster->SetDir(ObjDir::Left);
		NewGangster->SetState(ObjState::Idle);
		NewGangster->SetMapTexture("stage3_bg_collision", TEXT("stage3_bg_collision.bmp"), "MapPath");

		NewGangster = CreateObject<CGangster>("Gangster");	// ¿ì 1Ãþ
		NewGangster->SetPos({ 3425, 771 });
		NewGangster->SetDir(ObjDir::Left);
		NewGangster->SetState(ObjState::Idle);
		NewGangster->SetMapTexture("stage3_bg_collision", TEXT("stage3_bg_collision.bmp"), "MapPath");

		
		// ÆûÇÁ
		CPomp* NewPomp = CreateObject<CPomp>("Pomp");	// ÁÂ 2Ãþ
		NewPomp->SetPos({ 1420, 387.f });
		NewPomp->SetDir(ObjDir::Left);
		NewPomp->SetState(ObjState::Walk);
		NewPomp->SetPatrol(true);
		NewPomp->SetPatrolTime(3.f);
		NewPomp->SetMapTexture("stage3_bg_collision", TEXT("stage3_bg_collision.bmp"), "MapPath");

		NewPomp = CreateObject<CPomp>("Pomp");	// Áß¾Ó 2Ãþ
		NewPomp->SetPos({ 3220, 515.f });
		NewPomp->SetDir(ObjDir::Left);
		NewPomp->SetState(ObjState::Idle);
		NewPomp->SetPatrol(false);
		NewPomp->SetMapTexture("stage3_bg_collision", TEXT("stage3_bg_collision.bmp"), "MapPath");

		NewPomp = CreateObject<CPomp>("Pomp");	// ÁÂ 1Ãþ Á¤Âû
		NewPomp->SetPos({ 1530, 771.f });
		NewPomp->SetDir(ObjDir::Left);
		NewPomp->SetState(ObjState::Walk);
		NewPomp->SetPatrol(true);
		NewPomp->SetMapTexture("stage3_bg_collision", TEXT("stage3_bg_collision.bmp"), "MapPath");

		NewPomp = CreateObject<CPomp>("Pomp");	// ¿ì 1Ãþ Áß¾Ó
		NewPomp->SetPos({ 3645, 771.f });
		NewPomp->SetDir(ObjDir::Right);
		NewPomp->SetState(ObjState::Idle);
		NewPomp->SetPatrol(false);
		NewPomp->SetMapTexture("stage3_bg_collision", TEXT("stage3_bg_collision.bmp"), "MapPath");

		NewPomp = CreateObject<CPomp>("Pomp");	// ¿ì 1Ãþ Áß¾Ó
		NewPomp->SetPos({ 3710, 771.f });
		NewPomp->SetDir(ObjDir::Left);
		NewPomp->SetState(ObjState::Idle);
		NewPomp->SetPatrol(false);
		NewPomp->SetMapTexture("stage3_bg_collision", TEXT("stage3_bg_collision.bmp"), "MapPath");

		// 2848 546 ÀÌº¥Æ® 
	}


	CreateWidgetWindow<CCharacterHUD>("CharacterHUD");

	m_BgmOn = true;

	SetCameraShakeOn(true);

	return true;
}

void CStage_3::Update(float DeltaTime)
{
	CScene::Update(DeltaTime);

	if (g_3BgmOn == false &&
		m_BgmOn == true)
	{
		m_BgmOn = !m_BgmOn;
		g_3BgmOn = true;

		GetSceneResource()->SoundPlay("song_sneaky_driver");
	}

	//if (true == CInput::GetInst()->IsDown('1'))
	//{
	//	CInput::GetInst()->ClearCallback();
	//	CSceneManager::GetInst()->CreateScene<CStage_1>();
	//}

	if (true == CInput::GetInst()->IsDown('R'))
	{
		SetCameraShakeOn(true);
		//GetSceneResource()->SoundStop("song_sneaky_driver");

		GetSceneResource()->SoundPlay("go");

		CInput::GetInst()->ClearCallback();
		CSceneManager::GetInst()->CreateScene<CStage_3>();
	}



}

void CStage_3::SetSlowMap()
{
	Back->SetTexture("stage3_bg_render_slow", TEXT("stage3_bg_render_slow.bmp"), "MapPath");
}

void CStage_3::SetNormalMap()
{
	Back->SetTexture("stage3_bg_render", TEXT("stage3_bg_render.bmp"), "MapPath");
}

void CStage_3::CreateAnimationSequencePlayer()
{
	// Idle_Left
	CResourceManager::GetInst()->CreateAnimationSequence("spr_idle_left",
		"spr_idle_left", nullptr, TEXTURE_PATH);

	// Idle_Right
	CResourceManager::GetInst()->CreateAnimationSequence("spr_idle_right",
		"spr_idle_right", nullptr, TEXTURE_PATH);

	// Idle_to_Run_Left
	CResourceManager::GetInst()->CreateAnimationSequence("spr_idle_to_run_left",
		"spr_idle_to_run_left", nullptr, TEXTURE_PATH);


	// Idle_to_Run_Right
	CResourceManager::GetInst()->CreateAnimationSequence("spr_idle_to_run_right",
		"spr_idle_to_run_right", nullptr, TEXTURE_PATH);


	// Run_Left
	CResourceManager::GetInst()->CreateAnimationSequence("spr_run_left",
		"spr_run_left", nullptr, TEXTURE_PATH);

	// Run_Right
	CResourceManager::GetInst()->CreateAnimationSequence("spr_run_right",
		"spr_run_right", nullptr, TEXTURE_PATH);

	// Run_To_Idle_Left
	CResourceManager::GetInst()->CreateAnimationSequence("spr_run_to_idle_left",
		"spr_run_to_idle_left", nullptr, TEXTURE_PATH);

	// Run_To_Idle_Right
	CResourceManager::GetInst()->CreateAnimationSequence("spr_run_to_idle_right",
		"spr_run_to_idle_right", nullptr, TEXTURE_PATH);

	// spr_jump_left
	CResourceManager::GetInst()->CreateAnimationSequence("spr_jump_left",
		"spr_jump_left", nullptr, TEXTURE_PATH);

	// spr_jump_right
	CResourceManager::GetInst()->CreateAnimationSequence("spr_jump_right",
		"spr_jump_right", nullptr, TEXTURE_PATH);


	// spr_fall_left
	CResourceManager::GetInst()->CreateAnimationSequence("spr_fall_left",
		"spr_fall_left", nullptr, TEXTURE_PATH);

	// spr_fall_right
	CResourceManager::GetInst()->CreateAnimationSequence("spr_fall_right",
		"spr_fall_right", nullptr, TEXTURE_PATH);

	// spr_attack_left
	CResourceManager::GetInst()->CreateAnimationSequence("spr_attack_left",
		"spr_attack_left", nullptr, TEXTURE_PATH);

	// spr_attack_right
	CResourceManager::GetInst()->CreateAnimationSequence("spr_attack_right",
		"spr_attack_right", nullptr, TEXTURE_PATH);

	// spr_landing_left
	CResourceManager::GetInst()->CreateAnimationSequence("spr_landing_left",
		"spr_landing_left", nullptr, TEXTURE_PATH);

	// spr_landing_right
	CResourceManager::GetInst()->CreateAnimationSequence("spr_landing_right",
		"spr_landing_right", nullptr, TEXTURE_PATH);

	// spr_roll_left
	CResourceManager::GetInst()->CreateAnimationSequence("spr_roll_left",
		"spr_roll_left", nullptr, TEXTURE_PATH);

	// spr_roll_right
	CResourceManager::GetInst()->CreateAnimationSequence("spr_roll_right",
		"spr_roll_right", nullptr, TEXTURE_PATH);


	// spr_player_playsong
	CResourceManager::GetInst()->CreateAnimationSequence("spr_player_playsong",
		"spr_player_playsong", nullptr, TEXTURE_PATH);

	// spr_hurtfly_begin_left
	CResourceManager::GetInst()->CreateAnimationSequence("spr_hurtfly_begin_left",
		"spr_hurtfly_begin_left", nullptr, TEXTURE_PATH);

	// spr_hurtfly_begin_right
	CResourceManager::GetInst()->CreateAnimationSequence("spr_hurtfly_begin_right",
		"spr_hurtfly_begin_right", nullptr, TEXTURE_PATH);


	// spr_hurtfly_loop_left
	CResourceManager::GetInst()->CreateAnimationSequence("spr_hurtfly_loop_left",
		"spr_hurtfly_loop_left", nullptr, TEXTURE_PATH);


	// spr_hurtfly_loop_right
	CResourceManager::GetInst()->CreateAnimationSequence("spr_hurtfly_loop_right",
		"spr_hurtfly_loop_right", nullptr, TEXTURE_PATH);


	// spr_hurtground_left
	CResourceManager::GetInst()->CreateAnimationSequence("spr_hurtground_left",
		"spr_hurtground_left", nullptr, TEXTURE_PATH);

	// spr_hurtground_right
	CResourceManager::GetInst()->CreateAnimationSequence("spr_hurtground_right",
		"spr_hurtground_right", nullptr, TEXTURE_PATH);



}

void CStage_3::CreateAnimationSequencePlayer2()
{
	// spr_wallgrab_left
	CResourceManager::GetInst()->CreateAnimationSequence("spr_wallgrab_left",
		"spr_wallgrab_left", nullptr, TEXTURE_PATH);

	// spr_wallgrab_right
	CResourceManager::GetInst()->CreateAnimationSequence("spr_wallgrab_right",
		"spr_wallgrab_right", nullptr, TEXTURE_PATH);

	// spr_player_flip_left
	CResourceManager::GetInst()->CreateAnimationSequence("spr_player_flip_left",
		"spr_player_flip_left", nullptr, TEXTURE_PATH);

	// spr_player_flip_right
	CResourceManager::GetInst()->CreateAnimationSequence("spr_player_flip_right",
		"spr_player_flip_right", nullptr, TEXTURE_PATH);

}

void CStage_3::CreateAnimationSequenceGrunt()
{
	// ## Grunt Animation ##
	// Grunt Idle_Left
	CResourceManager::GetInst()->CreateAnimationSequence("spr_grunt_idle_left",
		"spr_grunt_idle_left", nullptr, TEXTURE_PATH);

	// Grunt Idle_Right
	CResourceManager::GetInst()->CreateAnimationSequence("spr_grunt_idle_right",
		"spr_grunt_idle_right", nullptr, TEXTURE_PATH);


	// Grunt Run_Left
	CResourceManager::GetInst()->CreateAnimationSequence("spr_grunt_run_left",
		"spr_grunt_run_left", nullptr, TEXTURE_PATH);

	// Grunt Run_Right
	CResourceManager::GetInst()->CreateAnimationSequence("spr_grunt_run_right",
		"spr_grunt_run_right", nullptr, TEXTURE_PATH);


	// Grunt Turn_Left
	CResourceManager::GetInst()->CreateAnimationSequence("spr_grunt_turn_left",
		"spr_grunt_turn_left", nullptr, TEXTURE_PATH);


	// Grunt Turn_Right
	CResourceManager::GetInst()->CreateAnimationSequence("spr_grunt_turn_right",
		"spr_grunt_turn_right", nullptr, TEXTURE_PATH);


	// Grunt Walk_Left
	CResourceManager::GetInst()->CreateAnimationSequence("spr_grunt_walk_left",
		"spr_grunt_walk_left", nullptr, TEXTURE_PATH);


	// Grunt Walk_Right
	CResourceManager::GetInst()->CreateAnimationSequence("spr_grunt_walk_right",
		"spr_grunt_walk_right", nullptr, TEXTURE_PATH);

	// Grunt Attack_Left
	CResourceManager::GetInst()->CreateAnimationSequence("spr_grunt_attack_left",
		"spr_grunt_attack_left", nullptr, TEXTURE_PATH);


	// Grunt Attack_Right
	CResourceManager::GetInst()->CreateAnimationSequence("spr_grunt_attack_right",
		"spr_grunt_attack_right", nullptr, TEXTURE_PATH);


	// Grunt HurtFly_Left
	CResourceManager::GetInst()->CreateAnimationSequence("spr_grunt_hurtfly_left",
		"spr_grunt_hurtfly_left", nullptr, TEXTURE_PATH);


	// Grunt HurtFly_Right
	CResourceManager::GetInst()->CreateAnimationSequence("spr_grunt_hurtfly_right",
		"spr_grunt_hurtfly_right", nullptr, TEXTURE_PATH);


	// Grunt HurtGround_Left
	CResourceManager::GetInst()->CreateAnimationSequence("spr_grunt_hurtground_left",
		"spr_grunt_hurtground_left", nullptr, TEXTURE_PATH);


	// Grunt HurtGround_Right
	CResourceManager::GetInst()->CreateAnimationSequence("spr_grunt_hurtground_right",
		"spr_grunt_hurtground_right", nullptr, TEXTURE_PATH);

}

void CStage_3::CreateAnimationSequenceGangster()
{
	// #### Gangster Animation ####
	// Gangster Idle_Left
	CResourceManager::GetInst()->CreateAnimationSequence("spr_gangster_idle_left",
		"spr_gangster_idle_left", nullptr, TEXTURE_PATH);

	// Gangster Idle_Right
	CResourceManager::GetInst()->CreateAnimationSequence("spr_gangster_idle_right",
		"spr_gangster_idle_right", nullptr, TEXTURE_PATH);

	// Gangster spr_gangsteraim_left
	CResourceManager::GetInst()->CreateAnimationSequence("spr_gangsteraim_left",
		"spr_gangsteraim_left", nullptr, TEXTURE_PATH);

	// Gangster spr_gangsteraim_right
	CResourceManager::GetInst()->CreateAnimationSequence("spr_gangsteraim_right",
		"spr_gangsteraim_right", nullptr, TEXTURE_PATH);


	// Gangster HurtFly_Left
	CResourceManager::GetInst()->CreateAnimationSequence("spr_gangsterhurtfly_left",
		"spr_gangsterhurtfly_left", nullptr, TEXTURE_PATH);

	// Gangster HurtFly_Right
	CResourceManager::GetInst()->CreateAnimationSequence("spr_gangsterhurtfly_right",
		"spr_gangsterhurtfly_right", nullptr, TEXTURE_PATH);


	// Gangster HurtGround_Left
	CResourceManager::GetInst()->CreateAnimationSequence("spr_gangsterhurtground_left",
		"spr_gangsterhurtground_left", nullptr, TEXTURE_PATH);

	// Gangster HurtGround_Right
	CResourceManager::GetInst()->CreateAnimationSequence("spr_gangsterhurtground_right",
		"spr_gangsterhurtground_right", nullptr, TEXTURE_PATH);

	// Gangster spr_gangsterrun_left
	CResourceManager::GetInst()->CreateAnimationSequence("spr_gangsterrun_left",
		"spr_gangsterrun_left", nullptr, TEXTURE_PATH);

	// Gangster spr_gangsterrun_right
	CResourceManager::GetInst()->CreateAnimationSequence("spr_gangsterrun_right",
		"spr_gangsterrun_right", nullptr, TEXTURE_PATH);


	// Gangster spr_gangsterturn_left
	CResourceManager::GetInst()->CreateAnimationSequence("spr_gangsterturn_left",
		"spr_gangsterturn_left", nullptr, TEXTURE_PATH);

	// Gangster spr_gangsterturn_right
	CResourceManager::GetInst()->CreateAnimationSequence("spr_gangsterturn_right",
		"spr_gangsterturn_right", nullptr, TEXTURE_PATH);


	// Gangster spr_gangsterwalk_left
	CResourceManager::GetInst()->CreateAnimationSequence("spr_gangsterwalk_left",
		"spr_gangsterwalk_left", nullptr, TEXTURE_PATH);

	// Gangster spr_gangsterwalk_right
	CResourceManager::GetInst()->CreateAnimationSequence("spr_gangsterwalk_right",
		"spr_gangsterwalk_right", nullptr, TEXTURE_PATH);

}

void CStage_3::CreateAnimationSequencePomp()
{
	// spr_pomp_attack_left
	CResourceManager::GetInst()->CreateAnimationSequence("spr_pomp_attack_left",
		"spr_pomp_attack_left", nullptr, TEXTURE_PATH);

	// spr_pomp_attack_right
	CResourceManager::GetInst()->CreateAnimationSequence("spr_pomp_attack_right",
		"spr_pomp_attack_right", nullptr, TEXTURE_PATH);

	// spr_pomp_hurtfly_left
	CResourceManager::GetInst()->CreateAnimationSequence("spr_pomp_hurtfly_left",
		"spr_pomp_hurtfly_left", nullptr, TEXTURE_PATH);


	// spr_pomp_hurtfly_right
	CResourceManager::GetInst()->CreateAnimationSequence("spr_pomp_hurtfly_right",
		"spr_pomp_hurtfly_right", nullptr, TEXTURE_PATH);


	// spr_pomp_hurtground_left
	CResourceManager::GetInst()->CreateAnimationSequence("spr_pomp_hurtground_left",
		"spr_pomp_hurtground_left", nullptr, TEXTURE_PATH);

	// spr_pomp_hurtground_right
	CResourceManager::GetInst()->CreateAnimationSequence("spr_pomp_hurtground_right",
		"spr_pomp_hurtground_right", nullptr, TEXTURE_PATH);

	// spr_pomp_idle_left
	CResourceManager::GetInst()->CreateAnimationSequence("spr_pomp_idle_left",
		"spr_pomp_idle_left", nullptr, TEXTURE_PATH);

	// spr_pomp_idle_right
	CResourceManager::GetInst()->CreateAnimationSequence("spr_pomp_idle_right",
		"spr_pomp_idle_right", nullptr, TEXTURE_PATH);

	// spr_pomp_knockdown_left
	CResourceManager::GetInst()->CreateAnimationSequence("spr_pomp_knockdown_left",
		"spr_pomp_knockdown_left", nullptr, TEXTURE_PATH);

	// spr_pomp_knockdown_right
	CResourceManager::GetInst()->CreateAnimationSequence("spr_pomp_knockdown_right",
		"spr_pomp_knockdown_right", nullptr, TEXTURE_PATH);

	// spr_pomp_run_left
	CResourceManager::GetInst()->CreateAnimationSequence("spr_pomp_run_left",
		"spr_pomp_run_left", nullptr, TEXTURE_PATH);

	// spr_pomp_run_right
	CResourceManager::GetInst()->CreateAnimationSequence("spr_pomp_run_right",
		"spr_pomp_run_right", nullptr, TEXTURE_PATH);

	// spr_pomp_turn_left
	CResourceManager::GetInst()->CreateAnimationSequence("spr_pomp_turn_left",
		"spr_pomp_turn_left", nullptr, TEXTURE_PATH);

	// spr_pomp_turn_right
	CResourceManager::GetInst()->CreateAnimationSequence("spr_pomp_turn_right",
		"spr_pomp_turn_right", nullptr, TEXTURE_PATH);

	// spr_pomp_walk_left
	CResourceManager::GetInst()->CreateAnimationSequence("spr_pomp_walk_left",
		"spr_pomp_walk_left", nullptr, TEXTURE_PATH);

	// spr_pomp_walk_right
	CResourceManager::GetInst()->CreateAnimationSequence("spr_pomp_walk_right",
		"spr_pomp_walk_right", nullptr, TEXTURE_PATH);


}

void CStage_3::CreateAnimationSequenceEffect_Frame()
{
	// #################### EFFECT ####################
	// Dust_Cloud Animation
	CResourceManager::GetInst()->CreateAnimationSequence("spr_dustcloud",
		"spr_dustcloud", nullptr, TEXTURE_PATH);

	// Jump_Cloud
	CResourceManager::GetInst()->CreateAnimationSequence("spr_jumpcloud",
		"spr_jumpcloud", nullptr, TEXTURE_PATH);


	// Land_Cloud
	CResourceManager::GetInst()->CreateAnimationSequence("spr_landcloud",
		"spr_landcloud", nullptr, TEXTURE_PATH);

	// Slash
	CResourceManager::GetInst()->CreateAnimationSequence("spr_slash",
		"spr_slash", nullptr, TEXTURE_PATH);

}

void CStage_3::CreateAnimationSequenceEffect_Sprite()
{
	// ## EFFECT
	// BloodAnimation_Left ÇÑÀåÂ¥¸® ÀÌ¹ÌÁö ¹æ½Ä
	GetSceneResource()->CreateAnimationSequence("effect_bloodanimation_left",
		"effect_bloodanimation_left", TEXT("Effect/effect_bloodanimation_left.bmp"), TEXTURE_PATH);
	GetSceneResource()->SetColorKey("effect_bloodanimation_left", 255, 0, 255);


	// BloodAnimation_Right ÇÑÀåÂ¥¸® ÀÌ¹ÌÁö ¹æ½Ä
	GetSceneResource()->CreateAnimationSequence("effect_bloodanimation_right",
		"effect_bloodanimation_right", TEXT("Effect/effect_bloodanimation_right.bmp"), TEXTURE_PATH);
	GetSceneResource()->SetColorKey("effect_bloodanimation_right", 255, 0, 255);


	// BloodAnimation2_Left ÇÑÀåÂ¥¸® ÀÌ¹ÌÁö ¹æ½Ä
	GetSceneResource()->CreateAnimationSequence("effect_bloodanimation2_left",
		"effect_bloodanimation2_left", TEXT("Effect/effect_bloodanimation2_left.bmp"), TEXTURE_PATH);
	GetSceneResource()->SetColorKey("effect_bloodanimation2_left", 255, 0, 255);


	// BloodAnimation2_Right ÇÑÀåÂ¥¸® ÀÌ¹ÌÁö ¹æ½Ä
	GetSceneResource()->CreateAnimationSequence("effect_bloodanimation2_right",
		"effect_bloodanimation2_right", TEXT("Effect/effect_bloodanimation2_right.bmp"), TEXTURE_PATH);
	GetSceneResource()->SetColorKey("effect_bloodanimation2_right", 255, 0, 255);


	// effect_slash_hit ÇÑÀåÂ¥¸® ÀÌ¹ÌÁö ¹æ½Ä
	GetSceneResource()->CreateAnimationSequence("effect_slash_hit",
		"effect_slash_hit", TEXT("Effect/effect_slash_hit.bmp"), TEXTURE_PATH);
	GetSceneResource()->SetColorKey("effect_slash_hit", 255, 0, 255);


	// effect_reflect ÇÑÀåÂ¥¸® ÀÌ¹ÌÁö ¹æ½Ä
	GetSceneResource()->CreateAnimationSequence("effect_reflect",
		"effect_reflect", TEXT("Effect/effect_reflect.bmp"), TEXTURE_PATH);
	GetSceneResource()->SetColorKey("effect_reflect", 255, 0, 255);


	// effect_gunspark_left ÇÑÀåÂ¥¸® ÀÌ¹ÌÁö ¹æ½Ä
	GetSceneResource()->CreateAnimationSequence("effect_gunspark_left",
		"effect_gunspark_left", TEXT("Effect/effect_gunspark_left.bmp"), TEXTURE_PATH);
	GetSceneResource()->SetColorKey("effect_gunspark_left", 255, 0, 255);


	// effect_gunspark_left ÇÑÀåÂ¥¸® ÀÌ¹ÌÁö ¹æ½Ä
	GetSceneResource()->CreateAnimationSequence("effect_gunspark_right",
		"effect_gunspark_right", TEXT("Effect/effect_gunspark_right.bmp"), TEXTURE_PATH);
	GetSceneResource()->SetColorKey("effect_gunspark_right", 255, 0, 255);


}

