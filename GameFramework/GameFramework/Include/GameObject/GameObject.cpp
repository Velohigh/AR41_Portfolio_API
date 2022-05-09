#include "GameObject.h"

CGameObject::CGameObject()
{
	SetTypeID<CGameObject>();
}

CGameObject::CGameObject(const CGameObject& Obj) :
	CRef(Obj),
	m_Pos(Obj.m_Pos),
	m_Size(Obj.m_Size),
	m_Pivot(Obj.m_Pivot)
{
}

CGameObject::~CGameObject()
{
}

bool CGameObject::Init()
{
	return true;
}

void CGameObject::Update(float DeltaTime)
{
}

void CGameObject::Render(HDC hDC, float DeltaTime)
{
}
