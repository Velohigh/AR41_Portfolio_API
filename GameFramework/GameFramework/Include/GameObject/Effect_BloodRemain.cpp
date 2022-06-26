
#include "Effect_BloodRemain.h"

extern Vector2 g_AttackDir;

CEffect_BloodRemain::CEffect_BloodRemain()
{
}

CEffect_BloodRemain::CEffect_BloodRemain(const CEffect_BloodRemain& Obj) :
	CEffect(Obj)
{
}

CEffect_BloodRemain::~CEffect_BloodRemain()
{
}

bool CEffect_BloodRemain::Init()
{
	//CEffect::Init();

	if (g_AttackDir.x >= 0)
	{
		SetPos({ 70.f, -10.f });
		SetTexture("effect_blood_remain1_right", TEXT("effect_blood_remain1_right.bmp"));
	}
	else if (g_AttackDir.x < 0)
	{
		SetPos({ -70.f, -10.f });
		SetTexture("effect_blood_remain1_left", TEXT("effect_blood_remain1_left.bmp"));
	}

	SetColorKey(255, 0, 255);

	SetPivot(0.5f, 1.f);

	SetRenderScale(2);
	
	return true;
}

void CEffect_BloodRemain::Update(float DeltaTime)
{
	CEffect::Update(DeltaTime);

}

void CEffect_BloodRemain::PostUpdate(float DeltaTime)
{
	CEffect::PostUpdate(DeltaTime);
}

void CEffect_BloodRemain::Render(HDC hDC, float DeltaTime)
{
	CEffect::Render(hDC, DeltaTime);
}
