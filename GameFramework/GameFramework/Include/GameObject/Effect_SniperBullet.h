#pragma once

#include "Effect.h"

class CEffect_SniperBullet :
    public CEffect
{
	friend class CScene;

	CEffect_SniperBullet();
	CEffect_SniperBullet(const CEffect_SniperBullet& Obj);
	virtual ~CEffect_SniperBullet();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);


};

