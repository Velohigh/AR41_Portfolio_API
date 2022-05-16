
#include "Monster.h"
#include "../Scene/Scene.h"
#include "Bullet.h"

CMonster::CMonster()
{
	SetTypeID<CMonster>();
}

CMonster::CMonster(const CMonster& Obj) :
	CCharacter(Obj),
	m_MoveSpeed(Obj.m_MoveSpeed),
	m_Dir(Obj.m_Dir),
	m_FireTime(Obj.m_FireTime),
	m_FireCount(Obj.m_FireCount)
{
}

CMonster::~CMonster()
{
}

bool CMonster::Init()
{
	m_MoveSpeed = 300.f;
	m_FireTime = 0.f;
	m_Dir = 1;
	m_FireCount = 0;

	SetPos(900.f, 100.f);
	SetSize(100.f, 100.f);
	SetPivot(0.5f, 0.5f);

	SetTexture("Monster", TEXT("teemo.bmp"));

	return true;
}

void CMonster::Update(float DeltaTime)
{
	m_Pos.y += m_Dir * m_MoveSpeed * DeltaTime;

	if (m_Pos.y + (1.f - m_Pivot.y) * m_Size.y >= 720.f)
	{
		m_Pos.y = 720.f - (1.f - m_Pivot.y) * m_Size.y;
		m_Dir = -1;
	}

	else if (m_Pos.y - m_Pivot.y * m_Size.y <= 0.f)
	{
		m_Pos.y = m_Pivot.y * m_Size.y;
		m_Dir = 1;
	}

	m_FireTime += DeltaTime;

	if (m_FireTime >= 0.5f)
	{
		m_FireTime -= 0.5f;

		++m_FireCount;

		CBullet* Bullet = m_Scene->CreateObject<CBullet>("Bullet");

		float	BulletX = m_Pos.x - m_Pivot.x * m_Size.x -
			(1.f - Bullet->GetPivot().x) * Bullet->GetSize().x;

		Bullet->SetPos(BulletX, m_Pos.y);

		if (m_FireCount == 3)
		{
			m_FireCount = 0;

			// 플레이어 방향으로 나갈 각도를 구한다.
			float Angle = Bullet->GetPos().Angle(m_Scene->GetPlayer()->GetPos());
			Bullet->SetAngle(Angle);
		}
	}
}

void CMonster::Render(HDC hDC, float DeltaTime)
{
	CCharacter::Render(hDC, DeltaTime);

	//Vector2	RenderLT;

	//RenderLT = m_Pos - m_Pivot * m_Size;

	//Rectangle(hDC, (int)RenderLT.x, (int)RenderLT.y,
//		(int)(RenderLT.x + m_Size.x), (int)(RenderLT.y + m_Size.y));
}
