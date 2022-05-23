
#include "ColliderCircle.h"
#include "../GameObject/GameObject.h"
#include "../GameManager.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "CollisionManager.h"
#include "ColliderBox.h"

CColliderCircle::CColliderCircle()
{
	SetTypeID<CColliderCircle>();

	m_ColliderType = ECollider_Type::Circle;

	m_Info.Radius = 30.f;
}

CColliderCircle::CColliderCircle(const CColliderCircle& collider) :
	CCollider(collider),
	m_Info(collider.m_Info)
{
}

CColliderCircle::~CColliderCircle()
{
}

bool CColliderCircle::Init()
{
	if (!CCollider::Init())
		return false;

	return true;
}

void CColliderCircle::Update(float DeltaTime)
{
	CCollider::Update(DeltaTime);
}

void CColliderCircle::PostUpdate(float DeltaTime)
{
	CCollider::PostUpdate(DeltaTime);

	Vector2 Pos = m_Owner->GetPos();
	m_Info.Center = Pos + m_Offset;
}

void CColliderCircle::Render(HDC hDC, float DeltaTime)
{
	CCollider::Render(hDC, DeltaTime);

#ifdef _DEBUG

	HPEN Pen = CGameManager::GetInst()->GetPen(EBrush_Type::Green);

	// ������� ������� �������� �浹���̴�.
	if (!m_CollisionList.empty())
		Pen = CGameManager::GetInst()->GetPen(EBrush_Type::Red);

	HPEN PrevPen = (HPEN)SelectObject(hDC, Pen);

	CCamera* Camera = m_Scene->GetCamera();

	Vector2 Pos = m_Info.Center - Camera->GetPos();

	MoveToEx(hDC, (long)(Pos.x + m_Info.Radius), (long)Pos.y, nullptr);
	 
	for (int i = 12; i <= 360; i += 12)
	{
		Vector2 Target;
		Target.x = Pos.x + cosf(DegreeToRadian((float)i)) * m_Info.Radius;
		Target.y = Pos.y + sinf(DegreeToRadian((float)i)) * m_Info.Radius;

		LineTo(hDC, (long)Target.x, (long)Target.y);
	}

	SelectObject(hDC, PrevPen);

#endif // _DEBUG
}

bool CColliderCircle::Collision(CCollider* Dest)
{
	switch (Dest->GetColliderType())
	{
	case ECollider_Type::Box:
		//return CCollisionManager::GetInst()->CollisionBoxToBox(m_HitPoint, this, (CColliderCircle*)Dest);
		break;
	case ECollider_Type::Circle:
		return CCollisionManager::GetInst()->CollisionCircleToCircle(m_HitPoint, this, (CColliderCircle*)Dest);
	}

	return false;
}

