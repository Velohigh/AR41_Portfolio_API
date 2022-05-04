#pragma once

#include "../GameInfo.h"
#include "../SingletonMacro.h"

class CSceneManager
{
private:
	class CScene* m_Scene;

public:
	bool Init();

public:
	template <typename T>
	bool CreateScene()
	{
		T* Scene = new T;

		if (!Scene->Init())
		{
			SAFE_DELETE(Scene);
			return false;
		}

	if (!m_Scene)
		m_Scene = (CScene*)Scene;

	return true;
	}

	DECLARE_SINGLE(CSceneManager)
};

