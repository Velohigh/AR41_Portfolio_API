
#include "TextureManager.h"
#include "Texture.h"

CTextureManager::CTextureManager()
{
}

CTextureManager::~CTextureManager()
{
}

bool CTextureManager::Init()
{
	return true;
}

bool CTextureManager::LoadTexture(const std::string& Name, 
	const TCHAR* FileName, const std::string& PathName)
{
	// ���� �̸����� ����Ȱ� �ִٸ� �߸��Ȱ��̴�.
	CTexture* Texture = FindTexture(Name);

	if (Texture)
		return false;

	Texture = new CTexture;

	if (!Texture->LoadTexture(FileName, PathName))
	{
		SAFE_RELEASE(Texture);
		return false;
	}

	m_mapTexture.insert(std::make_pair(Name, Texture));

	return true;
}

CTexture* CTextureManager::FindTexture(const std::string& Name)
{
	auto	iter = m_mapTexture.find(Name);

	if (iter == m_mapTexture.end())
		return nullptr;

	return iter->second;
}
