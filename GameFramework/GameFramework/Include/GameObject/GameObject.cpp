
#include "GameObject.h"
#include "../Resource/ResourceManager.h"
#include "../Resource/Texture/Texture.h"

CGameObject::CGameObject()	:
	m_Scene(nullptr)
{
	SetTypeID<CGameObject>();
}

CGameObject::CGameObject(const CGameObject& Obj)	:
	CRef(Obj),
	m_Scene(nullptr),
	m_Pos(Obj.m_Pos),
	m_Size(Obj.m_Size),
	m_Pivot(Obj.m_Pivot)
{
}

CGameObject::~CGameObject()
{
}

void CGameObject::SetTexture(const std::string& Name)
{
	m_Texture = CResourceManager::GetInst()->FindTexture(Name);
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
	if (m_Texture)
	{
		Vector2	RenderLT;

		RenderLT = m_Pos - m_Pivot * m_Size;

		BitBlt(hDC, (int)RenderLT.x, (int)RenderLT.y, 
			(int)m_Size.x, (int)m_Size.y, m_Texture->GetDC(),
			0, 0, SRCCOPY);
	}
}
