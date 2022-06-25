
#include "Effect_JumpCloud.h"

CEffect_JumpCloud::CEffect_JumpCloud()
{
}

CEffect_JumpCloud::CEffect_JumpCloud(const CEffect_JumpCloud& Obj) :
	CEffect(Obj)
{
}

CEffect_JumpCloud::~CEffect_JumpCloud()
{
}

bool CEffect_JumpCloud::Init()
{
	CEffect::Init();

	SetRenderScale(2);
	return true;
}

void CEffect_JumpCloud::Update(float DeltaTime)
{
	CEffect::Update(DeltaTime);

}

void CEffect_JumpCloud::PostUpdate(float DeltaTime)
{
	CEffect::PostUpdate(DeltaTime);
}

void CEffect_JumpCloud::Render(HDC hDC, float DeltaTime)
{
	CEffect::Render(hDC, DeltaTime);
}

