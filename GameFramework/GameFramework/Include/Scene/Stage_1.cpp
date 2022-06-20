
#include "Stage_1.h"
#include "../GameObject/Player.h"
#include "../GameObject/Monster.h"
#include "../GameObject/BackObj.h"
#include "SceneResource.h"
#include "Camera.h"
#include "../Input.h"
#include "../Widget/CharacterHUD.h"
#include "../GameObject/TileMap.h"

CStage_1::CStage_1()	:
	Back(nullptr)
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
	GetCamera()->SetWorldResolution(1800.f, 784.f);
	GetCamera()->SetTargetPivot(0.5f, 0.5f);

	Back = CreateObject<CBackObj>("BackObj");
	Back->SetTexture("room_factory_2", TEXT("room_factory_2.bmp"), "MapPath");

	CPlayer* Player = CreateObject<CPlayer>("Player");

	SetPlayer(Player);

	GetCamera()->SetTarget(Player);

	//CreateWidgetWindow<CCharacterHUD>("CharacterHUD");

	return true;
}

void CStage_1::CreateAnimationSequence()
{

}

