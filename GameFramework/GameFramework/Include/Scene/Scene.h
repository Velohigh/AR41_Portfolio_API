#pragma once

#include "../GameInfo.h"

class CScene
{
	friend class CSceneManager;

protected: 
	CScene();
	virtual ~CScene();

protected:
	std::list<class CGameObject*>	m_ObjList;

public:
	bool Init();
	void Update(float DeltaTime);
	void Render(HDC hDC, float DeltaTime);
};

