
#include "Scene.h"
#include "../GameObject/GameObject.h"

CScene::CScene()
{
}

CScene::~CScene()
{
}

void CScene::SetPlayer(CGameObject* Player)
{
	m_Player = Player;
}

bool CScene::Init()
{
	return true;
}

void CScene::Update(float DeltaTime)
{
	std::list<CSharedPtr<class CGameObject>>::iterator iter = m_ObjList.begin();
	std::list<CSharedPtr<class CGameObject>>::iterator iterEnd = m_ObjList.end();

	//auto iter = m_ObjList.begin(); // 사파 연습할떈 쓰지말자.

	for (; iter != iterEnd;)
	{
		if (!(*iter)->GetActive())
		{
			// 리스트에서 제거하는 순간 SharedPtr의 소멸자가 호출되어
			// 카운트가 감소한다.
			// 즉, delete (*iter) 할 필요가 없다!!
			iter = m_ObjList.erase(iter);
		}

		else if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}

		(*iter)->Update(DeltaTime);
		++iter;
	}
}

void CScene::Render(HDC hDC, float DeltaTime)
{
	std::list<CSharedPtr<class CGameObject>>::iterator iter = m_ObjList.begin();
	std::list<CSharedPtr<class CGameObject>>::iterator iterEnd = m_ObjList.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->GetActive())
		{
			// 리스트에서 제거하는 순간 SharedPtr의 소멸자가 호출되어
			// 카운트가 감소한다.
			// 즉, delete (*iter) 할 필요가 없다!!
			iter = m_ObjList.erase(iter);
		}

		else if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}

		(*iter)->Render(hDC, DeltaTime);
		++iter;
	}
}
