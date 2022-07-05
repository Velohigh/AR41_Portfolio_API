
#include "Effect_GunSpark.h"

#include "../Scene/Scene.h"

CEffect_GunSpark::CEffect_GunSpark()
{
}

CEffect_GunSpark::CEffect_GunSpark(const CEffect_GunSpark& Obj) :
	CEffect(Obj)
{
}

CEffect_GunSpark::~CEffect_GunSpark()
{
}

bool CEffect_GunSpark::Init()
{
	CEffect::Init();

	SetRenderScale(2);
	SetPivot({ 0.5f, 0.5f });

	return true;
}

void CEffect_GunSpark::Update(float DeltaTime)
{
	CEffect::Update(DeltaTime);

}

void CEffect_GunSpark::PostUpdate(float DeltaTime)
{
	CEffect::PostUpdate(DeltaTime);
}

void CEffect_GunSpark::Render(HDC hDC, float DeltaTime)
{
	CEffect::Render(hDC, DeltaTime);
}
