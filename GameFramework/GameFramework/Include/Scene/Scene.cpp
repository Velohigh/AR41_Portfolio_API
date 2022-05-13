
#include "Scene.h"
#include "../GameObject/GameObject.h"
#include "SceneResource.h"

CScene::CScene()
{
	m_Resource = new CSceneResource;
}

CScene::~CScene()
{
	m_ObjList.clear();

	SAFE_DELETE(m_Resource);
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
	// �̷��� �� �����ϼ��� ����....
	// std::list<CSharedPtr<class CGameObject>>::iterator

	// auto : ����� ���ÿ� ������ ������ ���־�� �Ѵ�.
	// ���Ե� Ÿ������ Ÿ���� ����ȴ�.
	auto	iter = m_ObjList.begin();
	auto	iterEnd = m_ObjList.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->GetActive())
		{
			// ����Ʈ���� �����ϴ� ���� SharedPtr�� �Ҹ��ڰ� ȣ��Ǿ�
			// ī��Ʈ�� �����Ѵ�.
			iter = m_ObjList.erase(iter);
			iterEnd = m_ObjList.end();
			continue;
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
	auto	iter = m_ObjList.begin();
	auto	iterEnd = m_ObjList.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->GetActive())
		{
			// ����Ʈ���� �����ϴ� ���� SharedPtr�� �Ҹ��ڰ� ȣ��Ǿ�
			// ī��Ʈ�� �����Ѵ�.
			iter = m_ObjList.erase(iter);
			iterEnd = m_ObjList.end();
			continue;
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
