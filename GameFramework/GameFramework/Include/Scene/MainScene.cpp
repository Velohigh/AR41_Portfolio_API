
#include "MainScene.h"
#include "../GameObject/Player.h"
#include "../GameObject/Monster.h"
#include "../GameObject/BackObj.h"
#include "SceneResource.h"

CMainScene::CMainScene()
{
}

CMainScene::~CMainScene()
{
}

bool CMainScene::Init()
{
	CreateAnimationSequence();



	CreateObject<CBackObj>("BackObj");

	CPlayer* Player = CreateObject<CPlayer>("Player");

	SetPlayer(Player);

	CreateObject<CMonster>("Monster");

	return true;
}

void CMainScene::CreateAnimationSequence()
{
	GetSceneResource()->CreateAnimationSequence("PlayerRightIdle",
		"PlayerRightIdle", TEXT("Player/Right/astand.bmp"), TEXTURE_PATH);

	for (int i = 0; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrame("PlayerRightIdle", 82.f * i, 0.f,
			82.f, 73.f);
	}

	GetSceneResource()->SetColorKey("PlayerRightIdle", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("PlayerRightWalk",
		"PlayerRightWalk", TEXT("Player/Right/awalk.bmp"), TEXTURE_PATH);

	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("PlayerRightWalk", 85.f * i, 0.f,
			85.f, 75.f);
	}

	GetSceneResource()->SetColorKey("PlayerRightWalk", 255, 0, 255);
}
