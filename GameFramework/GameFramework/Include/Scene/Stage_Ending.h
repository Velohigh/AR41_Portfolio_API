#pragma once

#include "Scene.h"

class CStage_Ending :
    public CScene
{
	friend class CSceneManager;

protected:
	CStage_Ending();
	virtual ~CStage_Ending();

public:
	bool Init();
	virtual void Update(float DeltaTime);

private:
	class CBackObj* Back;

private:
	void EnterPush();
	void CreateAnimationSequence();

};

