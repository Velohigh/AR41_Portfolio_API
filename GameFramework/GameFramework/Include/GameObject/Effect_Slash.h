#pragma once

#include "Effect.h"

class CEffect_Slash :
    public CEffect
{
	friend class CScene;

	CEffect_Slash();
	CEffect_Slash(const CEffect_Slash& Obj);
	virtual ~CEffect_Slash();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);

};

