
#include "EditScene.h"
#include "../GameObject/TileMap.h"
#include "SceneResource.h"
#include "Camera.h"
#include "../Input.h"
#include "Camera.h"

CEditScene::CEditScene()
{
}

CEditScene::~CEditScene()
{
}

bool CEditScene::Init()
{
	GetCamera()->SetResolution(1280.f, 720.f);
	GetCamera()->SetWorldResolution(1280.f, 720.f);
	GetCamera()->SetTargetPivot(0.5f, 0.5f);

	CInput::GetInst()->AddBindFunction<CEditScene>("MoveFront",
		Input_Type::Push, this, &CEditScene::MoveUp);
	CInput::GetInst()->AddBindFunction<CEditScene>("MoveBack",
		Input_Type::Push, this, &CEditScene::MoveDown);
	CInput::GetInst()->AddBindFunction<CEditScene>("GunRotation",
		Input_Type::Push, this, &CEditScene::MoveRight);
	CInput::GetInst()->AddBindFunction<CEditScene>("GunRotationInv",
		Input_Type::Push, this, &CEditScene::MoveLeft);

	return true;
}

void CEditScene::MoveLeft()
{
	//GetCamera()->
}

void CEditScene::MoveRight()
{
}

void CEditScene::MoveUp()
{
}

void CEditScene::MoveDown()
{
}
