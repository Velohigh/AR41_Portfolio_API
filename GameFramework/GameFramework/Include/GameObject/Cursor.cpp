
#include "Cursor.h"
#include "../Scene/Scene.h"
#include "../Input.h"

CCursor::CCursor()
{
}

CCursor::CCursor(const CCursor& Obj) :
	CGameObject(Obj)
{
}

CCursor::~CCursor()
{
}

bool CCursor::Init()
{
	CGameObject::Init();

	SetSize(25.f, 25.f);
	SetPivot(0.5f, 0.5f);
	SetTexture("cursor", TEXT("cursor.bmp"));
	m_RenderLayer = ERender_Layer::UI;

	SetRenderScale(2);
	return true;
}

void CCursor::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	Vector2 Pos = CInput::GetInst()->GetMouseWorldPos();
	SetPos(Pos);

}

void CCursor::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CCursor::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);
}
