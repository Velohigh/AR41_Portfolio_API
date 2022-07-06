
#include "Stage_2.h"
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
#include "../GameObject/Cursor.h"
#include "../Resource/Texture/Texture.h"
#include "../GameObject/Effect.h"
#include "../Resource/ResourceManager.h"
#include "../Resource/Animation/AnimationManager.h"

CStage_2::CStage_2() :
	Back(nullptr)
{
}

CStage_2::~CStage_2()
{
}

bool CStage_2::Init()
{
	CScene::Init();

	CreateAnimationSequencePlayer();
	CreateAnimationSequenceGrunt();
	CreateAnimationSequenceGangster();
	CreateAnimationSequenceEffect_Frame();
	CreateAnimationSequenceEffect_Sprite();

	GetSceneResource()->LoadSound("BGM", "bgm_bunker", true, "bgm_bunker.mp3");
	GetSceneResource()->LoadSound("Effect", "sound_enemy_bloodsplat1", false, "sound_enemy_bloodsplat1.wav");
	GetSceneResource()->LoadSound("Effect", "sound_enemy_bloodsplat2", false, "sound_enemy_bloodsplat2.wav");
	GetSceneResource()->LoadSound("Effect", "sound_enemy_bloodsplat3", false, "sound_enemy_bloodsplat3.wav");
	GetSceneResource()->LoadSound("Effect", "sound_enemy_bloodsplat4", false, "sound_enemy_bloodsplat4.wav");
	GetSceneResource()->SetVolume(100);
	GetSceneResource()->LoadSound("Effect", "fire", false, "fire.wav");
	GetSceneResource()->LoadSound("Effect", "swing", false, "swing.wav");
	GetSceneResource()->LoadSound("Effect", "punch", false, "punch.wav");
	GetSceneResource()->LoadSound("Effect", "death_bullet", false, "death_bullet.wav");
	GetSceneResource()->LoadSound("Effect", "reflect", false, "reflect.wav");


	GetCamera()->SetResolution(1280.f, 720.f);
	GetCamera()->SetWorldResolution(2176.f, 3500.f);
	GetCamera()->SetTargetPivot(0.5f, 0.5f);

	Back = CreateObject<CBackObj>("BackObj");
	Back->SetTexture("stage2_bg_render", TEXT("stage2_bg_render.bmp"), "MapPath");

	auto iter = m_ObjList[(int)ERender_Layer::Default].begin();
	auto iterEnd = m_ObjList[(int)ERender_Layer::Default].end();

	// 마우스
	CCursor* Cursor = CreateObject<CCursor>("Cursor");
	Cursor->SetPos(CInput::GetInst()->GetMouseWorldPos());
	Cursor->SetColorKey(255, 0, 255);

	// 플레이어
	CPlayer* Player = CreateObject<CPlayer>("Player");
	Player->SetPos({ 375.f, 300.f });
	Player->StateChange(PlayerState::Idle);
	Player->SetMapTexture("stage2_bg_collision", TEXT("stage2_bg_collision.bmp"), "MapPath");

	SetPlayer(Player);
	GetCamera()->SetTarget(Player);


	{
		// 그런트
		CGrunt* NewGrunt = CreateObject<CGrunt>("Grunt");	// 10층
		NewGrunt->SetPos({ 550.f, 415.f });
		NewGrunt->SetDir(ObjDir::Right);
		NewGrunt->SetState(ObjState::Walk);
		NewGrunt->SetPatrol(true);
		NewGrunt->SetPatrolTime(3.f);
		NewGrunt->SetMapTexture("stage2_bg_collision", TEXT("stage2_bg_collision.bmp"), "MapPath");


		NewGrunt = CreateObject<CGrunt>("Grunt");	// 8층 순찰
		NewGrunt->SetPos({ 642, 863.f });
		NewGrunt->SetDir(ObjDir::Right);
		NewGrunt->SetState(ObjState::Walk);
		NewGrunt->SetPatrol(true);
		NewGrunt->SetPatrolTime(3.f);
		NewGrunt->SetMapTexture("stage2_bg_collision", TEXT("stage2_bg_collision.bmp"), "MapPath");


		NewGrunt = CreateObject<CGrunt>("Grunt");	// 6층 정찰
		NewGrunt->SetPos({ 924, 1311.f });
		NewGrunt->SetDir(ObjDir::Left);
		NewGrunt->SetState(ObjState::Walk);
		NewGrunt->SetPatrol(true);
		NewGrunt->SetPatrolTime(2.f);
		NewGrunt->SetMapTexture("stage2_bg_collision", TEXT("stage2_bg_collision.bmp"), "MapPath");

		NewGrunt = CreateObject<CGrunt>("Grunt");	// 6층 Idle
		NewGrunt->SetPos({ 596, 1311.f });
		NewGrunt->SetDir(ObjDir::Right);
		NewGrunt->SetState(ObjState::Idle);
		NewGrunt->SetMapTexture("stage2_bg_collision", TEXT("stage2_bg_collision.bmp"), "MapPath");

		NewGrunt = CreateObject<CGrunt>("Grunt");	// 5층 Patrol
		NewGrunt->SetPos({ 871, 1535 });
		NewGrunt->SetDir(ObjDir::Right);
		NewGrunt->SetState(ObjState::Walk);
		NewGrunt->SetPatrol(true);
		NewGrunt->SetPatrolTime(3.f);
		NewGrunt->SetMapTexture("stage2_bg_collision", TEXT("stage2_bg_collision.bmp"), "MapPath");


		NewGrunt = CreateObject<CGrunt>("Grunt");	// 2층 Idle
		NewGrunt->SetPos({ 630, 2207 });
		NewGrunt->SetDir(ObjDir::Left);
		NewGrunt->SetState(ObjState::Idle);
		NewGrunt->SetMapTexture("stage2_bg_collision", TEXT("stage2_bg_collision.bmp"), "MapPath");

		NewGrunt = CreateObject<CGrunt>("Grunt");	// 1층 계단 순찰
		NewGrunt->SetPos({ 1155, 2754 });
		NewGrunt->SetDir(ObjDir::Left);
		NewGrunt->SetState(ObjState::Walk);
		NewGrunt->SetPatrol(true);
		NewGrunt->SetPatrolTime(5.f);
		NewGrunt->SetMapTexture("stage2_bg_collision", TEXT("stage2_bg_collision.bmp"), "MapPath");


		NewGrunt = CreateObject<CGrunt>("Grunt");	// 1층 Idle
		NewGrunt->SetPos({ 1638, 2943 });
		NewGrunt->SetDir(ObjDir::Right);
		NewGrunt->SetState(ObjState::Idle);
		NewGrunt->SetMapTexture("stage2_bg_collision", TEXT("stage2_bg_collision.bmp"), "MapPath");

		NewGrunt = CreateObject<CGrunt>("Grunt");	// 1층 Idle
		NewGrunt->SetPos({ 1741, 2943 });
		NewGrunt->SetDir(ObjDir::Left);
		NewGrunt->SetState(ObjState::Idle);
		NewGrunt->SetMapTexture("stage2_bg_collision", TEXT("stage2_bg_collision.bmp"), "MapPath");



		// 갱스터
		CGangster* NewGangster = CreateObject<CGangster>("Gangster");	// 9층 우측끝
		NewGangster->SetPos({ 1212, 639 });
		NewGangster->SetDir(ObjDir::Left);
		NewGangster->SetState(ObjState::Idle);
		NewGangster->SetMapTexture("stage2_bg_collision", TEXT("stage2_bg_collision.bmp"), "MapPath");

		NewGangster = CreateObject<CGangster>("Gangster");	// 8층 좌측끝
		NewGangster->SetPos({ 574, 863 });
		NewGangster->SetDir(ObjDir::Right);
		NewGangster->SetState(ObjState::Idle);
		NewGangster->SetMapTexture("stage2_bg_collision", TEXT("stage2_bg_collision.bmp"), "MapPath");

		NewGangster = CreateObject<CGangster>("Gangster");	// 7층 끝
		NewGangster->SetPos({ 1216, 1087 });
		NewGangster->SetDir(ObjDir::Left);
		NewGangster->SetState(ObjState::Idle);
		NewGangster->SetMapTexture("stage2_bg_collision", TEXT("stage2_bg_collision.bmp"), "MapPath");


		NewGangster = CreateObject<CGangster>("Gangster");	// 5층 끝
		NewGangster->SetPos({ 1220, 1535 });
		NewGangster->SetDir(ObjDir::Left);
		NewGangster->SetState(ObjState::Idle);
		NewGangster->SetMapTexture("stage2_bg_collision", TEXT("stage2_bg_collision.bmp"), "MapPath");

		NewGangster = CreateObject<CGangster>("Gangster");	// 5층
		NewGangster->SetPos({ 1150, 1535 });
		NewGangster->SetDir(ObjDir::Right);
		NewGangster->SetState(ObjState::Idle);
		NewGangster->SetMapTexture("stage2_bg_collision", TEXT("stage2_bg_collision.bmp"), "MapPath");

		NewGangster = CreateObject<CGangster>("Gangster");	// 4층
		NewGangster->SetPos({ 575, 1759 });
		NewGangster->SetDir(ObjDir::Right);
		NewGangster->SetState(ObjState::Idle);
		NewGangster->SetMapTexture("stage2_bg_collision", TEXT("stage2_bg_collision.bmp"), "MapPath");

		NewGangster = CreateObject<CGangster>("Gangster");	// 4층 계단
		NewGangster->SetPos({ 986, 1731 });
		NewGangster->SetDir(ObjDir::Left);
		NewGangster->SetState(ObjState::Idle);
		NewGangster->SetMapTexture("stage2_bg_collision", TEXT("stage2_bg_collision.bmp"), "MapPath");


		NewGangster = CreateObject<CGangster>("Gangster");	// 3층 끝
		NewGangster->SetPos({ 1220, 1983 });
		NewGangster->SetDir(ObjDir::Left);
		NewGangster->SetState(ObjState::Idle);
		NewGangster->SetMapTexture("stage2_bg_collision", TEXT("stage2_bg_collision.bmp"), "MapPath");


		NewGangster = CreateObject<CGangster>("Gangster");	// 2층 끝
		NewGangster->SetPos({ 583, 2207 });
		NewGangster->SetDir(ObjDir::Right);
		NewGangster->SetState(ObjState::Idle);
		NewGangster->SetMapTexture("stage2_bg_collision", TEXT("stage2_bg_collision.bmp"), "MapPath");

		NewGangster = CreateObject<CGangster>("Gangster");	// 1층 끝
		NewGangster->SetPos({ 2000, 2943 });
		NewGangster->SetDir(ObjDir::Left);
		NewGangster->SetState(ObjState::Idle);
		NewGangster->SetMapTexture("stage2_bg_collision", TEXT("stage2_bg_collision.bmp"), "MapPath");


	}


	CreateWidgetWindow<CCharacterHUD>("CharacterHUD");

	m_BgmOn = true;

	return true;
}

