#include "GameManager.h"
// IconID�� ����ϱ� ���ؼ� ���Խ�Ų��.
#include "resource.h"
#include "Timer.h"
#include "GameObject/Player.h"
#include "Scene/SceneManager.h"
#include "Input.h"

DEFINITION_SINGLE(CGameManager)
bool CGameManager::m_Loop = true;


CGameManager::CGameManager()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(100); //Leak�������� ã�� ���� �Լ�
}

CGameManager::~CGameManager()
{
    CSceneManager::DestroyInst();

    CInput::DestroyInst();

    SAFE_DELETE(m_Timer);

    // ���α׷��� ����ɶ� DC�� �����Ѵ�.
    ReleaseDC(m_hWnd, m_hDC);

}

bool CGameManager::Init(HINSTANCE hInst)
{
	m_hInst = hInst;

	// ������Ŭ���� ����ü�� ������ְ� ����Ѵ�.
	Register();

	// ������ â�� �����ϰ� �����ش�.
	Create();

    // �Է°����� �ʱ�ȭ
    if (!CInput::GetInst()->Init())
        return false;

    // �������� ����
    if (!CSceneManager::GetInst()->Init())
        return false;

    // Ÿ�̸� ����
    m_Timer = new CTimer;
    m_Timer->Init();

    // DC�� ���´�.
    m_hDC = GetDC(m_hWnd);

    m_FrameLimitTime = 1 / 60.f;

	return true;
}

int CGameManager::Run()
{
    // �ü���� ������� �޼����� ������ ���� ����ü�̴�.
    MSG msg;

    // GetMessage : �޼��� ť���� �޼����� �������� �Լ��̴�.
    // ��, �޼��� ť�� ������� ��� �޼����� ���ö����� �� �Լ��� �������� �� ����.
    // �̷��� ���缭 ����ϰ� �ִ� ���� ���ŷ ��� ��� �Ѵ�.
    // ť�� �� �����ִ� �ð��� �������� ����Ÿ���̶�� �θ���.
    while (m_Loop)
    {
        // PeekMessage : �� �Լ��� �޼��� ť���� �޼����� ��������
        // �Լ��̴�. ��, �� �Լ��� �޼��� ť�� ������� ��� false
        // �� ��ȯ�ϸ� �ٷ� ���������� �ȴ�.
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            // �޼���ť���� ������ �޼����� TranslateMessage �Լ��� �Ѱ��ָ� ���� Ű���� 
            // F1, ����Ű ���� Ű������ �Ǵ����ش�.
            // �̷��� Ű���� WM_KEYDOWN���� �޼����� �ν��� �ǰ�
            // ���� Ű�� WM_CHAR�� �ν��� �ȴ�.
            // Ű�� ������ ����Ű�� ��� WM_CHAR�� ����������ϱ� ������ WM_KEYDOWN
            // �� �Ͼ�� ����Ű�� ��� WM_CHAR�޼����� �߰��� ���� �޼��� ť��
            // �־��ش�.
            TranslateMessage(&msg);

            // DispatchMessage �Լ��� �޼���ť���� ������ �޼����� �޼��� ó�� �Լ���
            // �����ش�. WndProc�� �����ִ� ���̴�.
            DispatchMessage(&msg);
        }

        // �޼��� ť�� ������� ��� ���۵ȴ�. ��, �������� ����Ÿ�ӽ�
        // �� else ������ ���۵Ǳ� ������ ���⿡ ���� ���ӷ�����
        // �ۼ��ϸ� �ȴ�.
        else
        {
            Logic();
        }
    }

    return (int)msg.wParam;
}

void CGameManager::Logic()
{
    // Ÿ�̸Ӹ� �����Ͽ� ��Ÿ�� �� FPS �� ���Ѵ�.
    m_Timer->Update();

    float DeltaTime = m_Timer->GetDeltaTime();

    Input(DeltaTime);

    // Scene �� ��ü�� ��� ó������ �ٽ� ���۽�Ų��.
    if (Update(DeltaTime))
        return;

    Collision(DeltaTime);

    Render(DeltaTime);
}

void CGameManager::Input(float DeltaTime)
{
    CInput::GetInst()->Update(DeltaTime);
}

bool CGameManager::Update(float DeltaTime)
{
    return CSceneManager::GetInst()->Update(DeltaTime);
}

void CGameManager::Collision(float DeltaTime)
{
}

void CGameManager::Render(float DeltaTime)
{
    CSceneManager::GetInst()->Render(m_hDC, DeltaTime);

    //// �����ڵ�� �Ǽ� ���ڿ� ó���� ����� �ȵȴ�. ���� ��Ƽ����Ʈ�� ó���Ѵ�.
    //char FPSText[64] = {};

    //sprintf_s(FPSText, "DeltaTime : %.5f", DeltaTime);

    //TextOutA(m_hDC, 1000, 50, FPSText, strlen(FPSText));

    //// TextOutA : ��Ƽ����Ʈ ���ڿ�(char ���ڿ�)�� ����ϴ� �Լ��̴�.
    //// TextOutW : �����ڵ� ���ڿ�(wchar_t ���ڿ�)�� ����ϴ� �Լ��̴�.
    //// TextOut : ���� ������Ʈ�� ������ ��Ƽ����Ʈ�� �����ڵ�Ŀ� ���� ���� �� �Լ��� �ϳ��� �����ȴ�.
    //TextOut(m_hDC, 50, 50, TEXT("�ؽ�Ʈ ���"), lstrlen(TEXT("�ؽ�Ʈ ���")));
}

