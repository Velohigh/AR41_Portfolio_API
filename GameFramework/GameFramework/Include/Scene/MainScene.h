#pragma once
#include "Scene.h"
class CMainScene : public CScene
{
	friend class CSceneManager;

protected:
	CMainScene();
	virtual ~CMainScene();

public:
	bool Init();
	void Update(float DeltaTime);
	void Render(HDC hDC, float DeltaTime);

};