void CStage_2::Update(float DeltaTime)
{
	CScene::Update(DeltaTime);

	if (m_BgmOn == true)
	{
		m_BgmOn = !m_BgmOn;

		GetSceneResource()->SoundPlay("bgm_bunker");
	}

}

void CStage_2::SetSlowMap()
{
	Back->SetTexture("stage2_bg_render_slow", TEXT("stage2_bg_render_slow.bmp"), "MapPath");
}

void CStage_2::SetNormalMap()
{
	Back->SetTexture("stage2_bg_render", TEXT("stage2_bg_render.bmp"), "MapPath");
}

void CStage_2::CreateAnimationSequencePlayer()
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

void CStage_2::CreateAnimationSequenceGrunt()
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

void CStage_2::CreateAnimationSequenceGangster()
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

void CStage_2::CreateAnimationSequenceEffect_Frame()
{
}

void CStage_2::CreateAnimationSequenceEffect_Sprite()
{
	// ## EFFECT
	// BloodAnimation_Left 한장짜리 이미지 방식
	GetSceneResource()->CreateAnimationSequence("effect_bloodanimation_left",
		"effect_bloodanimation_left", TEXT("Effect/effect_bloodanimation_left.bmp"), TEXTURE_PATH);
	GetSceneResource()->SetColorKey("effect_bloodanimation_left", 255, 0, 255);


	// BloodAnimation_Right 한장짜리 이미지 방식
	GetSceneResource()->CreateAnimationSequence("effect_bloodanimation_right",
		"effect_bloodanimation_right", TEXT("Effect/effect_bloodanimation_right.bmp"), TEXTURE_PATH);
	GetSceneResource()->SetColorKey("effect_bloodanimation_right", 255, 0, 255);


	// BloodAnimation2_Left 한장짜리 이미지 방식
	GetSceneResource()->CreateAnimationSequence("effect_bloodanimation2_left",
		"effect_bloodanimation2_left", TEXT("Effect/effect_bloodanimation2_left.bmp"), TEXTURE_PATH);
	GetSceneResource()->SetColorKey("effect_bloodanimation2_left", 255, 0, 255);


	// BloodAnimation2_Right 한장짜리 이미지 방식
	GetSceneResource()->CreateAnimationSequence("effect_bloodanimation2_right",
		"effect_bloodanimation2_right", TEXT("Effect/effect_bloodanimation2_right.bmp"), TEXTURE_PATH);
	GetSceneResource()->SetColorKey("effect_bloodanimation2_right", 255, 0, 255);


	// effect_slash_hit 한장짜리 이미지 방식
	GetSceneResource()->CreateAnimationSequence("effect_slash_hit",
		"effect_slash_hit", TEXT("Effect/effect_slash_hit.bmp"), TEXTURE_PATH);
	GetSceneResource()->SetColorKey("effect_slash_hit", 255, 0, 255);


	// effect_reflect 한장짜리 이미지 방식
	GetSceneResource()->CreateAnimationSequence("effect_reflect",
		"effect_reflect", TEXT("Effect/effect_reflect.bmp"), TEXTURE_PATH);
	GetSceneResource()->SetColorKey("effect_reflect", 255, 0, 255);


	// effect_gunspark_left 한장짜리 이미지 방식
	GetSceneResource()->CreateAnimationSequence("effect_gunspark_left",
		"effect_gunspark_left", TEXT("Effect/effect_gunspark_left.bmp"), TEXTURE_PATH);
	GetSceneResource()->SetColorKey("effect_gunspark_left", 255, 0, 255);


	// effect_gunspark_left 한장짜리 이미지 방식
	GetSceneResource()->CreateAnimationSequence("effect_gunspark_right",
		"effect_gunspark_right", TEXT("Effect/effect_gunspark_right.bmp"), TEXTURE_PATH);
	GetSceneResource()->SetColorKey("effect_gunspark_right", 255, 0, 255);


}

