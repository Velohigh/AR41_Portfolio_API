#pragma once

#include "Scene.h"

class CStartScene :
    public CScene
{
	friend class CSceneManager;

protected:
	CStartScene();
	virtual ~CStartScene();

public:
	bool Init();
	virtual void Update(float DeltaTime);
	
private:
	int iSelect = 0;
	int iPreSelect = 0;
	bool isStart = false;
	class CBackObj* Back;

};

