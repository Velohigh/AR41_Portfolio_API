#pragma once
#include "Scene.h"
class CEditScene :
    public CScene
{
	friend class CSceneManager;

protected:
	CEditScene();
	virtual ~CEditScene();

public:
	bool Init();

public:
	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();
};

