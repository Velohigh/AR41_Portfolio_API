
#include "ColliderBox.h"

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
}

void CColliderBox::Render(HDC hDC, float DeltaTime)
{
	CCollider::Render(hDC, DeltaTime);
}