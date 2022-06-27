
#include "Effect_BloodAnimation2.h"
#include "../Scene/Scene.h"

CEffect_BloodAnimation2::CEffect_BloodAnimation2()
{
}

CEffect_BloodAnimation2::CEffect_BloodAnimation2(const CEffect_BloodAnimation2& Obj) :
	CEffect(Obj)
{
}

CEffect_BloodAnimation2::~CEffect_BloodAnimation2()
{
}

bool CEffect_BloodAnimation2::Init()
{
	CEffect::Init();

	AddAnimation("effect_bloodanimation2_left", true, 0.6f);
	AddAnimation("effect_bloodanimation2_right", true, 0.6f);

	SetRenderScale(1);
	SetPivot({ 0.5f, 1.f });

	return true;
}

void CEffect_BloodAnimation2::Update(float DeltaTime)
{
	CEffect::Update(DeltaTime);

	
	if (m_CurDir == ObjDir::Right && nullptr != GetOwner())
		SetPos(GetOwner()->GetPos() + Vector2{ 50.f, -45.f });
	else if (m_CurDir == ObjDir::Left && nullptr != GetOwner())
		SetPos(GetOwner()->GetPos() + Vector2{ -50.f, -45.f });

}

void CEffect_BloodAnimation2::PostUpdate(float DeltaTime)
{
	CEffect::PostUpdate(DeltaTime);
}

void CEffect_BloodAnimation2::Render(HDC hDC, float DeltaTime)
{
	CEffect::Render(hDC, DeltaTime);
}
