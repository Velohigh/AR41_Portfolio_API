
#include "SceneResource.h"
#include "../Resource/Texture/Texture.h"
#include "../Resource/ResourceManager.h"
#include "../Resource/Animation/AnimationSequence.h"

CSceneResource::CSceneResource()
{
}

CSceneResource::~CSceneResource()
{
	auto	iter = m_mapTexture.begin();
	auto	iterEnd = m_mapTexture.end();

	for (; iter != iterEnd;)
	{
		std::string	Key = iter->first;

		iter = m_mapTexture.erase(iter);
		iterEnd = m_mapTexture.end();

		CResourceManager::GetInst()->ReleaseTexture(Key);
	}
}

bool CSceneResource::LoadTexture(const std::string& Name, const TCHAR* FileName,
	const std::string& PathName)
{
	if (FindTexture(Name))
		return false;

	if (!CResourceManager::GetInst()->LoadTexture(Name, FileName, PathName))
		return false;

	CTexture* Texture = CResourceManager::GetInst()->FindTexture(Name);

	m_mapTexture.insert(std::make_pair(Name, Texture));

	return true;
}

bool CSceneResource::LoadTextureFullPath(const std::string& Name, 
	const TCHAR* FullPath)
{
	if (FindTexture(Name))
		return false;

	if (!CResourceManager::GetInst()->LoadTextureFullPath(Name, FullPath))
		return false;

	CTexture* Texture = CResourceManager::GetInst()->FindTexture(Name);

	m_mapTexture.insert(std::make_pair(Name, Texture));

	return true;
}

#ifdef UNICODE

bool CSceneResource::LoadTexture(const std::string& Name, 
	const std::vector<std::wstring>& vecFileName, const std::string& PathName)
{
	if (FindTexture(Name))
		return false;

	if (!CResourceManager::GetInst()->LoadTexture(Name, vecFileName, PathName))
		return false;

	CTexture* Texture = CResourceManager::GetInst()->FindTexture(Name);

	m_mapTexture.insert(std::make_pair(Name, Texture));

	return true;
}

bool CSceneResource::LoadTextureFullPath(const std::string& Name, 
	const std::vector<std::wstring>& vecFullPath)
{
	if (FindTexture(Name))
		return false;

	if (!CResourceManager::GetInst()->LoadTextureFullPath(Name, vecFullPath))
		return false;

	CTexture* Texture = CResourceManager::GetInst()->FindTexture(Name);

	m_mapTexture.insert(std::make_pair(Name, Texture));

	return true;
}

#else

bool CSceneResource::LoadTexture(const std::string& Name, 
	const std::vector<std::string>& vecFileName, const std::string& PathName)
{
	if (FindTexture(Name))
		return false;

	if (!CResourceManager::GetInst()->LoadTexture(Name, vecFileName, PathName))
		return false;

	CTexture* Texture = CResourceManager::GetInst()->FindTexture(Name);

	m_mapTexture.insert(std::make_pair(Name, Texture));

	return true;
}

bool CSceneResource::LoadTextureFullPath(const std::string& Name, 
	const std::vector<std::string>& vecFullPath)
{
	if (FindTexture(Name))
		return false;

	if (!CResourceManager::GetInst()->LoadTextureFullPath(Name, vecFullPath))
		return false;

	CTexture* Texture = CResourceManager::GetInst()->FindTexture(Name);

	m_mapTexture.insert(std::make_pair(Name, Texture));

	return true;
}


#endif

bool CSceneResource::SetColorKey(const std::string& Name, unsigned char r, unsigned char g, unsigned char b, int Index)
{
	return CResourceManager::GetInst()->SetColorKey(Name, r, g, b, Index);
}

bool CSceneResource::SetColorKeyAll(const std::string& Name, unsigned char r, unsigned char g, unsigned char b)
{
	return CResourceManager::GetInst()->SetColorKeyAll(Name, r, g, b);
}

CTexture* CSceneResource::FindTexture(const std::string& Name)
{
	auto	iter = m_mapTexture.find(Name);

	if (iter == m_mapTexture.end())
	{
		CTexture* Texture = CResourceManager::GetInst()->FindTexture(Name);

		if (!Texture)
			return nullptr;

		m_mapTexture.insert(std::make_pair(Name, Texture));

		return Texture;
	}

	return iter->second;
}

bool CSceneResource::CreateAnimationSequence(const std::string& Name,
	CTexture* Texture)
{
	if (FindAnimation(Name))
		return false;

	if (!CResourceManager::GetInst()->CreateAnimationSequence(Name, Texture))
		return false;

	CAnimationSequence* Animation = CResourceManager::GetInst()->FindAnimation(Name);

	m_mapAnimationSequence.insert(std::make_pair(Name, Animation));

	return true;
}

