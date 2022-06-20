#pragma once

#include "GameObject.h"

enum class ActorState
{
	Idle,
	Run,
	Attack,

	End
};

class CCharacter :
    public CGameObject
{
	friend class CScene;

protected:
	ActorState	m_CurState;
	ActorState	m_PreState;

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
};

