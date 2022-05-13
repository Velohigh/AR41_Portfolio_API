
#include "Texture.h"
#include "../../PathManager.h"
#include "../../GameManager.h"

CTexture::CTexture()	:
	m_Type(ETexture_Type::Sprite)
{
}

CTexture::~CTexture()
{
	size_t	Size = m_vecImageInfo.size();

	for (size_t i = 0; i < Size; ++i)
	{
		SAFE_DELETE(m_vecImageInfo[i]);
	}
}

bool CTexture::LoadTexture(const TCHAR* FileName, 
	const std::string& PathName)
{
	const PathInfo* Path = CPathManager::GetInst()->FindPath(PathName);

	TCHAR	FullPath[MAX_PATH] = {};

	if (Path)
		lstrcpy(FullPath, Path->Path);

	lstrcat(FullPath, FileName);

	return LoadTextureFullPath(FullPath);
}

bool CTexture::LoadTextureFullPath(const TCHAR* FullPath)
{
	// 화면DC를 넣고 메모리 DC를 얻는다.
	HDC	hDC = CreateCompatibleDC(CGameManager::GetInst()->GetWindowDC());

	// 비트맵을 로딩한다.
	HBITMAP	hBmp = (HBITMAP)LoadImage(CGameManager::GetInst()->GetWindowInstance(),
		FullPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	if (!hBmp)
		return false;

	// 읽어온 비트맵을 메모리 DC에 지정한다.
	// 기존에 DC가 가지고 있던 도구를 반환한다.
	HBITMAP hPrevBmp = (HBITMAP)SelectObject(hDC, hBmp);

	BITMAP	BmpInfo;

	GetObject(hBmp, sizeof(BITMAP), &BmpInfo);

	ImageInfo* Info = new ImageInfo;

	Info->hMemDC = hDC;
	Info->hBmp = hBmp;
	Info->hPrevBmp = hPrevBmp;
	Info->BmpInfo = BmpInfo;

	m_vecImageInfo.push_back(Info);

	return true;
}

#ifdef UNICODE

bool CTexture::LoadTexture(const std::vector<std::wstring>& vecFileName,
	const std::string& PathName)
{
	m_Type = ETexture_Type::Frame;

	const PathInfo* Path = CPathManager::GetInst()->FindPath(PathName);

	std::vector<std::wstring>	vecFullPath;

	size_t	Size = vecFileName.size();

	// 미리 개수만큼 push 해놓는 효과이다.
	vecFullPath.resize(Size);

	// 미리 배열 공간을 확보하여 꽉 찼을때 공간 재할당이 일어나는것을 방지해주는
	// 역할을 할때 사용한다.
	//vecFullPath.reserve(Size);

	for (size_t i = 0; i < Size; ++i)
	{
		if (Path)
			vecFullPath[i] = Path->Path;

		vecFullPath[i] += vecFileName[i];
	}

	return LoadTextureFullPath(vecFullPath);
}

bool CTexture::LoadTextureFullPath(const std::vector<std::wstring>& vecFullPath)
{
	m_Type = ETexture_Type::Frame;

	size_t	Size = vecFullPath.size();

	for (size_t i = 0; i < Size; ++i)
	{
		// 화면DC를 넣고 메모리 DC를 얻는다.
		HDC	hDC = CreateCompatibleDC(CGameManager::GetInst()->GetWindowDC());

		// 비트맵을 로딩한다.
		// string 이나 wstring 클래스의 c_str() 함수는 문자열 포인터를 얻어온다.
		HBITMAP	hBmp = (HBITMAP)LoadImage(CGameManager::GetInst()->GetWindowInstance(),
			vecFullPath[i].c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

		if (!hBmp)
			return false;

		// 읽어온 비트맵을 메모리 DC에 지정한다.
		// 기존에 DC가 가지고 있던 도구를 반환한다.
		HBITMAP hPrevBmp = (HBITMAP)SelectObject(hDC, hBmp);

		BITMAP	BmpInfo;

		GetObject(hBmp, sizeof(BITMAP), &BmpInfo);

		ImageInfo* Info = new ImageInfo;

		Info->hMemDC = hDC;
		Info->hBmp = hBmp;
		Info->hPrevBmp = hPrevBmp;
		Info->BmpInfo = BmpInfo;

		m_vecImageInfo.push_back(Info);
	}

	return true;
}

#else

bool CTexture::LoadTexture(const std::vector<std::string>& vecFileName,
	const std::string& PathName)
{
	m_Type = ETexture_Type::Frame;

	const PathInfo* Path = CPathManager::GetInst()->FindPath(PathName);

	std::vector<std::string>	vecFullPath;

	size_t	Size = vecFileName.size();

	// 미리 개수만큼 push 해놓는 효과이다.
	vecFullPath.resize(Size);

	// 미리 배열 공간을 확보하여 꽉 찼을때 공간 재할당이 일어나는것을 방지해주는
	// 역할을 할때 사용한다.
	//vecFullPath.reserve(Size);

	for (size_t i = 0; i < Size; ++i)
	{
		if (Path)
			vecFullPath[i] = Path->Path;

		vecFullPath[i] += vecFileName[i];
	}

	return LoadTextureFullPath(vecFullPath);
}

bool CTexture::LoadTextureFullPath(const std::vector<std::string>& vecFullPath)
{
	m_Type = ETexture_Type::Frame;

	size_t	Size = vecFullPath.size();

	for (size_t i = 0; i < Size; ++i)
	{
		// 화면DC를 넣고 메모리 DC를 얻는다.
		HDC	hDC = CreateCompatibleDC(CGameManager::GetInst()->GetWindowDC());

		// 비트맵을 로딩한다.
		// string 이나 wstring 클래스의 c_str() 함수는 문자열 포인터를 얻어온다.
		HBITMAP	hBmp = (HBITMAP)LoadImage(CGameManager::GetInst()->GetWindowInstance(),
			vecFullPath[i].c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

		if (!hBmp)
			return false;

		// 읽어온 비트맵을 메모리 DC에 지정한다.
		// 기존에 DC가 가지고 있던 도구를 반환한다.
		HBITMAP hPrevBmp = (HBITMAP)SelectObject(hDC, hBmp);

		BITMAP	BmpInfo;

		GetObject(hBmp, sizeof(BITMAP), &BmpInfo);

		ImageInfo* Info = new ImageInfo;

		Info->hMemDC = hDC;
		Info->hBmp = hBmp;
		Info->hPrevBmp = hPrevBmp;
		Info->BmpInfo = BmpInfo;

		m_vecImageInfo.push_back(Info);
	}

	return true;
}

#endif // UNICODE
