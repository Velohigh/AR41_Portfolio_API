#pragma once

#include "Effect.h"

class CEffect_DustCloud :
    public CEffect
{
	friend class CScene;

    CEffect_DustCloud();
	CEffect_DustCloud(const CEffect_DustCloud& Obj);
    virtual ~CEffect_DustCloud();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);

};

