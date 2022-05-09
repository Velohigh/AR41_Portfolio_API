#pragma once

#include "../GameInfo.h"

class CScene
{
	friend class CSceneManager;

protected: 
	CScene();
	virtual ~CScene();

protected:
	std::list<CSharedPtr<class CGameObject>>	m_ObjList;

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

		if (!Obj->Init())
		{
			SAFE_DELETE(Obj);
			return nullptr;
		}

		m_ObjList.push_back((CGameObject*)Obj);

		return Obj;
	}


};

