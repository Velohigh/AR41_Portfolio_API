
#include "EditScene.h"
#include "../GameObject/TileMap.h"
#include "SceneResource.h"
#include "Camera.h"
#include "../Input.h"
#include "Camera.h"
#include "../GameManager.h"
#include "EditDlg.h"
#include "../Resource/Texture/Texture.h"

CEditScene::CEditScene()	:
	m_TileMapDlg(nullptr)
{
}

CEditScene::~CEditScene()
{
	CGameManager::GetInst()->SetEditMode(false);
	SAFE_DELETE(m_TileMapDlg);
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
	CInput::GetInst()->AddBindFunction<CEditScene>("OpenTileMapEditor",
		Input_Type::Down, this, &CEditScene::OpenTileMapEditor);

	CGameManager::GetInst()->SetEditMode(true);

	return true;
}

void CEditScene::CreateTileMap(int CountX, int CountY, int SizeX, int SizeY)
{
	if (!m_TileMap)
		m_TileMap = CreateObject<CTileMap>("TileMap");

	m_TileMap->CreateTile(CountX, CountY, Vector2((float)SizeX, (float)SizeY));
}

void CEditScene::SetTileTexture(CTexture* Texture)
{
	if (m_TileMap)
		m_TileMap->SetTileTexture(Texture);
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

void CEditScene::OpenTileMapEditor()
{
	if (!m_TileMapDlg)
	{
		m_TileMapDlg = new CEditDlg;

		m_TileMapDlg->m_Scene = this;
		m_TileMapDlg->Init();
	}
}
