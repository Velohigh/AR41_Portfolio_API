
#include "Effect_LandCloud.h"

CEffect_LandCloud::CEffect_LandCloud()
{
}

CEffect_LandCloud::CEffect_LandCloud(const CEffect_LandCloud& Obj) :
	CEffect(Obj)
{
}

CEffect_LandCloud::~CEffect_LandCloud()
{
}

bool CEffect_LandCloud::Init()
{
	CEffect::Init();

	SetRenderScale(2);
	return true;
}

void CEffect_LandCloud::Update(float DeltaTime)
{
	CEffect::Update(DeltaTime);

}

void CEffect_LandCloud::PostUpdate(float DeltaTime)
{
	CEffect::PostUpdate(DeltaTime);
}

void CEffect_LandCloud::Render(HDC hDC, float DeltaTime)
{
	CEffect::Render(hDC, DeltaTime);
}
