
#include "ColliderBox.h"
#include "../GameObject/GameObject.h"
#include "../GameManager.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "CollisionManager.h"
#include "ColliderCircle.h"

CColliderBox::CColliderBox()	:
	m_Width(100.f),
	m_Height(100.f)
{
	SetTypeID<CColliderBox>();

	m_ColliderType = ECollider_Type::Box;
}

CColliderBox::CColliderBox(const CColliderBox& collider) :
	CCollider(collider),
	m_Width(collider.m_Width),
	m_Height(collider.m_Height),
	m_Info(collider.m_Info)
{
}

CColliderBox::~CColliderBox()
{
}

bool CColliderBox::Init()
{
	if (!CCollider::Init())
		return false;

	return true;
}

void CColliderBox::Update(float DeltaTime)
{
	CCollider::Update(DeltaTime);
}

void CColliderBox::PostUpdate(float DeltaTime)
{
	CCollider::PostUpdate(DeltaTime);

	Vector2 Pos = m_Owner->GetPos();
	Vector2 Size(m_Width, m_Height);

	m_Info.LT = Pos + m_Offset - Size / 2.f;
	m_Info.RB = Pos + m_Offset + Size / 2.f;
}

void CColliderBox::Render(HDC hDC, float DeltaTime)
{
	CCollider::Render(hDC, DeltaTime);

#ifdef _DEBUG

	HBRUSH Brush = CGameManager::GetInst()->GetBrush(EBrush_Type::Green);

	// 비어있지 않을경우 누군가와 충돌중이다.
	if (!m_CollisionList.empty())
		Brush = CGameManager::GetInst()->GetBrush(EBrush_Type::Red);

	CCamera* Camera = m_Scene->GetCamera();

	RECT	RenderRC;

	RenderRC.left = (long)(m_Info.LT.x - Camera->GetPos().x);
	RenderRC.top = (long)(m_Info.LT.y - Camera->GetPos().y);
	RenderRC.right = (long)(m_Info.RB.x - Camera->GetPos().x);
	RenderRC.bottom = (long)(m_Info.RB.y - Camera->GetPos().y);

	FrameRect(hDC, &RenderRC, Brush);

#endif // _DEBUG
}

bool CColliderBox::Collision(CCollider* Dest)
{
	switch (Dest->GetColliderType())
	{
	case ECollider_Type::Box:
		return CCollisionManager::GetInst()->CollisionBoxToBox(m_HitPoint, this, (CColliderBox*)Dest);
	case ECollider_Type::Circle:
		break;
	}

	return false;
}
