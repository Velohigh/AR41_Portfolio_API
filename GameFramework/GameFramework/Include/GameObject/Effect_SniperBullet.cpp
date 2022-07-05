
#include "Effect_SniperBullet.h"
#include "../Scene/Scene.h"

CEffect_SniperBullet::CEffect_SniperBullet()
{
}

CEffect_SniperBullet::CEffect_SniperBullet(const CEffect_SniperBullet& Obj) :
	CEffect(Obj)
{
}

CEffect_SniperBullet::~CEffect_SniperBullet()
{
}

bool CEffect_SniperBullet::Init()
{
	CEffect::Init();

	SetRenderScale(2);
	return true;
}

void CEffect_SniperBullet::Update(float DeltaTime)
{
	CEffect::Update(DeltaTime);

}

void CEffect_SniperBullet::PostUpdate(float DeltaTime)
{
	CEffect::PostUpdate(DeltaTime);
}

void CEffect_SniperBullet::Render(HDC hDC, float DeltaTime)
{
	CEffect::Render(hDC, DeltaTime);
}
