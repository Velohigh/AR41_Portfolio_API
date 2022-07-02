#pragma once

#include "Effect.h"

class CEffect_Hit_Lazer :
    public CEffect
{
	friend class CScene;

	CEffect_Hit_Lazer();
	CEffect_Hit_Lazer(const CEffect_Hit_Lazer& Obj);
	virtual ~CEffect_Hit_Lazer();

private:
	float	m_Time;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);

};

