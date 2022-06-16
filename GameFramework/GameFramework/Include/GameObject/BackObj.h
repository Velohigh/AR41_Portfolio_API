#pragma once

#include "GameObject.h"

class CBackObj :
    public CGameObject
{
	friend class CScene;
	friend class CTitleScene;
	friend class CSceneManager;

private:
	int m_iSelect = 0;
	int m_iPreSelect = 0;

protected:
	CBackObj();
	CBackObj(const CBackObj& Obj);
	virtual ~CBackObj();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);

private:
	void MoveUpPush();
	void MoveDownPush();
	void EnterPush();
	void SceneChange();


};

