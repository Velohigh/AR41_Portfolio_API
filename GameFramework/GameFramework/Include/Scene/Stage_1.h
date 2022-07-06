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
	class CBackObj* Back;
	CSharedPtr<class CMonster>	m_Monster;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

public:
	void SetSlowMap();
	void SetNormalMap();

private:
	void CreateAnimationSequencePlayer();
	void CreateAnimationSequenceGrunt();
	void CreateAnimationSequenceGangster();
	void CreateAnimationSequenceEffect_Frame();
	void CreateAnimationSequenceEffect_Sprite();

private:
};

