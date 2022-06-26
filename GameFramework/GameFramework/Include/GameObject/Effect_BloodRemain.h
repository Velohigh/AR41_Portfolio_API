#pragma once

#include "Effect.h"

class CEffect_BloodRemain :
    public CEffect
{
	friend class CScene;

	CEffect_BloodRemain();
	CEffect_BloodRemain(const CEffect_BloodRemain& Obj);
	virtual ~CEffect_BloodRemain();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);

};