bool CSceneResource::CreateAnimationSequence(const std::string& Name,
	const std::string& TexName)
{
	if (FindAnimation(Name))
		return false;

	if (!CResourceManager::GetInst()->CreateAnimationSequence(Name, TexName))
		return false;

	CAnimationSequence* Animation = CResourceManager::GetInst()->FindAnimation(Name);

	m_mapAnimationSequence.insert(std::make_pair(Name, Animation));

	return true;
}

bool CSceneResource::CreateAnimationSequence(const std::string& Name,
	const std::string& TexName, const TCHAR* FileName,
	const std::string& PathName)
{
	if (FindAnimation(Name))
		return false;

	if (!CResourceManager::GetInst()->CreateAnimationSequence(Name, TexName,
		FileName, PathName))
		return false;

	CAnimationSequence* Animation = CResourceManager::GetInst()->FindAnimation(Name);

	m_mapAnimationSequence.insert(std::make_pair(Name, Animation));

	return true;
}

bool CSceneResource::CreateAnimationSequenceFullPath(const std::string& Name,
	const std::string& TexName, const TCHAR* FullPath)
{
	if (FindAnimation(Name))
		return false;

	if (!CResourceManager::GetInst()->CreateAnimationSequenceFullPath(Name, TexName,
		FullPath))
		return false;

	CAnimationSequence* Animation = CResourceManager::GetInst()->FindAnimation(Name);

	m_mapAnimationSequence.insert(std::make_pair(Name, Animation));

	return true;
}

#ifdef UNICODE

bool CSceneResource::CreateAnimationSequence(const std::string& Name,
	const std::string& TexName, const std::vector<std::wstring>& vecFileName,
	const std::string& PathName)
{
	if (FindAnimation(Name))
		return false;

	if (!CResourceManager::GetInst()->CreateAnimationSequence(Name, TexName,
		vecFileName, PathName))
		return false;

	CAnimationSequence* Animation = CResourceManager::GetInst()->FindAnimation(Name);

	m_mapAnimationSequence.insert(std::make_pair(Name, Animation));

	return true;
}

bool CSceneResource::CreateAnimationSequenceFullPath(const std::string& Name,
	const std::string& TexName, const std::vector<std::wstring>& vecFullPath)
{
	if (FindAnimation(Name))
		return false;

	if (!CResourceManager::GetInst()->CreateAnimationSequenceFullPath(Name, TexName,
		vecFullPath))
		return false;

	CAnimationSequence* Animation = CResourceManager::GetInst()->FindAnimation(Name);

	m_mapAnimationSequence.insert(std::make_pair(Name, Animation));

	return true;
}

#else

bool CSceneResource::CreateAnimationSequence(const std::string& Name,
	const std::string& TexName, const std::vector<std::string>& vecFileName, const std::string& PathName)
{
	if (FindAnimation(Name))
		return false;

	if (!CResourceManager::GetInst()->CreateAnimationSequence(Name, TexName,
		vecFileName, PathName))
		return false;

	CAnimationSequence* Animation = CResourceManager::GetInst()->FindAnimation(Name);

	m_mapAnimationSequence.insert(std::make_pair(Name, Animation));

	return true;
}

bool CSceneResource::CreateAnimationSequenceFullPath(const std::string& Name,
	const std::string& TexName, const std::vector<std::string>& vecFullPath)
{
	if (FindAnimation(Name))
		return false;

	if (!CResourceManager::GetInst()->CreateAnimationSequenceFullPath(Name, TexName,
		vecFullPath))
		return false;

	CAnimationSequence* Animation = CResourceManager::GetInst()->FindAnimation(Name);

	m_mapAnimationSequence.insert(std::make_pair(Name, Animation));

	return true;
}

#endif

bool CSceneResource::AddAnimationFrame(const std::string& Name,
	const Vector2& Start, const Vector2& End)
{
	return CResourceManager::GetInst()->AddAnimationFrame(Name, Start, End);
}

bool CSceneResource::AddAnimationFrame(const std::string& Name, float PosX,
	float PosY, float SizeX, float SizeY)
{
	return CResourceManager::GetInst()->AddAnimationFrame(Name, PosX, PosY, SizeX, SizeY);
}

CAnimationSequence* CSceneResource::FindAnimation(const std::string& Name)
{
	auto	iter = m_mapAnimationSequence.find(Name);

	if (iter == m_mapAnimationSequence.end())
	{
		CAnimationSequence* Animation = CResourceManager::GetInst()->FindAnimation(Name);

		if (!Animation)
			return nullptr;

		m_mapAnimationSequence.insert(std::make_pair(Name, Animation));

		return Animation;
	}

	return iter->second;
}
