
#include "ResourceManager.h"
#include "Texture/TextureManager.h"
#include "Animation/AnimationManager.h"

DEFINITION_SINGLE(CResourceManager)

CResourceManager::CResourceManager()
{
	m_TextureManager = new CTextureManager;

	m_TextureManager->Init();

	m_AnimationManager = new CAnimationManager;

	m_AnimationManager->Init();
}

CResourceManager::~CResourceManager()
{
	SAFE_DELETE(m_AnimationManager);
	SAFE_DELETE(m_TextureManager);
}

bool CResourceManager::Init()
{
	return true;
}

void CResourceManager::Update()
{
}

bool CResourceManager::LoadTexture(const std::string& Name, const TCHAR* FileName, const std::string& PathName)
{
	return m_TextureManager->LoadTexture(Name, FileName, PathName);
}

bool CResourceManager::LoadTextureFullPath(const std::string& Name, const TCHAR* FullPath)
{
	return m_TextureManager->LoadTextureFullPath(Name, FullPath);
}

#ifdef UNICODE

bool CResourceManager::LoadTexture(const std::string& Name,
	const std::vector<std::wstring>& vecFileName, const std::string& PathName)
{
	return m_TextureManager->LoadTexture(Name, vecFileName, PathName);
}

bool CResourceManager::LoadTextureFullPath(const std::string& Name, 
	const std::vector<std::wstring>& vecFullPath)
{
	return m_TextureManager->LoadTextureFullPath(Name, vecFullPath);
}

#else

bool CResourceManager::LoadTexture(const std::string& Name, 
	const std::vector<std::string>& vecFileName, const std::string& PathName)
{
	return m_TextureManager->LoadTexture(Name, vecFileName, PathName);
}

bool CResourceManager::LoadTextureFullPath(const std::string& Name, 
	const std::vector<std::string>& vecFullPath)
{
	return m_TextureManager->LoadTextureFullPath(Name, vecFullPath);
}

#endif

bool CResourceManager::SetColorKey(const std::string& Name, unsigned char r, unsigned char g, unsigned char b, int Index)
{
	return m_TextureManager->SetColorKey(Name, r, g, b, Index);
}

bool CResourceManager::SetColorKeyAll(const std::string& Name, unsigned char r, unsigned char g, unsigned char b)
{
	return m_TextureManager->SetColorKeyAll(Name, r, g, b);
}

CTexture* CResourceManager::FindTexture(const std::string& Name)
{
	return m_TextureManager->FindTexture(Name);
}

void CResourceManager::ReleaseTexture(const std::string& Name)
{
	m_TextureManager->ReleaseTexture(Name);
}

bool CResourceManager::CreateAnimationSequence(const std::string& Name, 
	CTexture* Texture)
{
	return m_AnimationManager->CreateAnimationSequence(Name, Texture);
}

bool CResourceManager::CreateAnimationSequence(const std::string& Name,
	const std::string& TexName)
{
	CTexture* Texture = FindTexture(TexName);

	return m_AnimationManager->CreateAnimationSequence(Name, Texture);
}

bool CResourceManager::CreateAnimationSequence(const std::string& Name, 
	const std::string& TexName, const TCHAR* FileName, 
	const std::string& PathName)
{
	CTexture* Texture = FindTexture(TexName);

	// 같은 이름으로 추가되어 있을 경우 바로 처리
	if (Texture)
		return m_AnimationManager->CreateAnimationSequence(Name, Texture);

	// 같은 이름의 텍스쳐가 없을 경우 로딩하고 처리
	if (!m_TextureManager->LoadTexture(TexName, FileName, PathName))
		return false;

	Texture = FindTexture(TexName);

	return m_AnimationManager->CreateAnimationSequence(Name, Texture);
}

