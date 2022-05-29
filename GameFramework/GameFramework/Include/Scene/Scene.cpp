
#include "Scene.h"
#include "../GameObject/GameObject.h"
#include "SceneResource.h"
#include "Camera.h"
#include "SceneCollision.h"

CScene::CScene()
{
	m_Resource = new CSceneResource;
	m_Camera = new CCamera;
	m_Collision = new CSceneCollision;
}

CScene::~CScene()
{
	for (int i = 0; i < (int)ERender_Layer::Max; ++i)
	{
		m_ObjList[i].clear();
	}

	SAFE_DELETE(m_Collision);
	SAFE_DELETE(m_Camera);
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
	for (int i = 0; i < (int)ERender_Layer::Max; ++i)
	{
		auto	iter = m_ObjList[i].begin();
		auto	iterEnd = m_ObjList[i].end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->GetActive())
			{
				// ����Ʈ���� �����ϴ� ���� SharedPtr�� �Ҹ��ڰ� ȣ��Ǿ�
				// ī��Ʈ�� �����Ѵ�.
				iter = m_ObjList[i].erase(iter);
				iterEnd = m_ObjList[i].end();
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

	size_t Size = m_vecWidgetWindow.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecWidgetWindow[i]->Update(DeltaTime);
	}

	m_Camera->Update(DeltaTime);
}

void CScene::PostUpdate(float DeltaTime)
{
	for (int i = 0; i < (int)ERender_Layer::Max; ++i)
	{
		auto	iter = m_ObjList[i].begin();
		auto	iterEnd = m_ObjList[i].end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->GetActive())
			{
				// ����Ʈ���� �����ϴ� ���� SharedPtr�� �Ҹ��ڰ� ȣ��Ǿ�
				// ī��Ʈ�� �����Ѵ�.
				iter = m_ObjList[i].erase(iter);
				iterEnd = m_ObjList[i].end();
				continue;
			}

			else if (!(*iter)->GetEnable())
			{
				++iter;
				continue;
			}

			(*iter)->PostUpdate(DeltaTime);

			++iter;
		}
	}

	size_t Size = m_vecWidgetWindow.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecWidgetWindow[i]->PostUpdate(DeltaTime);
	}

	m_Collision->CollisionMouse(DeltaTime);

	m_Collision->Collision(DeltaTime);
}

void CScene::Render(HDC hDC, float DeltaTime)
{
	// ��� ����� �����Ѵ�. (Y����)
	for (int i = 0; i < (int)ERender_Layer::Max; ++i)
	{
		m_ObjList[i].sort(SortY);

		auto	iter = m_ObjList[i].begin();
		auto	iterEnd = m_ObjList[i].end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->GetActive())
			{
				// ����Ʈ���� �����ϴ� ���� SharedPtr�� �Ҹ��ڰ� ȣ��Ǿ�
				// ī��Ʈ�� �����Ѵ�.
				iter = m_ObjList[i].erase(iter);
				iterEnd = m_ObjList[i].end();
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

	// ��������� ��ü�� ��µ� ���Ŀ� UI�� ����Ѵ�.
	size_t Size = m_vecWidgetWindow.size();

	for (size_t i = 0; i < Size; ++i)
	{
		if (!m_vecWidgetWindow[i]->GetVisibility())
			continue;

		m_vecWidgetWindow[i]->Render(hDC, DeltaTime);
	}
	
	// UI�� ����� ���Ŀ� ���콺�� ����Ѵ�.
}

bool CScene::SortY(const CSharedPtr<CGameObject>& Src, const CSharedPtr<CGameObject>& Dest)
{
	// �߹� �������� ������ �����ؾ� �ϱ� ������ �߹��� Y�� �����ش�.
	float	SrcY = Src->GetPos().y + (1.f - Src->GetPivot().y) * Src->GetSize().y;
	float	DestY = Dest->GetPos().y + (1.f - Dest->GetPivot().y) * Dest->GetSize().y;

	return SrcY < DestY;
}
