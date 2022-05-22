#pragma once

#include "Character.h"

class CMonster :
    public CCharacter
{
	friend class CScene;

protected:
	CMonster();
	CMonster(const CMonster& Obj);
	virtual ~CMonster();

private:
	Vector2	m_Dir;
	float	m_FireTime;
	int		m_FireCount;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);

private:
	void CollisionBegin(CCollider* Src, CCollider* Dest);
	void CollisionEnd(CCollider* Src, CCollider* Dest);
};

