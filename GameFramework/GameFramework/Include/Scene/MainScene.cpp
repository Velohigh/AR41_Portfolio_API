
#include "MainScene.h"
#include "../GameObject/Player.h"
#include "../GameObject/Monster.h"

CMainScene::CMainScene()
{
}

CMainScene::~CMainScene()
{
}

bool CMainScene::Init()
{
	CPlayer* Player = CreateObject<CPlayer>("Player");

	SetPlayer(Player);

	CreateObject<CMonster>("Monster");

	return true;
}
