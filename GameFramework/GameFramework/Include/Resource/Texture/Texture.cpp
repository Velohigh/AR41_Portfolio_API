
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
	// ������ ������� �����ش�.
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

	// ȭ��DC�� �ְ� �޸� DC�� ��´�.
	m_hMemDC = CreateCompatibleDC(CGameManager::GetInst()->GetWindowDC());

	// ��Ʈ���� �ε��Ѵ�.
	m_hBmp = (HBITMAP)LoadImage(CGameManager::GetInst()->GetWindowInstance(),
		FullPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	if (!m_hBmp)
		return false;

	// �о�� ��Ʈ���� �޸� DC�� �����Ѵ�.
	// ������ DC�� ������ �ִ� ������ ��ȯ�Ѵ�.
	m_hPrevBmp = (HBITMAP)SelectObject(m_hMemDC, m_hBmp);

	GetObject(m_hBmp, sizeof(BITMAP), &m_BmpInfo);

	return true;
}