void CGameManager::Register()
{
    // �������Ϳ� ����� ������ Ŭ���� ����ü�� ������ش�.
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;

    // �޼���ť���� ������ �޼����� ���ڷ� �����ϸ� ȣ���� �Լ��� �Լ� �ּҸ�
    // ����Ѵ�.
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;

    // ������ �ν��Ͻ��� ����Ѵ�.
    wcex.hInstance = m_hInst;

    // �������Ͽ� ����� �������� ����Ѵ�.
    wcex.hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_ICON1));

    // ���콺 Ŀ�� ����� �����Ѵ�.
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    // �޴��� ������� ������ �����Ѵ�.
    wcex.lpszMenuName = nullptr;// MAKEINTRESOURCEW(IDC_MY220428);

    // ����� Ŭ������ �̸��� �����ڵ� ���ڿ��� ���� �����Ѵ�.
    // TEXT ��ũ�δ� ������Ʈ ������ �����ڵ�� �Ǿ����� ��� �����ڵ� ���ڿ��� ���������
    // ��Ƽ����Ʈ�� �Ǿ����� ��� ��Ƽ����Ʈ ���ڿ��� ��������� �ȴ�.
    wcex.lpszClassName = TEXT("GameFramework");

    // ������â �»�ܿ� ǥ���� ���� �������� ����Ѵ�.
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

    RegisterClassExW(&wcex);
}

bool CGameManager::Create()
{
    // ������ â�� �����Ѵ�.
    // 1�� ���ڴ� ������ Ŭ������ ����� �̸��̴�.
    // 2�� ���ڴ� Ÿ��Ʋ�ٿ� ǥ���� �̸��̴�.
    // 3�����ڴ� �� ������ â�� ��� ���������� �����ϴ� �ɼ��̴�.
    // 4, 5�� ���ڴ� �� ������ â�� ������ ȭ�鿡���� ��ġ�� �����Ѵ�.
    // �ȼ��� �����Ѵ�. ���� ��� 1920, 1080 �ػ󵵶�� �ű⿡�� ���ϴ� ���� �־��ָ�
    // �ش� ��ġ�� ������ �ȴ�.
    // 4���� ������ǥ, 5���� ������ǥ�� ����� �ȴ�.
    // 6��, 7�� ���ڴ� ������â�� ����, ������ ũ�⸦ �����Ѵ�.
    // �ȼ������� ������ ���ش�.
    // 8�� ���ڴ� �θ������찡 �ִٸ� �θ��������� �ڵ��� �����Ѵ�.
    // ������ nullptr�� �����Ѵ�.
    // 9�� ���ڴ� �޴��� �ִٸ� �޴� �ڵ��� �־��ְ� ������ nullptr�� �����Ѵ�.
    // 10�� ���ڴ� ������ �ν��Ͻ��� �����Ͽ� �� ������ �ν��Ͻ��� ���� ������ â��
    // ������ְ� �ȴ�.
    // ������ â�� ������ְ� ���������� ��������ٸ� ������ ������ â�� �ڵ���
    // ��ȯ���ش�.
    // HWND �� ������ �ڵ��� �ǹ��Ѵ�.
    // ���� ������ ����� �ȵǾ��ٸ� 0�� ��ȯ�Ѵ�.
    m_hWnd = CreateWindowW(TEXT("GameFramework"),
        TEXT("GameFramework"), WS_OVERLAPPEDWINDOW,
        100, 0, 0, 0, nullptr, nullptr, m_hInst, nullptr);

    if (!m_hWnd)
    {
        return false;
    }

    // RECT : �簢���� ǥ���ϱ� ���ؼ� �����ϴ� ����ü�̴�.
    // left, top, right, bottom ������ �̷���� �ִ�.
    // ������ ũ�⸦ ǥ���ϴ� Rect ����ü�� �ϳ� ������ش�.
    RECT    rc = { 0, 0, 1280, 720 };

    // ������ ������ ũ�⸸ŭ Ŭ���̾�Ʈ ������ ũ��� ��� ���ؼ�
    // �ʿ��� ���� �������� ũ�⸦ ���´�.
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

    // ������ ���� ũ��� ������ â�� ũ�⸦ �����Ѵ�.
    MoveWindow(m_hWnd, 50, 50, rc.right - rc.left,
        rc.bottom - rc.top, TRUE);

    // ������ â�� �����ش�. 1�����ڿ� �� �ڵ��� ������ â�� �������� ������
    // �������ش�.
    ShowWindow(m_hWnd, SW_SHOW);

    // �� �Լ��� ȣ���Ͽ� Ŭ���̾�Ʈ ������ ����� ���ŵǾ��ٸ� 0�� �ƴ� ���� ��ȯ�ϰ�
    // ������ �������� ��� 0�� ��ȯ�Ѵ�.
    UpdateWindow(m_hWnd);

    return true;
}

LRESULT CGameManager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        // �����찡 ����ɶ� ������ �޼����̴�.
        m_Loop = false;
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
