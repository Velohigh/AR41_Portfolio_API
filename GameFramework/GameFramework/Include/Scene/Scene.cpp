
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

	//auto iter = m_ObjList.begin(); // ���� �����ҋ� ��������.

	for (; iter != iterEnd;)
	{
		if (!(*iter)->GetActive())
		{
			// ����Ʈ���� �����ϴ� ���� SharedPtr�� �Ҹ��ڰ� ȣ��Ǿ�
			// ī��Ʈ�� �����Ѵ�.
			// ��, delete (*iter) �� �ʿ䰡 ����!!
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
			// ����Ʈ���� �����ϴ� ���� SharedPtr�� �Ҹ��ڰ� ȣ��Ǿ�
			// ī��Ʈ�� �����Ѵ�.
			// ��, delete (*iter) �� �ʿ䰡 ����!!
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
