
#include "MainScene.h"
#include "../GameObject/Player.h"

CMainScene::CMainScene()
{
}

CMainScene::~CMainScene()
{
}

bool CMainScene::Init()
{
	CreateObject<CPlayer>("Player");

	return true;
}

