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
	class CBackObj* Back;

private:
	void CreateAnimationSequence();

};

