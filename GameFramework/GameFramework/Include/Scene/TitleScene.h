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
	int m_iSelect = 0;
	int m_iPreSelect = 0;
	class CBackObj* Back;

private:
	void MoveUpPush();
	void MoveDownPush();
	void EnterPush();
	void SceneChange();
	void CreateAnimationSequence();

};

