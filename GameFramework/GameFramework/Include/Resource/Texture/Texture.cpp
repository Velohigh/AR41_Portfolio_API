
#include "Texture.h"
#include "../../PathManager.h"
#include "../../GameManager.h"

CTexture::CTexture()	:
	m_hMemDC(0),
	m_hBmp(0),
	m_hPrevBmp(0),
	m_BmpInfo{}
{
}

CTexture::~CTexture()
{
	// 도구를 원래대로 돌려준다.
	SelectObject(m_hMemDC, m_hPrevBmp);
	DeleteObject(m_hBmp);
	DeleteDC(m_hMemDC);
}

bool CTexture::LoadTexture(const TCHAR* FileName, 
	const std::string& PathName)
{
	const PathInfo* Path = CPathManager::GetInst()->FindPath(PathName);

	TCHAR	FullPath[MAX_PATH] = {};

	if (Path)
		lstrcpy(FullPath, Path->Path);

	lstrcat(FullPath, FileName);

	// 화면DC를 넣고 메모리 DC를 얻는다.
	m_hMemDC = CreateCompatibleDC(CGameManager::GetInst()->GetWindowDC());

	// 비트맵을 로딩한다.
	m_hBmp = (HBITMAP)LoadImage(CGameManager::GetInst()->GetWindowInstance(),
		FullPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	if (!m_hBmp)
		return false;

	// 읽어온 비트맵을 메모리 DC에 지정한다.
	// 기존에 DC가 가지고 있던 도구를 반환한다.
	m_hPrevBmp = (HBITMAP)SelectObject(m_hMemDC, m_hBmp);

	GetObject(m_hBmp, sizeof(BITMAP), &m_BmpInfo);

	return true;
}
