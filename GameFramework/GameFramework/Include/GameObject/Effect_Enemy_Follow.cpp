
#include "Effect_Enemy_Follow.h"

CEffect_Enemy_Follow::CEffect_Enemy_Follow()
{
}

CEffect_Enemy_Follow::CEffect_Enemy_Follow(const CEffect_Enemy_Follow& Obj) :
	CEffect(Obj)
{
}

CEffect_Enemy_Follow::~CEffect_Enemy_Follow()
{
}

bool CEffect_Enemy_Follow::Init()
{
	// 애니메이션을 만들필요없어서 실행X
	//CEffect::Init();

	SetTexture("enemy_follow", TEXT("enemy_follow.bmp"));

	SetColorKey(255, 0, 255);

	SetPivot(0.5f, 1.f);

	SetRenderScale(2);

	return true;
}

void CEffect_Enemy_Follow::Update(float DeltaTime)
{
	CEffect::Update(DeltaTime);

	if (GetOwner() != nullptr)
		SetPos(GetOwner()->GetPos() + Vector2(0.f, -80));

	if (GetOwner()->GetState() == ObjState::Dead)
		SetActive(false);

}

void CEffect_Enemy_Follow::PostUpdate(float DeltaTime)
{
	CEffect::PostUpdate(DeltaTime);
}

void CEffect_Enemy_Follow::Render(HDC hDC, float DeltaTime)
{
	CEffect::Render(hDC, DeltaTime);
}
