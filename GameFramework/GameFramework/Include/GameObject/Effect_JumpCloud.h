#pragma once

#include "Effect.h"

class CEffect_JumpCloud :
    public CEffect
{
	friend class CScene;

	CEffect_JumpCloud();
	CEffect_JumpCloud(const CEffect_JumpCloud& Obj);
	virtual ~CEffect_JumpCloud();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);

};

