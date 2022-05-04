#pragma once
#include "Character.h"
class CPlayer :
    public CCharacter
{
public:
	CPlayer();
	virtual ~CPlayer();

private:
	float	m_GunAngle;
	float	m_GunLength;
	Vector2	m_GunPos;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
};

