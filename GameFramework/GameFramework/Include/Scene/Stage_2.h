#pragma once

#include "Scene.h"

class CStage_2 :
    public CScene
{
	friend class CSceneManager;

protected:
	CStage_2();
	virtual ~CStage_2();

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

