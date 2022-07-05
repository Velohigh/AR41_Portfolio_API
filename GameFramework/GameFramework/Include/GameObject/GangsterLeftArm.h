#pragma once

#include "Effect.h"

class CGangsterLeftArm :
    public CEffect
{
	friend class CScene;

	CGangsterLeftArm();
	CGangsterLeftArm(const CGangsterLeftArm& Obj);
	virtual ~CGangsterLeftArm();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);

};

