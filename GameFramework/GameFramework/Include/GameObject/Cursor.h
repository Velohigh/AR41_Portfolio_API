#pragma once

#include "GameObject.h"

class CCursor :
    public CGameObject
{
	friend class CScene;

	CCursor();
	CCursor(const CCursor& Obj);
	virtual ~CCursor();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);

};

