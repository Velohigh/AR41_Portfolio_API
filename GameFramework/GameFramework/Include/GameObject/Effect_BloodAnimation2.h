#pragma once

#include "Effect.h"

class CEffect_BloodAnimation2 :
    public CEffect
{
	friend class CScene;

	CEffect_BloodAnimation2();
	CEffect_BloodAnimation2(const CEffect_BloodAnimation2& Obj);
	virtual ~CEffect_BloodAnimation2();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);

};

