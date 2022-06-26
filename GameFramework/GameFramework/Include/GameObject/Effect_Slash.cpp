
#include "Effect_Slash.h"

CEffect_Slash::CEffect_Slash()
{
}

CEffect_Slash::CEffect_Slash(const CEffect_Slash& Obj) :
	CEffect(Obj)
{
}

CEffect_Slash::~CEffect_Slash()
{
}

bool CEffect_Slash::Init()
{
	CEffect::Init();

	SetRenderScale(2);
	return true;
}

void CEffect_Slash::Update(float DeltaTime)
{
	CEffect::Update(DeltaTime);

}

void CEffect_Slash::PostUpdate(float DeltaTime)
{
	CEffect::PostUpdate(DeltaTime);
}

void CEffect_Slash::Render(HDC hDC, float DeltaTime)
{
	CEffect::Render(hDC, DeltaTime);
}
