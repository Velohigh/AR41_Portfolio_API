#pragma once

#include "Scene.h"

class CStage_1 :
    public CScene
{
	friend class CSceneManager;

protected:
	CStage_1();
	virtual ~CStage_1();

private:
	CSharedPtr<class CMonster>	m_Monster;

public:
	bool Init();

private:
	void CreateAnimationSequence();

private:
};

