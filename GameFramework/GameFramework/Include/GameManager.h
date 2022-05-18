#pragma once

#include "GameInfo.h"
#include "SingletonMacro.h"

/*
������ �帧�� �����ϴ� �ܰ�
1. ������� �Է�
2. �Է¹��� ���뿡 ���ؼ� ������ ������Ʈ
�ΰ����ɵ��� ������ ������Ʈ
3. ������Ʈ�� �����͸� ���� �浹�� ����.
4. ����� �Ǿ�� �ϴ� ��ü���� �Ǵ�.
5. ȭ�鿡 ����� �Ǿ�� �ϴ� ��ü���� ���.
*/

// ������ â�� �����ϰ� ��ü ������ �����ϴ� Ŭ�����̴�.
class CGameManager
{
private:
	HINSTANCE	m_hInst;
	HWND		m_hWnd;
	HDC			m_hDC;
	HDC			m_hBackDC;
	HBITMAP		m_hBackBmp;
	HBITMAP		m_hBackPrevBmp;

	class CTimer* m_Timer;
	float		m_FrameLimitTime;
	float		m_DeltaTime;

	Resolution	m_RS;


	float		m_TimeScale;	// �۷ι� Ÿ�� ��� ����.(�̰� �ؾߵ�)






	//class CPlayer* m_Player;

	//RECT		m_TestRC;
	//int			m_Dir;

	// �� ������ static ��������� ������ ������ wndProc static ���
	// �Լ����� �� ������ �����찡 ����ɶ� false�� ������ֱ� ���ؼ�
	// static ��������� ������־���.
	static bool	m_Loop;

public:
	Resolution GetResolution()	const
	{
		return m_RS;
	}

	float GetDeltaTime()	const
	{
		return m_DeltaTime;
	}

	HDC GetWindowDC()	const
	{
		return m_hDC;
	}

	HWND GetWindowHandle()	const
	{
		return m_hWnd;
	}

	HINSTANCE GetWindowInstance()	const
	{
		return m_hInst;
	}

	float GetTimeScale()	const
	{
		return m_TimeScale;
	}

public:
	void SetTimeScale(float Scale)
	{
		m_TimeScale = Scale;
	}

public:
	bool Init(HINSTANCE hInst);
	int Run();

private:
	void Logic();
	void Input(float DeltaTime);
	bool Update(float DeltaTime);
	void PostUpdate(float DeltaTime);
	void Collision(float DeltaTime);
	void Render(float DeltaTime);


private:
	void Register();
	bool Create();

private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	DECLARE_SINGLE(CGameManager)
};

