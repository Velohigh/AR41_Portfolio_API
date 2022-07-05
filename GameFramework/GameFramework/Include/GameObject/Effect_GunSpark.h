#pragma once

#include "Effect.h"

class CEffect_GunSpark :
    public CEffect
{
	friend class CScene;

	CEffect_GunSpark();
	CEffect_GunSpark(const CEffect_GunSpark& Obj);
	virtual ~CEffect_GunSpark();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);

};

