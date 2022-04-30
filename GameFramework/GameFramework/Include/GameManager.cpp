#include "GameManager.h"
// IconID�� ����ϱ� ���ؼ� ���Խ�Ų��.
#include "resource.h"

DEFINITION_SINGLE(CGameManager)
bool CGameManager::m_Loop = true;


CGameManager::CGameManager()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(100); //Leak�������� ã�� ���� �Լ�
}

CGameManager::~CGameManager()
{


}

bool CGameManager::Init(HINSTANCE hInst)
{
	m_hInst = hInst;

	// ������Ŭ���� ����ü�� ������ְ� ����Ѵ�.
	Register();

	// ������ â�� �����ϰ� �����ش�.
	Create();

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
    Input(0.f);
    Update(0.f);
    Collision(0.f);
    Render(0.f);
}

void CGameManager::Input(float DeltaTime)
{
}

void CGameManager::Update(float DeltaTime)
{
}

void CGameManager::Collision(float DeltaTime)
{
}

void CGameManager::Render(float DeltaTime)
{
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
