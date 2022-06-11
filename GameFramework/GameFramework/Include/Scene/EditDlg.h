#pragma once

#include "../GameInfo.h"

class CEditDlg
{
	friend class CEditScene;

private:
	CEditDlg();
	~CEditDlg();

private:
	class CEditScene* m_Scene;
	HWND	m_hDlg;
	HWND	m_hTextureListBox;
	int		m_SelectTextureIndex;
	TCHAR	m_SelectTextureName[128];
	CSharedPtr<class CTexture>	m_SelectTexture;

public:
	bool Init();
	void CreateTileMap();
	void LoadTexture();
	void SelectTexture();

private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

