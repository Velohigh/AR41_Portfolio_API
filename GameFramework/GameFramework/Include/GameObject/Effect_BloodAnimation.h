#pragma once

#include "Effect.h"

class CEffect_BloodAnimation :
    public CEffect
{
	friend class CScene;

	CEffect_BloodAnimation();
	CEffect_BloodAnimation(const CEffect_BloodAnimation& Obj);
	virtual ~CEffect_BloodAnimation();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);

};

