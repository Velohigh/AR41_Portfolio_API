#pragma once

#include "Character.h"

class CGrunt :
    public CCharacter
{
    friend class CScene;

protected:
    CGrunt();
    CGrunt(const CGrunt& Obj);
    virtual ~CGrunt();

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render(HDC hDC, float DeltaTime);
    virtual float InflictDamage(float Damage);

private:
    void ViewCollisionBegin(CCollider* Src, CCollider* Dest);
    void ViewCollisionEnd(CCollider* Src, CCollider* Dest);

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
	virtual void DeadStart() override;


	virtual void IdleUpdate() override;
	virtual void WalkUpdate() override;
	virtual void TurnUpdate() override;
	virtual void RunUpdate() override;
	virtual void AttackUpdate() override;
	virtual void HurtGroundUpdate() override;
	virtual void HurtFlyUpdate() override;
	virtual void DeadUpdate() override;

private:
	// Notify
	void CreateAttackCollision();


};

