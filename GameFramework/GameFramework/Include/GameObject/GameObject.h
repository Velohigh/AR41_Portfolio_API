#pragma once

#include "../GameInfo.h"

class CGameObject
{
public:
	CGameObject();
	virtual ~CGameObject();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Render(float DeltaTime);


};

