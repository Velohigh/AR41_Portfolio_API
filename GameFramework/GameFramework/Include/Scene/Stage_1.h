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
	void CreateAnimationSequencePlayer_AddFrame();
	void CreateAnimationSequencePlayer2_AddFrame();
	void CreateAnimationSequenceGrunt_AddFrame();
	void CreateAnimationSequenceGangster_AddFrame();
	void CreateAnimationSequencePomp_AddFrame();
	void CreateAnimationSequenceEffect_Frame_AddFrame();
	void CreateAnimationSequenceEffect_Sprite_AddFrame();

private:
	void CreateAnimationSequencePlayer();
	void CreateAnimationSequencePlayer2();
	void CreateAnimationSequenceGrunt();
	void CreateAnimationSequenceGangster();
	void CreateAnimationSequencePomp();
	void CreateAnimationSequenceEffect_Frame();
	void CreateAnimationSequenceEffect_Sprite();


private:
};

