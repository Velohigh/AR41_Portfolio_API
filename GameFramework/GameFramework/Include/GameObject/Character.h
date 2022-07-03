#pragma once

#include "GameObject.h"


class CCharacter :
    public CGameObject
{
	friend class CScene;

protected:
	class CColliderBox* m_ViewCollider = nullptr;
	class CColliderCircle* m_AttackRangeCollider = nullptr;
	class CColliderBox* m_AttackCollider = nullptr;
	class CEffect_Enemy_Follow* m_Effect_EnemyFollow = nullptr;

protected:
	CCharacter();
	CCharacter(const CCharacter& Obj);
	virtual ~CCharacter();


public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
	virtual float InflictDamage(float Damage);

public:
	void CheckViewAngle();

};

