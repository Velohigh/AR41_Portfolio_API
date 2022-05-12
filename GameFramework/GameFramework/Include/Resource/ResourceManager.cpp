
#include "ResourceManager.h"
#include "Texture/TextureManager.h"

DEFINITION_SINGLE(CResourceManager)

CResourceManager::CResourceManager()
{
	m_TextureManager = new CTextureManager;

	m_TextureManager->Init();
}

CResourceManager::~CResourceManager()
{
	SAFE_DELETE(m_TextureManager);
}

bool CResourceManager::Init()
{
	LoadTexture("Player", TEXT("teemo.bmp"));

	return true;
}

void CResourceManager::Update()
{
}

bool CResourceManager::LoadTexture(const std::string& Name, const TCHAR* FileName, const std::string& PathName)
{
	return m_TextureManager->LoadTexture(Name, FileName, PathName);
}

CTexture* CResourceManager::FindTexture(const std::string& Name)
{
	return m_TextureManager->FindTexture(Name);
}
