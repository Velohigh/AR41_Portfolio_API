#pragma once

#include "Character.h"

class CGangster :
    public CCharacter
{
	friend class CScene;

protected:
	CGangster();
	CGangster(const CGangster& Obj);
	virtual ~CGangster();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
	virtual float InflictDamage(float Damage);

private:
	void CollisionBegin(CCollider* Src, CCollider* Dest);
	void CollisionEnd(CCollider* Src, CCollider* Dest);

private:
	///////////////////////////////
	////	FSM
	virtual void IdleStart() override;
	virtual void WalkStart() override;
	virtual void TurnStart() override;
	virtual void RunStart() override;
	virtual void AttackStart() override;
	virtual void HurtGroundStart() override;
	virtual void HurtFlyStart() override;


	virtual void IdleUpdate() override;
	virtual void WalkUpdate() override;
	virtual void TurnUpdate() override;
	virtual void RunUpdate() override;
	virtual void AttackUpdate() override;
	virtual void HurtGroundUpdate() override;
	virtual void HurtFlyUpdate() override;


};

