#pragma once

#include "Scene.h"

class CTitleScene :
    public CScene
{
	friend class CSceneManager;

protected:
	CTitleScene();
	virtual ~CTitleScene();

public:
	bool Init();
	virtual void Update(float DeltaTime);
	
private:
	int iSelect = 0;
	int iPreSelect = 0;
	bool isStart = false;
	class CBackObj* Back;

private:
	void MoveUpPush();
	void MoveDownPush();

	void CreateAnimationSequence();

};

