
#include "SceneCollision.h"
#include "../Collision/Collider.h"
#include "../Input.h"

CSceneCollision::CSceneCollision() :
	m_MouseCollision(nullptr)
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

void CSceneCollision::CollisionMouse(float DeltaTime)
{
	size_t Size = m_vecCollider.size();

	// ���콺�� ���߿� �׷����� �浹ü�� �浹�ؾ� �ϱ� ������
	// ������ ���������ʹ� �ݴ�� Y�� �������ش�.
	if (Size >= 1)
	{
		if (Size > 1) // ������ 2���̻��϶���
			std::sort(m_vecCollider.begin(), m_vecCollider.end(), CSceneCollision::SortY);

		Vector2 MouseWorldPos = CInput::GetInst()->GetMouseWorldPos();
		CollisionProfile* MouseProfile = CInput::GetInst()->GetMouseProfile();

		bool MouseCollision = false;

		for (size_t i = 0; i < Size; ++i)
		{
			CCollider* Dest = m_vecCollider[i];

			// �浹 Profile�� �����ͼ� �浹 ���Ѿ� �ϴ� ��ü���� �Ǵ��Ѵ�.
			const CollisionProfile* SrcProfile = MouseProfile;
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
			if (Dest->CollisionMouse(MouseWorldPos))
			{
					MouseCollision = true;

				// ���� �� ���콺�� �浹�� �����Ҷ�. 
				if (!Dest->GetMouseCollision())
				{
					// ������ �浹�Ǵ� ��ü�� ���� ��� ���콺���� �浹�� �����Ѵ�.
					if (m_MouseCollision)
						m_MouseCollision->SetMouseCollision(false);

					Dest->SetMouseCollision(true);

					// ���콺�浹 ���� �Լ��� ȣ���Ѵ�.
					Dest->CallMouseCollisionBegin(MouseWorldPos);
				}

				m_MouseCollision = Dest;
			}

			// �浹�� �Ǵ� ��ü�� ���� ��������.
			else if (Dest->GetMouseCollision())
			{
				// ���� �ϼ�����
			}
		}
	}
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

bool CSceneCollision::SortY(CCollider* Src, CCollider* Dest)
{
	return Src->GetBottom() > Dest->GetBottom();
}
