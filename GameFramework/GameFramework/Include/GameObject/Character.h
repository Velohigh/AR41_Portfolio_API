#pragma once
#include "GameObject.h"
class CCharacter :
    public CGameObject
{
public:
	CCharacter();
	virtual ~CCharacter();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Render(float DeltaTime);
};

