#pragma once

#include "Effect.h"

class CEffect_Enemy_Follow :
    public CEffect
{
	friend class CScene;

	CEffect_Enemy_Follow();
	CEffect_Enemy_Follow(const CEffect_Enemy_Follow& Obj);
	virtual ~CEffect_Enemy_Follow();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);

};

