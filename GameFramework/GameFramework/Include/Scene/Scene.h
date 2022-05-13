#pragma once

#include "../GameInfo.h"

class CScene
{
	friend class CSceneManager;

protected:
	CScene();
	virtual ~CScene();

private:
	class CSceneResource* m_Resource;

protected:
	std::list<CSharedPtr<class CGameObject>>	m_ObjList;
	CSharedPtr<class CGameObject>	m_Player;

public:
	class CSceneResource* GetSceneResource()	const
	{
		return m_Resource;
	}

	class CGameObject* GetPlayer()	const
	{
		return m_Player;
	}

	void SetPlayer(class CGameObject* Player);

public:
	bool Init();
	void Update(float DeltaTime);
	void Render(HDC hDC, float DeltaTime);

public:
	template <typename T>
	T* CreateObject(const std::string& Name = "GameObject")
	{
		T* Obj = new T;

		Obj->SetName(Name);
		Obj->m_Scene = this;

		if (!Obj->Init())
		{
			SAFE_DELETE(Obj);
			return nullptr;
		}

		m_ObjList.push_back((CGameObject*)Obj);

		return Obj;
	}
};

