
#include "EditDlg.h"
#include "../GameManager.h"
#include "../resource.h"
#include "EditScene.h"
#include "../PathManager.h"
#include "SceneResource.h"
#include "../Resource/Texture/Texture.h"

CEditDlg* g_Dlg = nullptr;

CEditDlg::CEditDlg()	:
	m_SelectTextureName{}
{
	g_Dlg = this;
	m_SelectTextureIndex = -1;
}

CEditDlg::~CEditDlg()
{
}

bool CEditDlg::Init()
{
	// Modal : 부모윈도우는 멈추고 열리는 다이얼로그만 동작.
	// Modeless : 부모윈도우와 다이얼로그 모두 동작.
	m_hDlg = CreateDialog(CGameManager::GetInst()->GetWindowInstance(),
		MAKEINTRESOURCE(IDD_DIALOG_EDIT), CGameManager::GetInst()->GetWindowHandle(),
		CEditDlg::WndProc);

	ShowWindow(m_hDlg, SW_SHOW);

	SetDlgItemInt(m_hDlg, IDC_EDIT_COUNTX, 40, TRUE);
	SetDlgItemInt(m_hDlg, IDC_EDIT_COUNTY, 40, TRUE);
	SetDlgItemInt(m_hDlg, IDC_EDIT_SIZEX, 40, TRUE);
	SetDlgItemInt(m_hDlg, IDC_EDIT_SIZEY, 53, TRUE);

	m_hTextureListBox = GetDlgItem(m_hDlg, IDC_LIST_TEXTURE);

	return true;
}

void CEditDlg::CreateTileMap()
{
	BOOL	Transfer = FALSE;

	int	CountX = GetDlgItemInt(m_hDlg, IDC_EDIT_COUNTX, &Transfer, TRUE);
	int	CountY = GetDlgItemInt(m_hDlg, IDC_EDIT_COUNTY, &Transfer, TRUE);
	int	SizeX = GetDlgItemInt(m_hDlg, IDC_EDIT_SIZEX, &Transfer, TRUE);
	int	SizeY = GetDlgItemInt(m_hDlg, IDC_EDIT_SIZEY, &Transfer, TRUE);

	m_Scene->CreateTileMap(CountX, CountY, SizeX, SizeY);
}

void CEditDlg::LoadTexture()
{
	TCHAR	FilePath[MAX_PATH] = {};

	OPENFILENAME	OpenFile = {};

	OpenFile.lStructSize = sizeof(OPENFILENAME);
	OpenFile.hwndOwner = m_hDlg;
	OpenFile.lpstrFilter = TEXT("모든파일\0*.*\0BmpFile\0*.bmp");
	OpenFile.lpstrFile = FilePath;	// FilePath 에 풀경로가 들어온다.
	OpenFile.nMaxFile = MAX_PATH;
	OpenFile.lpstrInitialDir = CPathManager::GetInst()->FindPath(TEXTURE_PATH)->Path;

	if (GetOpenFileName(&OpenFile) != 0)
	{
		TCHAR	FileName[128] = {};

		_wsplitpath_s(FilePath, nullptr, 0, nullptr, 0, FileName, 128, nullptr, 0);

		char	TextureName[128] = {};

#ifdef UNICODE

		// 유니코드로 되어있는 문자열을 멀티바이트로 바꾸기 위한 수를
		// 얻어온다.
		int	PathLength = WideCharToMultiByte(CP_ACP, 0, FileName, -1,
			0, 0, 0, 0);

		WideCharToMultiByte(CP_ACP, 0, FileName, -1,
			TextureName, PathLength, 0, 0);

#else

		strcpy_s(TextureName, FileName);

#endif // UNICODE

		// ListBox에 Texture 이름을 추가한다.
		SendMessage(m_hTextureListBox, LB_ADDSTRING, 0, (LPARAM)FileName);
		
		if (!m_Scene->GetSceneResource()->LoadTextureFullPath(TextureName, FilePath))
			return;

		m_Scene->GetSceneResource()->SetColorKey(TextureName, 255, 0, 255);
	}
}

void CEditDlg::SelectTexture()
{
	// 리스트박스에서 현재 선택된 셀의 인덱스를 얻어오도록 한다.
	m_SelectTextureIndex = (int)SendMessage(m_hTextureListBox, LB_GETCURSEL, 0, 0);

	if (m_SelectTextureIndex != -1)
	{
		memset(m_SelectTextureName, 0, sizeof(TCHAR) * 128);
		SendMessage(m_hTextureListBox, LB_GETTEXT, m_SelectTextureIndex, (LPARAM)m_SelectTextureName);

		char	TextureName[128] = {};

#ifdef UNICODE

		// 유니코드로 되어있는 문자열을 멀티바이트로 바꾸기 위한 수를
		// 얻어온다.
		int	PathLength = WideCharToMultiByte(CP_ACP, 0, m_SelectTextureName, -1,
			0, 0, 0, 0);

		WideCharToMultiByte(CP_ACP, 0, m_SelectTextureName, -1,
			TextureName, PathLength, 0, 0);

#else

		strcpy_s(TextureName, FileName);

#endif // UNICODE

		m_SelectTexture = m_Scene->GetSceneResource()->FindTexture(TextureName);

		m_Scene->SetTileTexture(m_SelectTexture);

		m_SelectTextureIndex = -1;
	}
}

LRESULT CEditDlg::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_CREATE_TILEMAP:
			g_Dlg->CreateTileMap();
			break;
		case IDC_BUTTON_LOADTEXTURE:
			g_Dlg->LoadTexture();
			break;
		case IDC_LIST_TEXTURE:
			switch (HIWORD(wParam))
			{
			case LBN_SELCHANGE:
				g_Dlg->SelectTexture();
				break;
			}
			break;
		}
		break;
	default:
		break;
	}

	return 0;
}
