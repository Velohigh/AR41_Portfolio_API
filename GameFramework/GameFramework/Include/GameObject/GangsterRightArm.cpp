
#include "GangsterRightArm.h"
#include "../Scene/Scene.h"

CGangsterRightArm::CGangsterRightArm()
{
}

CGangsterRightArm::CGangsterRightArm(const CGangsterRightArm& Obj) :
	CEffect(Obj)
{
}

CGangsterRightArm::~CGangsterRightArm()
{
}

bool CGangsterRightArm::Init()
{
	//CEffect::Init();

	SetRenderScale(1);

	SetColorKey(255, 0, 255);
	return true;
}

void CGangsterRightArm::Update(float DeltaTime)
{
	CEffect::Update(DeltaTime);

	if (GetOwner() != nullptr)
	{
		if (GetOwner()->GetDir() == ObjDir::Right)
		{
			SetTexture("GangsterRightArm_right", TEXT("Gangster_rightarm_right.bmp"));
			SetColorKey(255, 0, 255);
			SetPos(GetOwner()->GetPos() + Vector2{ +23, -21 });
		}
		else if (GetOwner()->GetDir() == ObjDir::Left)
		{
			SetTexture("GangsterRight_left", TEXT("Gangster_rightarm_left.bmp"));
			SetColorKey(255, 0, 255);
			SetPos(GetOwner()->GetPos() + Vector2{ -23, -21 });

		}
	}

}

void CGangsterRightArm::PostUpdate(float DeltaTime)
{
	CEffect::PostUpdate(DeltaTime);
}

void CGangsterRightArm::Render(HDC hDC, float DeltaTime)
{
	CEffect::Render(hDC, DeltaTime);
}
