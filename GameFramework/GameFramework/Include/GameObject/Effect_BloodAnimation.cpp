
#include "Effect_BloodAnimation.h"
#include "../Scene/Scene.h"
#include "Player.h"

CEffect_BloodAnimation::CEffect_BloodAnimation()
{
}

CEffect_BloodAnimation::CEffect_BloodAnimation(const CEffect_BloodAnimation& Obj) :
	CEffect(Obj)
{
}

CEffect_BloodAnimation::~CEffect_BloodAnimation()
{
}

bool CEffect_BloodAnimation::Init()
{
	CEffect::Init();

	AddAnimation("effect_bloodanimation_left", true, 0.36f);
	AddAnimation("effect_bloodanimation_right", true, 0.36f);

	SetEffectType(EEffect_Type::Loop);

	SetRenderScale(2);
	SetPivot({ 0.5f, 1.f });

	return true;
}

void CEffect_BloodAnimation::Update(float DeltaTime)
{
	CEffect::Update(DeltaTime);
	
	if(m_CurDir == ObjDir::Right)
		SetPos(m_Scene->GetPlayer()->GetPos() + Vector2{ 40.f, -50.f });
	else if (m_CurDir == ObjDir::Left)
		SetPos(m_Scene->GetPlayer()->GetPos() + Vector2{ -40.f, -50.f });

	if (ObjState::HurtFly != GetOwner()->GetState())
	{
		SetActive(false);
	}

}

void CEffect_BloodAnimation::PostUpdate(float DeltaTime)
{
	CEffect::PostUpdate(DeltaTime);
}

void CEffect_BloodAnimation::Render(HDC hDC, float DeltaTime)
{
	CEffect::Render(hDC, DeltaTime);
}
