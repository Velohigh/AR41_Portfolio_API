
#include "Stage_1.h"
#include "../GameObject/Player.h"
#include "../GameObject/Monster.h"
#include "../GameObject/BackObj.h"
#include "SceneResource.h"
#include "Camera.h"
#include "../Input.h"
#include "../Widget/CharacterHUD.h"
#include "../GameObject/TileMap.h"

CStage_1::CStage_1()
{
}

CStage_1::~CStage_1()
{
}

bool CStage_1::Init()
{
	CreateAnimationSequence();

	GetSceneResource()->SetVolume(100);

	GetCamera()->SetResolution(1280.f, 720.f);
	GetCamera()->SetWorldResolution(1500.f, 1200.f);
	GetCamera()->SetTargetPivot(0.5f, 0.5f);

	//CreateObject<CBackObj>("BackObj");

	CPlayer* Player = CreateObject<CPlayer>("Player");

	SetPlayer(Player);

	GetCamera()->SetTarget(Player);

	//CreateWidgetWindow<CCharacterHUD>("CharacterHUD");

	return true;
}

void CStage_1::CreateAnimationSequence()
{

}

