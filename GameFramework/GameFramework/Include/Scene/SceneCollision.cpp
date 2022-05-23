
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

				// �浹ü���� ���� ������Ʈ�� �����ִٸ� �浹 X
				if (Src->GetOwner() == Dest->GetOwner())
					continue;

				// �浹 Profile�� �����ͼ� �浹 ���Ѿ� �ϴ� ��ü���� �Ǵ��Ѵ�.
				const CollisionProfile* SrcProfile = Src->GetProfile();
				const CollisionProfile* DestProfile = Dest->GetProfile();

				// Profile���� �ٸ� ä�ΰ� ��ȣ�ۿ��� ��� �ؾ� �Ǵ����� ������ �ִ�.
				// �׷��Ƿ� ���� ä�ι�°�� ��ȣ�ۿ��� ���ͼ� �������� �浹������ �˾Ƴ��� �Ѵ�.
				ECollision_Interaction SrcInteraction = SrcProfile->vecCollisionInteraction[(int)DestProfile->Channel];
				ECollision_Interaction DestInteraction = DestProfile->vecCollisionInteraction[(int)SrcProfile->Channel];

				// ���� �ϳ��� �����ϱ�� �Ǿ� �ִٸ� �浹�� �����.
				if (SrcInteraction == ECollision_Interaction::Ignore ||
					DestInteraction == ECollision_Interaction::Ignore)
					continue;

				// �浹�� üũ�Ѵ�.
				if (Src->Collision(Dest))
				{
					// �浹����Ʈ�� ���ٸ�, ���� �� �浹�� �����Ҷ�. 
					if (!Src->CheckCollisionList(Dest))
					{
						// ���ο��� ���� �浹ü�� �浹��Ͽ� ����Ѵ�.
						Src->AddCollisionList(Dest);
						Dest->AddCollisionList(Src);

						// �浹 ���� �Լ��� ȣ���Ѵ�.
						Src->CallCollisionBegin(Dest);
						Dest->CallCollisionBegin(Src);
					}
				}

				// �浹����Ʈ�� �ִٸ�, �浹�� �Ǵ� ��ü�� ���� ��������.
				else if (Src->CheckCollisionList(Dest))
				{
					// ���� ��Ͽ��� �浹ü�� �����ش�.
					Src->DeleteCollisionList(Dest);
					Dest->DeleteCollisionList(Src);

					// �浹 ���� �Լ��� ȣ���Ѵ�.
					Src->CallCollisionEnd(Dest);
					Dest->CallCollisionEnd(Src);
				}
			}
		}
	}

	m_vecCollider.clear();
}
