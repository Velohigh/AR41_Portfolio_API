
#include "GangsterLeftArm.h"
#include "../Scene/Scene.h"

CGangsterLeftArm::CGangsterLeftArm()
{
}

CGangsterLeftArm::CGangsterLeftArm(const CGangsterLeftArm& Obj) :
	CEffect(Obj)
{
}

CGangsterLeftArm::~CGangsterLeftArm()
{
}

bool CGangsterLeftArm::Init()
{
	//CEffect::Init();

	SetRenderScale(1);

	SetColorKey(0, 0, 0);
	return true;
}

void CGangsterLeftArm::Update(float DeltaTime)
{
	CEffect::Update(DeltaTime);

	if (GetOwner() != nullptr)
	{
		if (GetOwner()->GetDir() == ObjDir::Right)
		{
			SetTexture("GangsterLeftArm_right", TEXT("Gangster_leftarm_right.bmp"));
			SetColorKey(255, 0, 255);
			SetPos(GetOwner()->GetPos() + Vector2{ +23, -40 });
		}
		else if (GetOwner()->GetDir() == ObjDir::Left)
		{
			SetTexture("GangsterLeftArm_left", TEXT("Gangster_leftarm_left.bmp"));
			SetColorKey(255, 0, 255);
			SetPos(GetOwner()->GetPos() + Vector2{ -23, -40 });

		}
	}

}

void CGangsterLeftArm::PostUpdate(float DeltaTime)
{
	CEffect::PostUpdate(DeltaTime);
}

void CGangsterLeftArm::Render(HDC hDC, float DeltaTime)
{
	CEffect::Render(hDC, DeltaTime);
}
