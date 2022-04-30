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

	// �� ������ static ��������� ������ ������ wndproc static
	// ����Լ����� �� ������ �����찡 ����� �� false�� ������ֱ�
	// ���ؼ� static ��� ������ ������־���.
	// static����Լ������� �Ϲݸ�������� ����Ҽ� ���⶧��!
	static bool	m_Loop;

public:
	bool Init(HINSTANCE hInst);
	int Run();

private:
	void Logic();
	void Input(float DeltaTime);
	void Update(float DeltaTime);
	void Collision(float DeltaTime);
	void Render(float DeltaTime);

private:
	void Register();
	bool Create();

private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	DECLARE_SINGLE(CGameManager);
};

