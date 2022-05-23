
#include "SceneCollision.h"
#include "../Collision/Collider.h"

CSceneCollision::CSceneCollision()
{
	m_vecCollider.reserve(500);
}

CSceneCollision::~CSceneCollision()
{
}

void CSceneCollision::AddCollider(CCollider* Collider)
{
	m_vecCollider.push_back(Collider);
}

void CSceneCollision::Collision(float DeltaTime)
{
	size_t Size = m_vecCollider.size();

	if (Size > 1)
	{
		for (size_t i = 0; i < Size - 1; ++i)
		{
			CCollider* Src = m_vecCollider[i];

			for (size_t j = i + 1; j < Size; ++j)
			{
				CCollider* Dest = m_vecCollider[j];

				// 충돌체끼리 같은 오브젝트에 속해있다면 충돌 X
				if (Src->GetOwner() == Dest->GetOwner())
					continue;

				// 충돌 Profile을 가져와서 충돌 시켜야 하는 물체인지 판단한다.
				const CollisionProfile* SrcProfile = Src->GetProfile();
				const CollisionProfile* DestProfile = Dest->GetProfile();

				// Profile에는 다른 채널과 상호작용을 어떻게 해야 되는지가 정해져 있다.
				// 그러므로 상대방 채널번째의 상호작용을 얻어와서 무시인지 충돌인지를 알아내야 한다.
				ECollision_Interaction SrcInteraction = SrcProfile->vecCollisionInteraction[(int)DestProfile->Channel];
				ECollision_Interaction DestInteraction = DestProfile->vecCollisionInteraction[(int)SrcProfile->Channel];

				// 둘중 하나라도 무시하기로 되어 있다면 충돌을 멈춘다.
				if (SrcInteraction == ECollision_Interaction::Ignore ||
					DestInteraction == ECollision_Interaction::Ignore)
					continue;

				// 충돌을 체크한다.
				if (Src->Collision(Dest))
				{
					// 충돌리스트에 없다면, 이제 막 충돌을 시작할때. 
					if (!Src->CheckCollisionList(Dest))
					{
						// 서로에게 상대방 충돌체를 충돌목록에 등록한다.
						Src->AddCollisionList(Dest);
						Dest->AddCollisionList(Src);

						// 충돌 시작 함수를 호출한다.
						Src->CallCollisionBegin(Dest);
						Dest->CallCollisionBegin(Src);
					}
				}

				// 충돌리스트에 있다면, 충돌이 되던 물체가 서로 떨어질때.
				else if (Src->CheckCollisionList(Dest))
				{
					// 서로 목록에서 충돌체를 지워준다.
					Src->DeleteCollisionList(Dest);
					Dest->DeleteCollisionList(Src);

					// 충돌 종료 함수를 호출한다.
					Src->CallCollisionEnd(Dest);
					Dest->CallCollisionEnd(Src);
				}
			}
		}
	}

	m_vecCollider.clear();
}
