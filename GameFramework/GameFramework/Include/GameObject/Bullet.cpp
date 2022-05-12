
#include "Bullet.h"

CBullet::CBullet()
{
	SetTypeID<CBullet>();
}

CBullet::CBullet(const CBullet& Obj) :
	CGameObject(Obj),
	m_MoveSpeed(Obj.m_MoveSpeed),
	m_Angle(Obj.m_Angle),
	m_Distance(Obj.m_Distance)
{
}

CBullet::~CBullet()
{
}

bool CBullet::Init()
{
	m_MoveSpeed = 700.f;
	m_Distance = 600.f;
	m_Angle = 180.f;

	SetPos(900.f, 100.f);
	SetSize(50.f, 50.f);
	SetPivot(0.5f, 0.5f);

	return true;
}

void CBullet::Update(float DeltaTime)
{
	m_Pos.x = m_Pos.x + cosf(DegreeToRadian(m_Angle)) * m_MoveSpeed * DeltaTime;
	m_Pos.y = m_Pos.y + sinf(DegreeToRadian(m_Angle)) * m_MoveSpeed * DeltaTime;

	m_Distance -= m_MoveSpeed * DeltaTime;

	if (m_Distance <= 0.f)
		SetActive(false);
}

void CBullet::Render(HDC hDC, float DeltaTime)
{
	Vector2	RenderLT;

	RenderLT = m_Pos - m_Pivot * m_Size;

	Ellipse(hDC, (int)RenderLT.x, (int)RenderLT.y,
		(int)(RenderLT.x + m_Size.x), (int)(RenderLT.y + m_Size.y));
}
