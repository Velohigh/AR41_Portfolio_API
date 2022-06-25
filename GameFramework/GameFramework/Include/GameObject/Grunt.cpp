
#include "Grunt.h"
#include "../Collision/ColliderBox.h"


CGrunt::CGrunt()
{
	SetTypeID<CGrunt>();
}

CGrunt::CGrunt(const CGrunt& Obj) :
	CCharacter(Obj)
{
}

CGrunt::~CGrunt()
{
}

bool CGrunt::Init()
{
	CGameObject::Init();

	SetSize(36.f, 70.f);

	// 충돌체 추가
	CColliderBox* Box = AddCollider<CColliderBox>("Body");
	Box->SetExtent(36.f, 70.f);
	Box->SetOffset(0.f, -35.f);
	Box->SetCollisionProfile("Monster");

	Box->SetCollisionBeginFunction<CGrunt>(this, &CGrunt::CollisionBegin);
	Box->SetCollisionEndFunction<CGrunt>(this, &CGrunt::CollisionEnd);


	return true;
}

void CGrunt::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CGrunt::PostUpdate(float DeltaTime)
{
	CCharacter::PostUpdate(DeltaTime);

}

void CGrunt::Render(HDC hDC, float DeltaTime)
{
	CCharacter::Render(hDC, DeltaTime);

}

float CGrunt::InflictDamage(float Damage)
{
	return 0.0f;
}

void CGrunt::CollisionBegin(CCollider* Src, CCollider* Dest)
{
}

void CGrunt::CollisionEnd(CCollider* Src, CCollider* Dest)
{
}
