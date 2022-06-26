#pragma once

#include "Effect.h"

class CEffect_LandCloud :
    public CEffect
{
	friend class CScene;

	CEffect_LandCloud();
	CEffect_LandCloud(const CEffect_LandCloud& Obj);
	virtual ~CEffect_LandCloud();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);

};