bool CResourceManager::CreateAnimationSequenceFullPath(const std::string& Name,
	const std::string& TexName, const TCHAR* FullPath)
{
	CTexture* Texture = FindTexture(TexName);

	// 같은 이름으로 추가되어 있을 경우 바로 처리
	if (Texture)
		return m_AnimationManager->CreateAnimationSequence(Name, Texture);

	// 같은 이름의 텍스쳐가 없을 경우 로딩하고 처리
	if (!m_TextureManager->LoadTextureFullPath(TexName, FullPath))
		return false;

	Texture = FindTexture(TexName);

	return m_AnimationManager->CreateAnimationSequence(Name, Texture);
}

#ifdef UNICODE

bool CResourceManager::CreateAnimationSequence(const std::string& Name, 
	const std::string& TexName, const std::vector<std::wstring>& vecFileName, 
	const std::string& PathName)
{
	CTexture* Texture = FindTexture(TexName);

	// 같은 이름으로 추가되어 있을 경우 바로 처리
	if (Texture)
		return m_AnimationManager->CreateAnimationSequence(Name, Texture);

	// 같은 이름의 텍스쳐가 없을 경우 로딩하고 처리
	if (!m_TextureManager->LoadTexture(TexName, vecFileName, PathName))
		return false;

	Texture = FindTexture(TexName);

	return m_AnimationManager->CreateAnimationSequence(Name, Texture);
}

bool CResourceManager::CreateAnimationSequenceFullPath(const std::string& Name, 
	const std::string& TexName, const std::vector<std::wstring>& vecFullPath)
{
	CTexture* Texture = FindTexture(TexName);

	// 같은 이름으로 추가되어 있을 경우 바로 처리
	if (Texture)
		return m_AnimationManager->CreateAnimationSequence(Name, Texture);

	// 같은 이름의 텍스쳐가 없을 경우 로딩하고 처리
	if (!m_TextureManager->LoadTextureFullPath(TexName, vecFullPath))
		return false;

	Texture = FindTexture(TexName);

	return m_AnimationManager->CreateAnimationSequence(Name, Texture);
}

#else

bool CResourceManager::CreateAnimationSequence(const std::string& Name, 
	const std::string& TexName, const std::vector<std::string>& vecFileName, const std::string& PathName)
{
	CTexture* Texture = FindTexture(TexName);

	// 같은 이름으로 추가되어 있을 경우 바로 처리
	if (Texture)
		return m_AnimationManager->CreateAnimationSequence(Name, Texture);

	// 같은 이름의 텍스쳐가 없을 경우 로딩하고 처리
	if (!m_TextureManager->LoadTexture(TexName, vecFileName, PathName))
		return false;

	Texture = FindTexture(TexName);

	return m_AnimationManager->CreateAnimationSequence(Name, Texture);
}

bool CResourceManager::CreateAnimationSequenceFullPath(const std::string& Name, 
	const std::string& TexName, const std::vector<std::string>& vecFullPath)
{
	CTexture* Texture = FindTexture(TexName);

	// 같은 이름으로 추가되어 있을 경우 바로 처리
	if (Texture)
		return m_AnimationManager->CreateAnimationSequence(Name, Texture);

	// 같은 이름의 텍스쳐가 없을 경우 로딩하고 처리
	if (!m_TextureManager->LoadTextureFullPath(TexName, vecFullPath))
		return false;

	Texture = FindTexture(TexName);

	return m_AnimationManager->CreateAnimationSequence(Name, Texture);
}

#endif

bool CResourceManager::AddAnimationFrame(const std::string& Name,
	const Vector2& Start, const Vector2& End)
{
	return m_AnimationManager->AddAnimationFrame(Name, Start, End);
}

bool CResourceManager::AddAnimationFrame(const std::string& Name, float PosX, 
	float PosY, float SizeX, float SizeY)
{
	return m_AnimationManager->AddAnimationFrame(Name, PosX, PosY, SizeX, SizeY);
}

CAnimationSequence* CResourceManager::FindAnimation(const std::string& Name)
{
	return m_AnimationManager->FindAnimation(Name);
}

void CResourceManager::ReleaseAnimation(const std::string& Name)
{
	m_AnimationManager->ReleaseAnimation(Name);
}
