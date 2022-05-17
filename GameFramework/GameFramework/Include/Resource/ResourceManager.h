#pragma once

#include "../SingletonMacro.h"
#include "../GameInfo.h"

class CResourceManager
{
private:
	class CTextureManager* m_TextureManager;
	class CAnimationManager* m_AnimationManager;

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

	bool SetColorKey(const std::string& Name, unsigned char r, unsigned char g, unsigned char b,
		int Index = 0);
	bool SetColorKeyAll(const std::string& Name, unsigned char r, unsigned char g, unsigned char b);

	class CTexture* FindTexture(const std::string& Name);
	void ReleaseTexture(const std::string& Name);



public:	// ==================== Animation Sequence ====================
	bool CreateAnimationSequence(const std::string& Name, class CTexture* Texture);
	bool CreateAnimationSequence(const std::string& Name, const std::string& TexName);
	bool CreateAnimationSequence(const std::string& Name, const std::string& TexName,
		const TCHAR* FileName, const std::string& PathName);
	bool CreateAnimationSequenceFullPath(const std::string& Name, const std::string& TexName,
		const TCHAR* FullPath);

#ifdef UNICODE

	bool CreateAnimationSequence(const std::string& Name, const std::string& TexName,
		const std::vector<std::wstring>& vecFileName, const std::string& PathName);
	bool CreateAnimationSequenceFullPath(const std::string& Name, const std::string& TexName,
		const std::vector<std::wstring>& vecFullPath);

#else

	bool CreateAnimationSequence(const std::string& Name, const std::string& TexName,
		const std::vector<std::string>& vecFileName, const std::string& PathName);
	bool CreateAnimationSequenceFullPath(const std::string& Name, const std::string& TexName,
		const std::vector<std::string>& vecFullPath);

#endif // UNICODE


	bool AddAnimationFrame(const std::string& Name, const Vector2& Start,
		const Vector2& End);
	bool AddAnimationFrame(const std::string& Name,
		float PosX, float PosY, float SizeX, float SizeY);

	class CAnimationSequence* FindAnimation(const std::string& Name);
	void ReleaseAnimation(const std::string& Name);

	DECLARE_SINGLE(CResourceManager)
};

