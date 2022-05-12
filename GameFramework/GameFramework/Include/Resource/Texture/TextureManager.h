#pragma once

#include "../../GameInfo.h"

class CTextureManager
{
	friend class CResourceManager;

private:
	CTextureManager();
	~CTextureManager();

private:
	std::unordered_map<std::string, CSharedPtr<class CTexture>>	m_mapTexture;

public:
	bool Init();

public:
	bool LoadTexture(const std::string& Name, const TCHAR* FileName,
		const std::string& PathName = TEXTURE_PATH);
	class CTexture* FindTexture(const std::string& Name);
};

