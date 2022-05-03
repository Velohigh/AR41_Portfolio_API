#pragma once
#include "Character.h"
class CPlayer :
    public CCharacter
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Render(float DeltaTime);
};

