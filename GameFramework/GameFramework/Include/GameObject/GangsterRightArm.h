#pragma once

#include "Effect.h"

class CGangsterRightArm :
    public CEffect
{
	friend class CScene;

	CGangsterRightArm();
	CGangsterRightArm(const CGangsterRightArm& Obj);
	virtual ~CGangsterRightArm();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);

};

