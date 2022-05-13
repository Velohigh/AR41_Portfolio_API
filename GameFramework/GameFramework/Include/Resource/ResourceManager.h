#pragma once

#include "../SingletonMacro.h"
#include "../GameInfo.h"

class CResourceManager
{
private:
	class CTextureManager* m_TextureManager;

public:
	bool Init();
	void Update();

public:	// ==================== Texture ====================
	bool LoadTexture(const std::string& Name, const TCHAR* FileName,
		const std::string& PathName = TEXTURE_PATH);
	bool LoadTextureFullPath(const std::string& Name, const TCHAR* FullPath);

#ifdef UNICODE

	bool LoadTexture(const std::string& Name, const std::vector<std::wstring>& vecFileName,
		const std::string& PathName = TEXTURE_PATH);
	bool LoadTextureFullPath(const std::string& Name, const std::vector<std::wstring>& vecFullPath);

#else

	bool LoadTexture(const std::string& Name, const std::vector<std::string>& vecFileName,
		const std::string& PathName = TEXTURE_PATH);
	bool LoadTextureFullPath(const std::string& Name, const std::vector<std::string>& vecFullPath);

#endif // UNICODE

	class CTexture* FindTexture(const std::string& Name);
	void ReleaseTexture(const std::string& Name);

	DECLARE_SINGLE(CResourceManager)
};

