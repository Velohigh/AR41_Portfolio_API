
#include "SceneManager.h"
#include "MainScene.h"

DEFINITION_SINGLE(CSceneManager)

CSceneManager::CSceneManager() :
	m_Scene(nullptr)
{

}

CSceneManager::~CSceneManager()
{
	SAFE_DELETE(m_Scene);
}

bool CSceneManager::Init()
{
	CreateScene<CMainScene>();

	return true;
}

bool CSceneManager::Update(float DeltaTime)
{
	m_Scene->Update(DeltaTime);

	return false;
}

void CSceneManager::Render(HDC hDC, float DeltaTime)
{
	m_Scene->Render(hDC, DeltaTime);
}
