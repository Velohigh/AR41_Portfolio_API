
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
	// 이렇게 꼭 연습하세요 제발....
	// std::list<CSharedPtr<class CGameObject>>::iterator

	// auto : 선언과 동시에 무조건 대입을 해주어야 한다.
	// 대입된 타입으로 타입이 선언된다.
	for (int i = 0; i < (int)ERender_Layer::Max; ++i)
	{
		auto	iter = m_ObjList[i].begin();
		auto	iterEnd = m_ObjList[i].end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->GetActive())
			{
				// 리스트에서 제거하는 순간 SharedPtr의 소멸자가 호출되어
				// 카운트가 감소한다.
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
				// 리스트에서 제거하는 순간 SharedPtr의 소멸자가 호출되어
				// 카운트가 감소한다.
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

	m_Camera->Update(DeltaTime);

	m_Collision->Collision(DeltaTime);
}

void CScene::Render(HDC hDC, float DeltaTime)
{
	// 출력 목록을 정렬한다. (Y소팅)
	for (int i = 0; i < (int)ERender_Layer::Max; ++i)
	{
		m_ObjList[i].sort(SortY);

		auto	iter = m_ObjList[i].begin();
		auto	iterEnd = m_ObjList[i].end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->GetActive())
			{
				// 리스트에서 제거하는 순간 SharedPtr의 소멸자가 호출되어
				// 카운트가 감소한다.
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
}

bool CScene::SortY(const CSharedPtr<CGameObject>& Src, const CSharedPtr<CGameObject>& Dest)
{
	// 발밑 기준으로 정렬을 진행해야 하기 때문에 발밑의 Y를 구해준다.
	float	SrcY = Src->GetPos().y + (1.f - Src->GetPivot().y) * Src->GetSize().y;
	float	DestY = Dest->GetPos().y + (1.f - Dest->GetPivot().y) * Dest->GetSize().y;

	return SrcY < DestY;
}
