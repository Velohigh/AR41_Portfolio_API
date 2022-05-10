
#include "Player.h"
#include "../Scene/Scene.h"
#include "Bullet.h"
#include "Tornado.h"

CPlayer::CPlayer()
{
	SetTypeID<CPlayer>();	// 최하위 객체이므로 타입ID설정
}

CPlayer::CPlayer(const CPlayer& Obj)	:
	CCharacter(Obj)
{
}

CPlayer::~CPlayer()
{
}

bool CPlayer::Init()
{
	m_GunAngle = 0.f;
	m_GunLength = 70.f;

	SetPos(100.f, 100.f);
	SetSize(100.f, 100.f);
	SetPivot(0.5f, 0.5f);

	return true;
}

void CPlayer::Update(float DeltaTime)
{
	// VK_RETURN : Enter키
	// VK_F1 : F1키
	// VK_LBUTTON : 왼쪽 마우스 버튼
	// GetAsyncKeyState : 키의 상태를 체크할 수 있다.
	// 반환값
	// 0 : 해당 키가 눌러진 상태가 아니다.
	// 0x8000 : 해당 키를 지금 누르고 있는 상태이다.
	// 0x1 : 해당 키를 이전 프레임에 눌렀다.
	if (GetAsyncKeyState('A') & 0x8000)
	{
		//m_Pos.x -= 100.f * DeltaTime;
		m_GunAngle -= 180.f * DeltaTime;
	}

	if (GetAsyncKeyState('D') & 0x8000)
	{
		//m_Pos.x += 100.f * DeltaTime;
		m_GunAngle += 180.f * DeltaTime;
	}

	m_GunPos.x = m_Pos.x + cosf(DegreeToRadian(m_GunAngle)) * m_GunLength;
	m_GunPos.y = m_Pos.y + sinf(DegreeToRadian(m_GunAngle)) * m_GunLength;

	if (GetAsyncKeyState('W') & 0x8000)
	{
		Vector2 Dir;
		Dir.x = cosf(DegreeToRadian(m_GunAngle));
		Dir.y = sinf(DegreeToRadian(m_GunAngle));

		m_Pos += Dir * 400.f * DeltaTime;
		//m_Pos.y -= 400.f * DeltaTime;
	}

	if (GetAsyncKeyState('S') & 0x8000)
	{
		Vector2 Dir;
		Dir.x = cosf(DegreeToRadian(m_GunAngle));
		Dir.y = sinf(DegreeToRadian(m_GunAngle));

		m_Pos -= Dir * 400.f * DeltaTime;
		//m_Pos.y += 400.f * DeltaTime;
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		CBullet* Bullet = m_Scene->CreateObject<CBullet>("Bullet");

		Bullet->SetAngle(m_GunAngle);

		Bullet->SetPos(m_GunPos);
	}

	if (GetAsyncKeyState('1') & 0x8000)
	{
		CTornado* Bullet = m_Scene->CreateObject<CTornado>("Tornado");

		Bullet->SetAngle(m_GunAngle);

		Bullet->SetPos(m_GunPos);
	}



}

void CPlayer::Render(HDC hDC, float DeltaTime)
{
	Vector2 RenderLT;

	RenderLT = m_Pos - m_Pivot * m_Size;

	Ellipse(hDC, (int)RenderLT.x, (int)RenderLT.y,
		(int)(RenderLT.x + m_Size.x), (int)(RenderLT.y + m_Size.y));

	MoveToEx(hDC, (int)m_Pos.x, (int)m_Pos.y, nullptr);
	LineTo(hDC, (int)m_GunPos.x, (int)m_GunPos.y);

}
