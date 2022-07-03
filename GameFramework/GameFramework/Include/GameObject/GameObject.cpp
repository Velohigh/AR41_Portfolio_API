
#include "GameObject.h"
#include "../Resource/Texture/Texture.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Scene/SceneManager.h"
#include "../Scene/SceneCollision.h"
#include "../Resource/Animation/AnimationSequence.h"
#include "../GameManager.h"
#include "../Scene/Camera.h"
#include "../Collision/Collider.h"
#include "../PathManager.h"
#include "TileMap.h"
#include "Tile.h"

CGameObject::CGameObject()	:
	m_Scene(nullptr),
	m_Animation(nullptr),
	m_TimeScale(1.f),
	m_MoveSpeed(0.f),
	m_RenderLayer(ERender_Layer::Default),
	m_PhysicsSimulate(false),
	m_Ground(false),
	m_FallTime(0.f),
	m_FallStartY(0.f),
	m_Jump(false),
	m_JumpVelocity(0.f),
	m_SideWallCheck(false),
	m_Start(false),
	m_MapColTexture(nullptr),
	m_MoveDir(0.f, 0.f)
{
	SetTypeID<CGameObject>();
}

CGameObject::CGameObject(const CGameObject& Obj)	:
	CRef(Obj),
	m_Scene(nullptr),
	m_Pos(Obj.m_Pos),
	m_Size(Obj.m_Size),
	m_Pivot(Obj.m_Pivot),
	m_TimeScale(Obj.m_TimeScale),
	m_PhysicsSimulate(Obj.m_PhysicsSimulate),
	m_Ground(false),
	m_GravityAccel(Obj.m_GravityAccel),
	m_FallTime(0.f),
	m_FallStartY(0.f),
	m_Jump(false),
	m_JumpVelocity(Obj.m_JumpVelocity),
	m_SideWallCheck(Obj.m_SideWallCheck),
	m_Start(false),
	m_MoveDir(Obj.m_MoveDir)
{
}

CGameObject::~CGameObject()
{
	{
		auto	iter = m_ColliderList.begin();
		auto	iterEnd = m_ColliderList.end();

		for (; iter != iterEnd; ++iter)
		{
			(*iter)->ClearCollisionList();
		}
	}

	{
		auto	iter = m_WidgetComponentList.begin();
		auto	iterEnd = m_WidgetComponentList.end();

		for (; iter != iterEnd; ++iter)
		{
			(*iter)->SetActive(false);
		}
	}

	SAFE_DELETE(m_Animation);
}

CCollider* CGameObject::FindCollider(const std::string& Name)
{
	auto	iter = m_ColliderList.begin();
	auto	iterEnd = m_ColliderList.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->GetName() == Name)
			return *iter;
	}

	return nullptr;
}

void CGameObject::SetTexture(const std::string& Name)
{
	m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);

	SetSize((float)m_Texture->GetWidth(), (float)m_Texture->GetHeight());
}

void CGameObject::SetTexture(CTexture* Texture)
{
	m_Texture = Texture;

	SetSize((float)m_Texture->GetWidth(), (float)m_Texture->GetHeight());
}

void CGameObject::SetTexture(const std::string& Name, const TCHAR* FileName, 
	const std::string& PathName)
{
	m_Scene->GetSceneResource()->LoadTexture(Name, FileName, PathName);

	m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);

	SetSize((float)m_Texture->GetWidth(), (float)m_Texture->GetHeight());
}

void CGameObject::SetTextureFullPath(const std::string& Name,
	const TCHAR* FullPath)
{
	m_Scene->GetSceneResource()->LoadTextureFullPath(Name, FullPath);

	m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);

	SetSize((float)m_Texture->GetWidth(), (float)m_Texture->GetHeight());
}

#ifdef UNICODE

void CGameObject::SetTexture(const std::string& Name,
	const std::vector<std::wstring>& vecFileName, const std::string& PathName)
{
	m_Scene->GetSceneResource()->LoadTexture(Name, vecFileName, PathName);

	m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);

	SetSize((float)m_Texture->GetWidth(), (float)m_Texture->GetHeight());
}

void CGameObject::SetTextureFullPath(const std::string& Name,
	const std::vector<std::wstring>& vecFullPath)
{
	m_Scene->GetSceneResource()->LoadTextureFullPath(Name, vecFullPath);

	m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);

	SetSize((float)m_Texture->GetWidth(), (float)m_Texture->GetHeight());
}

#else

void CGameObject::SetTexture(const std::string& Name,
	const std::vector<std::string>& vecFileName, const std::string& PathName)
{
	m_Scene->GetSceneResource()->LoadTexture(Name, vecFileName, PathName);

	m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);

	SetSize((float)m_Texture->GetWidth(), (float)m_Texture->GetHeight());
}

void CGameObject::SetTextureFullPath(const std::string& Name,
	const std::vector<std::string>& vecFullPath)
{
	m_Scene->GetSceneResource()->LoadTextureFullPath(Name, vecFullPath);

	m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);

	SetSize((float)m_Texture->GetWidth(), (float)m_Texture->GetHeight());
}

#endif

void CGameObject::SetMapTexture(const std::string& Name)
{
	m_MapColTexture = m_Scene->GetSceneResource()->FindTexture(Name);

	SetSize((float)m_MapColTexture->GetWidth(), (float)m_MapColTexture->GetHeight());
}

void CGameObject::SetMapTexture(CTexture* Texture)
{
	m_MapColTexture = Texture;

	SetSize((float)m_MapColTexture->GetWidth(), (float)m_MapColTexture->GetHeight());
}

void CGameObject::SetMapTexture(const std::string& Name, const TCHAR* FileName,
	const std::string& PathName)
{
	m_Scene->GetSceneResource()->LoadTexture(Name, FileName, PathName);

	m_MapColTexture = m_Scene->GetSceneResource()->FindTexture(Name);

	SetSize((float)m_MapColTexture->GetWidth(), (float)m_MapColTexture->GetHeight());
}

void CGameObject::SetMapTextureFullPath(const std::string& Name,
	const TCHAR* FullPath)
{
	m_Scene->GetSceneResource()->LoadTextureFullPath(Name, FullPath);

	m_MapColTexture = m_Scene->GetSceneResource()->FindTexture(Name);

	SetSize((float)m_MapColTexture->GetWidth(), (float)m_MapColTexture->GetHeight());
}

#ifdef UNICODE

void CGameObject::SetMapTexture(const std::string& Name,
	const std::vector<std::wstring>& vecFileName, const std::string& PathName)
{
	m_Scene->GetSceneResource()->LoadTexture(Name, vecFileName, PathName);

	m_MapColTexture = m_Scene->GetSceneResource()->FindTexture(Name);

	SetSize((float)m_MapColTexture->GetWidth(), (float)m_MapColTexture->GetHeight());
}

void CGameObject::SetMapTextureFullPath(const std::string& Name,
	const std::vector<std::wstring>& vecFullPath)
{
	m_Scene->GetSceneResource()->LoadTextureFullPath(Name, vecFullPath);

	m_MapColTexture = m_Scene->GetSceneResource()->FindTexture(Name);

	SetSize((float)m_MapColTexture->GetWidth(), (float)m_MapColTexture->GetHeight());
}

#else

void CGameObject::SetMapTexture(const std::string& Name,
	const std::vector<std::string>& vecFileName, const std::string& PathName)
{
	m_Scene->GetSceneResource()->LoadTexture(Name, vecFileName, PathName);

	m_MapColTexture = m_Scene->GetSceneResource()->FindTexture(Name);

	SetSize((float)m_MapColTexture->GetWidth(), (float)m_MapColTexture->GetHeight());
}

void CGameObject::SetMapTextureFullPath(const std::string& Name,
	const std::vector<std::string>& vecFullPath)
{
	m_Scene->GetSceneResource()->LoadTextureFullPath(Name, vecFullPath);

	m_MapColTexture = m_Scene->GetSceneResource()->FindTexture(Name);

	SetSize((float)m_MapColTexture->GetWidth(), (float)m_MapColTexture->GetHeight());
}

#endif


bool CGameObject::SetColorKey(unsigned char r, unsigned char g, unsigned char b, int Index)
{
	if (!m_Texture)
		return false;

	m_Texture->SetColorKey(r, g, b, Index);

	return true;
}

bool CGameObject::SetColorKeyAll(unsigned char r, unsigned char g, unsigned char b)
{
	if (!m_Texture)
		return false;

	m_Texture->SetColorKeyAll(r, g, b);

	return true;
}

void CGameObject::CreateAnimation()
{
	m_Animation = new CAnimation;

	m_Animation->m_Owner = this;
	m_Animation->m_Scene = m_Scene;
}

void CGameObject::AddAnimation(const std::string& SequenceName, bool Loop, 
	float PlayTime, float PlayScale, bool Reverse)
{
	m_Animation->AddAnimation(SequenceName, Loop, PlayTime, PlayScale, Reverse);
}

void CGameObject::SetPlayTime(const std::string& Name, float PlayTime)
{
	m_Animation->SetPlayTime(Name, PlayTime);
}

void CGameObject::SetPlayScale(const std::string& Name, float PlayScale)
{
	m_Animation->SetPlayScale(Name, PlayScale);
}

void CGameObject::SetPlayLoop(const std::string& Name, bool Loop)
{
	m_Animation->SetPlayLoop(Name, Loop);
}

void CGameObject::SetPlayReverse(const std::string& Name, bool Reverse)
{
	m_Animation->SetPlayReverse(Name, Reverse);
}

void CGameObject::SetCurrentAnimation(std::string& Name)
{
	m_Animation->SetCurrentAnimation(Name);
}

void CGameObject::ChangeAnimation(const std::string& Name)
{
	m_Animation->ChangeAnimation(Name);
}

bool CGameObject::CheckCurrentAnimation(const std::string& Name)
{
	return m_Animation->CheckCurrentAnimation(Name);
}

void CGameObject::MoveDir(const Vector2& Dir)
{
	m_Pos += Dir * m_MoveSpeed * DELTA_TIME * m_TimeScale;
}

void CGameObject::Move(const Vector2& MoveValue)
{
	m_Pos += MoveValue * m_TimeScale;
}

void CGameObject::Move(float Angle)
{
	Vector2	Dir;
	Dir.x = cosf(DegreeToRadian(Angle));
	Dir.y = sinf(DegreeToRadian(Angle));

	m_Pos += Dir * m_MoveSpeed * DELTA_TIME * m_TimeScale;
}

void CGameObject::DirAnimationCheck()
{
	if (m_PreDir != m_CurDir)
	{

		if (m_CurDir == ObjDir::Right)
		{
			m_ChangeDirText = "right";
		}
		else if (m_CurDir == ObjDir::Left)
		{
			m_ChangeDirText = "left";
		}

		m_Animation->ChangeAnimation(m_AnimationName + m_ChangeDirText);
		m_PreDir = m_CurDir;
	}

}

void CGameObject::StateChange(ObjState State)
{
	if (State != m_CurState)
	{
		switch (State)
		{
		case ObjState::Idle:
			IdleStart();
			break;
		case ObjState::Walk:
			WalkStart();
			break;
		case ObjState::Turn:
			TurnStart();
			break;
		case ObjState::Run:
			RunStart();
			break;
		case ObjState::Attack:
			AttackStart();
			break;
		case ObjState::HurtGround:
			HurtGroundStart();
			break;
		case ObjState::HurtFly:
			HurtFlyStart();
			break;
		case ObjState::Dead:
			DeadStart();
			break;

		}
		m_CurState = State;
	}
}

void CGameObject::ObjStateUpdate()
{
	switch (m_CurState)
	{
	case ObjState::Idle:
		IdleUpdate();
		break;
	case ObjState::Walk:
		WalkUpdate();
		break;
	case ObjState::Turn:
		TurnUpdate();
		break;
	case ObjState::Run:
		RunUpdate();
		break;
	case ObjState::Attack:
		AttackUpdate();
		break;
	case ObjState::HurtGround:
		HurtGroundUpdate();
		break;
	case ObjState::HurtFly:
		HurtFlyUpdate();
		break;
	case ObjState::Dead:
		DeadUpdate();
		break;

	}
}

void CGameObject::MapCollisionCheckMoveGround()
{
	{
		// �̷��� ��ġ�� ����Ͽ� �װ��� RGB���� üũ�ϰ�, �̵� ������ ���̸� �̵��Ѵ�.
		Vector2 NextPos = m_Pos + (Vector2{ 0,m_MoveDir.y } *DELTA_TIME * m_MoveSpeed);
		Vector2 CheckPos = NextPos + Vector2{ 0,0 };	// �̷� ��ġ�� �߱��� ����
		Vector2 CheckPosTopRight = NextPos + Vector2{ 18,-80 };	// �̷� ��ġ�� �Ӹ����� ����
		Vector2 CheckPosTopLeft = NextPos + Vector2{ -18,-80 };	// �̷� ��ġ�� �Ӹ����� ����

		int Color = m_MapColTexture->GetImagePixel(CheckPos);
		int TopRightColor = m_MapColTexture->GetImagePixel(CheckPosTopRight);
		int TopLeftColor = m_MapColTexture->GetImagePixel(CheckPosTopLeft);



		if (RGB(0, 0, 0) != Color &&
			RGB(0, 0, 0) != TopRightColor &&
			RGB(0, 0, 0) != TopLeftColor)
		{
			MoveDir(Vector2{ 0.f, m_MoveDir.y });
		}
	}

	{
		// �̷��� ��ġ�� ����Ͽ� �װ��� RGB���� üũ�ϰ�, �̵� ������ ���̸� �̵��Ѵ�.
		Vector2 NextPos = m_Pos + (Vector2{ m_MoveDir.x,0 } *DELTA_TIME * m_MoveSpeed);
		Vector2 CheckPos = NextPos + Vector2{ 0,0 };	// �̷� ��ġ�� �߱��� ����
		Vector2 CheckPosTopRight = NextPos + Vector2{ 18,-80 };	// �̷� ��ġ�� �Ӹ����� ����
		Vector2 CheckPosTopLeft = NextPos + Vector2{ -18,-80 };	// �̷� ��ġ�� �Ӹ����� ����
		Vector2 ForDownPos = m_Pos + Vector2{ 0,1.f };	// �� �Ʒ� ����

		int CurColor = m_MapColTexture->GetImagePixel(m_Pos);
		int ForDownColor = m_MapColTexture->GetImagePixel(ForDownPos);
		int Color = m_MapColTexture->GetImagePixel(CheckPos);
		int TopRightColor = m_MapColTexture->GetImagePixel(CheckPosTopRight);
		int TopLeftColor = m_MapColTexture->GetImagePixel(CheckPosTopLeft);


		// �׻� ���� �پ��ֱ�
		if (RGB(0, 0, 0) != ForDownColor && RGB(255, 0, 0) != ForDownColor)
		{
			SetPos(Vector2{ m_Pos.x, m_Pos.y + 1.5f });
		}

		// ��� �ö󰡱�
		while (RGB(0, 0, 0) == Color &&
			TopRightColor != RGB(0, 0, 0) && TopLeftColor != RGB(0, 0, 0))
		{
			CheckPos.y -= 1.0f;
			Color = m_MapColTexture->GetImagePixel(CheckPos);
			SetPos(Vector2{ m_Pos.x, m_Pos.y - 1.0f });
		}


		if (RGB(0, 0, 0) != Color &&
			RGB(0, 0, 0) != TopRightColor &&
			RGB(0, 0, 0) != TopLeftColor)
		{
			MoveDir(Vector2{ m_MoveDir.x,0 });
		}

	}

}

void CGameObject::MapCollisionCheckMoveAir()
{
	{
		// �̷��� ��ġ�� ����Ͽ� �װ��� RGB���� üũ�ϰ�, �̵� ������ ���̸� �̵��Ѵ�.
		Vector2 NextPos = m_Pos + (Vector2{ 0,m_MoveDir.y } *DELTA_TIME);
		Vector2 CheckPos = NextPos + Vector2{ 0,0 };	// �̷� ��ġ�� �߱��� ����
		Vector2 CheckPosTopRight = NextPos + Vector2{ 18,-80 };	// �̷� ��ġ�� �Ӹ����� ����
		Vector2 CheckPosTopLeft = NextPos + Vector2{ -18,-80 };	// �̷� ��ġ�� �Ӹ����� ����

		int Color = m_MapColTexture->GetImagePixel(CheckPos);
		int TopRightColor = m_MapColTexture->GetImagePixel(CheckPosTopRight);
		int TopLeftColor = m_MapColTexture->GetImagePixel(CheckPosTopLeft);


		if (RGB(0, 0, 0) != Color &&
			RGB(0, 0, 0) != TopRightColor &&
			RGB(0, 0, 0) != TopLeftColor)
		{
			Move(Vector2{ 0.f , m_MoveDir.y } *DELTA_TIME);
		}
	}

	{
		// �̷��� ��ġ�� ����Ͽ� �װ��� RGB���� üũ�ϰ�, �̵� ������ ���̸� �̵��Ѵ�.
		Vector2 NextPos = m_Pos + (Vector2{ m_MoveDir.x,0.f } *DELTA_TIME);
		Vector2 CheckPos = NextPos + Vector2{ 0.f, 0.f };	// �̷� ��ġ�� �߱��� ����
		Vector2 CheckPosTopRight = NextPos + Vector2{ 18,-80 };	// �̷� ��ġ�� �Ӹ����� ����
		Vector2 CheckPosTopLeft = NextPos + Vector2{ -18,-80 };	// �̷� ��ġ�� �Ӹ����� ����

		int Color = m_MapColTexture->GetImagePixel(CheckPos);
		int TopRightColor = m_MapColTexture->GetImagePixel(CheckPosTopRight);
		int TopLeftColor = m_MapColTexture->GetImagePixel(CheckPosTopLeft);

		if (RGB(0, 0, 0) != Color &&
			RGB(0, 0, 0) != TopRightColor &&
			RGB(0, 0, 0) != TopLeftColor)
		{
			Move(Vector2{ m_MoveDir.x,0 } *DELTA_TIME);
		}
	}

}

void CGameObject::MapCollisionCheckMoveGroundDie()
{
	{
		// �̷��� ��ġ�� ����Ͽ� �װ��� RGB���� üũ�ϰ�, �̵� ������ ���̸� �̵��Ѵ�.
		Vector2 NextPos = m_Pos + (Vector2{ 0,m_MoveDir.y } *DELTA_TIME);
		Vector2 CheckPos = NextPos + Vector2{ 0,0 };	// �̷� ��ġ�� �߱��� ����
		Vector2 CheckPosTopRight = NextPos + Vector2{ 18,-80 };	// �̷� ��ġ�� �Ӹ����� ����
		Vector2 CheckPosTopLeft = NextPos + Vector2{ -18,-80 };	// �̷� ��ġ�� �Ӹ����� ����

		int Color = m_MapColTexture->GetImagePixel(CheckPos);
		int TopRightColor = m_MapColTexture->GetImagePixel(CheckPosTopRight);
		int TopLeftColor = m_MapColTexture->GetImagePixel(CheckPosTopLeft);



		if (RGB(0, 0, 0) != Color && RGB(255, 0, 0) != Color &&
			RGB(0, 0, 0) != TopRightColor &&
			RGB(0, 0, 0) != TopLeftColor)
		{
			Move(Vector2{ 0.f, m_MoveDir.y } * DELTA_TIME);
		}
	}

	{
		// �̷��� ��ġ�� ����Ͽ� �װ��� RGB���� üũ�ϰ�, �̵� ������ ���̸� �̵��Ѵ�.
		Vector2 NextPos = m_Pos + (Vector2{ m_MoveDir.x, 0} *DELTA_TIME);
		Vector2 CheckPos = NextPos + Vector2{ 0,0 };	// �̷� ��ġ�� �߱��� ����
		Vector2 CheckPosTopRight = NextPos + Vector2{ 18,-80 };	// �̷� ��ġ�� �Ӹ����� ����
		Vector2 CheckPosTopLeft = NextPos + Vector2{ -18,-80 };	// �̷� ��ġ�� �Ӹ����� ����

		int Color = m_MapColTexture->GetImagePixel(CheckPos);
		int TopRightColor = m_MapColTexture->GetImagePixel(CheckPosTopRight);
		int TopLeftColor = m_MapColTexture->GetImagePixel(CheckPosTopLeft);

		if (RGB(0, 0, 0) != Color &&
			RGB(0, 0, 0) != TopRightColor &&
			RGB(0, 0, 0) != TopLeftColor)
		{
			Move(Vector2{ m_MoveDir.x,0 } * DELTA_TIME);
		}
	}

}

void CGameObject::MapCollisionCheckMoveAirDie()
{
	{
		// �̷��� ��ġ�� ����Ͽ� �װ��� RGB���� üũ�ϰ�, �̵� ������ ���̸� �̵��Ѵ�.
		Vector2 NextPos = m_Pos + (Vector2{ 0,m_MoveDir.y } *DELTA_TIME);
		Vector2 CheckPos = NextPos + Vector2{ 0,0 };	// �̷� ��ġ�� �߱��� ����
		Vector2 CheckPosTopRight = NextPos + Vector2{ 18,-80 };	// �̷� ��ġ�� �Ӹ����� ����
		Vector2 CheckPosTopLeft = NextPos + Vector2{ -18,-80 };	// �̷� ��ġ�� �Ӹ����� ����

		int Color = m_MapColTexture->GetImagePixel(CheckPos);
		int TopRightColor = m_MapColTexture->GetImagePixel(CheckPosTopRight);
		int TopLeftColor = m_MapColTexture->GetImagePixel(CheckPosTopLeft);



		if (RGB(0, 0, 0) != Color &&
			RGB(0, 0, 0) != TopRightColor &&
			RGB(0, 0, 0) != TopLeftColor)
		{
			Move(Vector2{ 0.f , m_MoveDir.y } * DELTA_TIME);
		}
	}

	{
		// �̷��� ��ġ�� ����Ͽ� �װ��� RGB���� üũ�ϰ�, �̵� ������ ���̸� �̵��Ѵ�.
		Vector2 NextPos = m_Pos + (Vector2{ m_MoveDir.x,0 } * DELTA_TIME);
		Vector2 CheckPos = NextPos + Vector2{ 0,0 };	// �̷� ��ġ�� �߱��� ����
		Vector2 CheckPosTopRight = NextPos + Vector2{ 18,-80 };	// �̷� ��ġ�� �Ӹ����� ����
		Vector2 CheckPosTopLeft = NextPos + Vector2{ -18,-80 };	// �̷� ��ġ�� �Ӹ����� ����

		int Color = m_MapColTexture->GetImagePixel(CheckPos);
		int TopRightColor = m_MapColTexture->GetImagePixel(CheckPosTopRight);
		int TopLeftColor = m_MapColTexture->GetImagePixel(CheckPosTopLeft);

		if (RGB(0, 0, 0) != Color &&
			RGB(0, 0, 0) != TopRightColor &&
			RGB(0, 0, 0) != TopLeftColor)
		{
			Move(Vector2{ m_MoveDir.x,0 } * DELTA_TIME);
		}
	}

}

void CGameObject::Start()
{
	m_Start = true;

	m_PrevPos = m_Pos;
}

bool CGameObject::Init()
{
	return true;
}

void CGameObject::Update(float DeltaTime)
{
	// �߷� ����
	if (!m_Ground && m_PhysicsSimulate)
	{
		// �������� �ð��� ���������ش�.
		m_FallTime += DeltaTime * m_GravityAccel;

		// 9.8 m/s^2
		// t�� �� y��
		// V : �ӵ� A : ���ӵ� G : �߷�
		// y = V * A - 0.5f * G * t * t
		// 0 = -0.5fGA^2 VA - y
		float Velocity = 0.f;

		if (m_Jump)
			Velocity = m_JumpVelocity * m_FallTime;

		m_Pos.y = m_FallStartY - (Velocity - 0.5f * GRAVITY * m_FallTime * m_FallTime);
	}

	if (m_Animation)
		m_Animation->Update(DeltaTime * m_TimeScale);

	{
		auto	iter = m_ColliderList.begin();
		auto	iterEnd = m_ColliderList.end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->GetActive())
			{
				iter = m_ColliderList.erase(iter);
				iterEnd = m_ColliderList.end();
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

	{
		auto	iter = m_WidgetComponentList.begin();
		auto	iterEnd = m_WidgetComponentList.end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->GetActive())
			{
				iter = m_WidgetComponentList.erase(iter);
				iterEnd = m_WidgetComponentList.end();
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

void CGameObject::PostUpdate(float DeltaTime)
{
	m_Move = m_Pos - m_PrevPos;

	// �ִϸ��̼��� ���۵� ��� �̹��� ũ��� ����� �����ϱ� ������ ���⿡�� �����
	// �ٽ� �����ֵ��� �Ѵ�.
	if (m_Animation)
	{
		CAnimationInfo* Current = m_Animation->m_CurrentAnimation;

		const AnimationFrameData& FrameData = Current->m_Sequence->GetFrame(Current->m_Frame);

		m_Size = FrameData.End - FrameData.Start;
	}

	{
		auto	iter = m_ColliderList.begin();
		auto	iterEnd = m_ColliderList.end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->GetActive())
			{
				iter = m_ColliderList.erase(iter);
				iterEnd = m_ColliderList.end();
				continue;
			}

			else if (!(*iter)->GetEnable())
			{
				++iter;
				continue;
			}

			(*iter)->PostUpdate(DeltaTime);

			m_Scene->GetCollision()->AddCollider(*iter);

			++iter;
		}
	}



	{
		auto	iter = m_WidgetComponentList.begin();
		auto	iterEnd = m_WidgetComponentList.end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->GetActive())
			{
				iter = m_WidgetComponentList.erase(iter);
				iterEnd = m_WidgetComponentList.end();
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

	if (m_Move.x != 0.f && m_SideWallCheck)
	{
		// ���������� �̵��Ҷ�
		if (m_Move.x > 0.f)
		{
			CheckMoveRight();
		}

		// �������� �̵��Ҷ�
		else
		{
			CheckMoveLeft();
		}
	}

	// �ٴڿ� ������Ų��.
	if (m_PhysicsSimulate && m_Move.y >= 0.f)
	{
		CTileMap* TileMap = m_Scene->GetTileMap();

		float	PrevBottom = m_PrevPos.y + (1.f - m_Pivot.y) * m_Size.y;
		float	CurBottom = m_Pos.y + (1.f - m_Pivot.y) * m_Size.y;

		float	PrevLeft = m_PrevPos.x - m_Pivot.x * m_Size.x;
		float	CurLeft = m_Pos.x - m_Pivot.x * m_Size.x;

		float	PrevRight = m_PrevPos.x + (1.f - m_Pivot.x) * m_Size.x;
		float	CurRight = m_Pos.x + (1.f - m_Pivot.x) * m_Size.x;

		float ResultLeft = PrevLeft < CurLeft ? PrevLeft : CurLeft;
		float ResultRight = PrevRight > CurRight ? PrevRight : CurRight;
		float ResultTop = PrevBottom < CurBottom ? PrevBottom : CurBottom;
		float ResultBottom = PrevBottom > CurBottom ? PrevBottom : CurBottom;

		int LeftIndex = TileMap->GetTileOriginIndexX(ResultLeft);
		int RightIndex = TileMap->GetTileOriginIndexX(ResultRight);
		int TopIndex = TileMap->GetTileOriginIndexY(ResultTop);
		int BottomIndex = TileMap->GetTileOriginIndexY(ResultBottom);

		LeftIndex = LeftIndex < 0 ? 0 : LeftIndex;
		TopIndex = TopIndex < 0 ? 0 : TopIndex;
		RightIndex = RightIndex > TileMap->GetCountX() - 1 ? TileMap->GetCountX() - 1 : RightIndex;
		BottomIndex = BottomIndex > TileMap->GetCountY() - 1 ? TileMap->GetCountY() - 1 : BottomIndex;

		if (LeftIndex <= TileMap->GetCountX() - 1 && TopIndex <= TileMap->GetCountY() - 1 &&
			RightIndex >= 0 && BottomIndex >= 0)
		{
			bool	Check = false;

			// ������ �Ʒ��� ���ʷ� �˻縦 �س�����.
			// �Ʒ��������� �ϰ� �Ǹ� ���� ���� ���� ��� �����ϰ� ó���ǹ��� ���� �ֱ� �����̴�.
			for (int i = TopIndex; i <= BottomIndex; ++i)
			{
				for (int j = LeftIndex; j <= RightIndex; ++j)
				{
					CTile* Tile = TileMap->GetTile(j, i);

					if (!Tile)
						continue;

					if (Tile->GetPos().y < PrevBottom)
						continue;

					// ���� Ÿ���� �̵��Ұ� Ÿ���� ��� �ٴ��� ��Ҵٴ� ���̴�.
					if (Tile->GetOption() == ETile_Option::ImpossibleToMove)
					{
						Check = true;
						m_FallTime = 0.f;

						// ���� Ÿ���� Top�� �� ������Ʈ�� Bottom������ �����Ѵ�.
						m_Pos.y = Tile->GetPos().y - (1.f - m_Pivot.y) * m_Size.y;
						m_Ground = true;
						m_Jump = false;
						break;
					}
				}

				if (Check)
					break;
			}

			// �ٴ��� ���� ���
			if (!Check)
			{
				// ���� ��� �ִ� ���¶�� ���� �������� ���°� �ɰ��̴�.
				if (m_Ground)
				{
					m_FallTime = 0.f;
					m_FallStartY = m_Pos.y;
				}

				m_Ground = false;
			}
		}
	}
}

void CGameObject::Render(HDC hDC, float DeltaTime)
{
	Vector2	Pos;
	Vector2	CameraPos;
	Vector2	Resolution;
	
	if (m_Scene)
	{
		CameraPos = m_Scene->GetCamera()->GetPos();
		Resolution = m_Scene->GetCamera()->GetResolution();
		Pos = m_Pos - m_Scene->GetCamera()->GetPos();
	}

	else
	{
		CScene* Scene = CSceneManager::GetInst()->GetScene();
		Pos = m_Pos - Scene->GetCamera()->GetPos();
		CameraPos = Scene->GetCamera()->GetPos();
		Resolution = Scene->GetCamera()->GetResolution();
	}

	if (m_Animation)
	{
		CAnimationInfo* Current = m_Animation->m_CurrentAnimation;

		const AnimationFrameData& FrameData = Current->m_Sequence->GetFrame(Current->m_Frame);

		Vector2	Size = FrameData.End - FrameData.Start;

		Vector2	RenderLT;

		RenderLT = Pos - m_Pivot * Size * m_RenderScale;

		Vector2	CullPos = m_Pos - m_Pivot * Size;

		if (CullPos.x > CameraPos.x + Resolution.x)
			return;

		else if (CullPos.x + Size.x < CameraPos.x)
			return;

		else if (CullPos.y > CameraPos.y + Resolution.y)
			return;

		else if (CullPos.y + Size.y < CameraPos.y)
			return;

		if (Current->m_Sequence->GetTextureType() == ETexture_Type::Sprite)
		{
			if (Current->m_Sequence->GetTexture()->GetEnableColorKey())
			{
				TransparentBlt(hDC, (int)RenderLT.x, (int)RenderLT.y,
					(int)Size.x * m_RenderScale, (int)Size.y * m_RenderScale,
					Current->m_Sequence->GetTexture()->GetDC(),
					(int)FrameData.Start.x, (int)FrameData.Start.y, 
					(int)Size.x, (int)Size.y,
					Current->m_Sequence->GetTexture()->GetColorKey());
			}

			else
			{
				BitBlt(hDC, (int)RenderLT.x, (int)RenderLT.y,
					(int)Size.x, (int)Size.y,
					Current->m_Sequence->GetTexture()->GetDC(),
					(int)FrameData.Start.x, (int)FrameData.Start.y, SRCCOPY);
			}
		}

		else
		{
			if (Current->m_Sequence->GetTexture()->GetEnableColorKey())
			{
				TransparentBlt(hDC, (int)RenderLT.x, (int)RenderLT.y,
					(int)Size.x * m_RenderScale, (int)Size.y * m_RenderScale,
					Current->m_Sequence->GetTexture()->GetDC(Current->m_Frame),
					(int)FrameData.Start.x, (int)FrameData.Start.y,
					(int)Size.x, (int)Size.y,
					Current->m_Sequence->GetTexture()->GetColorKey());
			}

			else
			{
				BitBlt(hDC, (int)RenderLT.x, (int)RenderLT.y,
					(int)Size.x, (int)Size.y,
					Current->m_Sequence->GetTexture()->GetDC(Current->m_Frame),
					(int)FrameData.Start.x, (int)FrameData.Start.y, SRCCOPY);
			}
		}
	}

	else
	{
		if (m_Texture)
		{
			Vector2	RenderLT;

			RenderLT = Pos - m_Pivot * m_Size * m_RenderScale;

			Vector2	CullPos = m_Pos - m_Pivot * m_Size;

			if (CullPos.x > CameraPos.x + Resolution.x)
				return;

			else if (CullPos.x + m_Size.x < CameraPos.x)
				return;

			else if (CullPos.y > CameraPos.y + Resolution.y)
				return;

			else if (CullPos.y + m_Size.y < CameraPos.y)
				return;

			if (m_Texture->GetEnableColorKey())
			{
				if (m_Texture->GetTextureType() == ETexture_Type::Sprite)
				{
					TransparentBlt(hDC, (int)RenderLT.x, (int)RenderLT.y,
						(int)m_Size.x * m_RenderScale, (int)m_Size.y* m_RenderScale, m_Texture->GetDC(),
						0, 0, (int)m_Size.x, (int)m_Size.y, m_Texture->GetColorKey());
				}

				else
				{
				}
			}

			else
			{
				if (m_Texture->GetTextureType() == ETexture_Type::Sprite)
				{
					BitBlt(hDC, (int)RenderLT.x, (int)RenderLT.y,
						(int)m_Size.x, (int)m_Size.y, m_Texture->GetDC(),
						0, 0, SRCCOPY);
				}

				else
				{
				}
			}
		}
	}



	auto	iter = m_ColliderList.begin();
	auto	iterEnd = m_ColliderList.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->GetActive())
		{
			iter = m_ColliderList.erase(iter);
			iterEnd = m_ColliderList.end();
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
	
	m_PrevPos = m_Pos;
}

float CGameObject::InflictDamage(float Damage)
{
	return Damage;
}

void CGameObject::Save(FILE* File)
{
	CRef::Save(File);

	fwrite(&m_RenderLayer, sizeof(ERender_Layer), 1, File);
	fwrite(&m_PrevPos, sizeof(Vector2), 1, File);
	fwrite(&m_Move, sizeof(Vector2), 1, File);
	fwrite(&m_Pos, sizeof(Vector2), 1, File);
	fwrite(&m_Size, sizeof(Vector2), 1, File);
	fwrite(&m_Pivot, sizeof(Vector2), 1, File);

	bool	Texture = false;

	if (m_Texture)
		Texture = true;

	fwrite(&Texture, sizeof(bool), 1, File);

	if (m_Texture)
	{
		// Texture ����
		m_Texture->Save(File);
	}

	bool	Animation = false;

	if (m_Animation)
		Animation = true;

	fwrite(&Animation, sizeof(bool), 1, File);

	if (m_Animation)
	{
		// Animation ����
	}

	fwrite(&m_TimeScale, sizeof(float), 1, File);
	fwrite(&m_MoveSpeed, sizeof(float), 1, File);

	fwrite(&m_PhysicsSimulate, sizeof(bool), 1, File);
	fwrite(&m_Ground, sizeof(bool), 1, File);

	fwrite(&m_GravityAccel, sizeof(float), 1, File);
	fwrite(&m_FallTime, sizeof(float), 1, File);
	fwrite(&m_FallStartY, sizeof(float), 1, File);
	fwrite(&m_JumpVelocity, sizeof(float), 1, File);

	fwrite(&m_Jump, sizeof(bool), 1, File);
}

void CGameObject::Load(FILE* File)
{
	CRef::Load(File);

	fread(&m_RenderLayer, sizeof(ERender_Layer), 1, File);
	fread(&m_PrevPos, sizeof(Vector2), 1, File);
	fread(&m_Move, sizeof(Vector2), 1, File);
	fread(&m_Pos, sizeof(Vector2), 1, File);
	fread(&m_Size, sizeof(Vector2), 1, File);
	fread(&m_Pivot, sizeof(Vector2), 1, File);

	bool	Texture = false;

	fread(&Texture, sizeof(bool), 1, File);

	if (Texture)
	{
		// Texture �ҷ�����
		m_Texture = m_Scene->GetSceneResource()->LoadTexture(File);
	}

	bool	Animation = false;

	fread(&Animation, sizeof(bool), 1, File);

	if (Animation)
	{
		// Animation �ҷ�����
	}

	fread(&m_TimeScale, sizeof(float), 1, File);
	fread(&m_MoveSpeed, sizeof(float), 1, File);

	fread(&m_PhysicsSimulate, sizeof(bool), 1, File);
	fread(&m_Ground, sizeof(bool), 1, File);

	fread(&m_GravityAccel, sizeof(float), 1, File);
	fread(&m_FallTime, sizeof(float), 1, File);
	fread(&m_FallStartY, sizeof(float), 1, File);
	fread(&m_JumpVelocity, sizeof(float), 1, File);

	fread(&m_Jump, sizeof(bool), 1, File);
}

void CGameObject::SaveFullPath(const char* FullPath)
{
	FILE* File = nullptr;

	fopen_s(&File, FullPath, "wb");

	if (!File)
		return;

	Save(File);

	fclose(File);
}

void CGameObject::LoadFullPath(const char* FullPath)
{
	FILE* File = nullptr;

	fopen_s(&File, FullPath, "rb");

	if (!File)
		return;

	Load(File);

	fclose(File);
}

void CGameObject::SaveFileName(const char* FileName, const std::string& PathName)
{
	const PathInfo* Info = CPathManager::GetInst()->FindPath(PathName);

	char	FullPath[MAX_PATH] = {};

	if (Info)
		strcpy_s(FullPath, Info->PathMultibyte);

	strcat_s(FullPath, FileName);

	SaveFullPath(FullPath);
}

void CGameObject::LoadFileName(const char* FileName, const std::string& PathName)
{
	const PathInfo* Info = CPathManager::GetInst()->FindPath(PathName);

	char	FullPath[MAX_PATH] = {};

	if (Info)
		strcpy_s(FullPath, Info->PathMultibyte);

	strcat_s(FullPath, FileName);

	LoadFullPath(FullPath);
}

void CGameObject::CheckMoveRight()
{
	Vector2	LT = m_Pos - m_Pivot * m_Size;
	Vector2	RB = LT + m_Size;

	Vector2	PrevLT = m_PrevPos - m_Pivot * m_Size;
	Vector2	PrevRB = PrevLT + m_Size;

	CTileMap* TileMap = m_Scene->GetTileMap();

	Vector2	ResultLT, ResultRB;

	ResultRB = RB;

	ResultLT.x = PrevRB.x;
	ResultLT.y = LT.y < PrevLT.y ? LT.y : PrevLT.y;

	ResultRB.y = RB.y > PrevRB.y ? RB.y : PrevRB.y;

	int LeftIndex = TileMap->GetTileOriginIndexX(ResultLT.x);
	int TopIndex = TileMap->GetTileOriginIndexY(ResultLT.y);
	int RightIndex = TileMap->GetTileOriginIndexX(ResultRB.x);
	int BottomIndex = TileMap->GetTileOriginIndexY(ResultRB.y);

	LeftIndex = LeftIndex < 0 ? 0 : LeftIndex;
	TopIndex = TopIndex < 0 ? 0 : TopIndex;
	RightIndex = RightIndex > TileMap->GetCountX() - 1 ? TileMap->GetCountX() - 1 : RightIndex;
	BottomIndex = BottomIndex > TileMap->GetCountY() - 1 ? TileMap->GetCountY() - 1 : BottomIndex;

	if (LeftIndex <= TileMap->GetCountX() - 1 && TopIndex <= TileMap->GetCountY() - 1 &&
		RightIndex >= 0 && BottomIndex >= 0)
	{
		bool	SideCollision = false;

		// ������ �Ʒ��� ���ʷ� �˻縦 �س�����.
		// �Ʒ��������� �ϰ� �Ǹ� ���� ���� ���� ��� �����ϰ� ó���ǹ��� ���� �ֱ� �����̴�.
		for (int i = TopIndex; i <= BottomIndex; ++i)
		{
			for (int j = LeftIndex; j <= RightIndex; ++j)
			{
				CTile* Tile = TileMap->GetTile(j, i);

				if (Tile->GetOption() != ETile_Option::ImpossibleToMove ||
					!Tile->GetSideCollision())
					continue;

				Vector2	TilePos = Tile->GetPos();
				Vector2	TileSize = Tile->GetSize();

				if (TilePos.y - 0.001f <= RB.y && RB.y <= TilePos.y + 0.001f)
					continue;

				/*if (RB.x - TilePos.x > 8.f)
					continue;*/

				// ���� ��ġ�� �簢���� Ÿ���� �浹���Ѽ� �İ������� �Ǵ��Ѵ�.
				if (LT.x <= TilePos.x + TileSize.x && LT.y <= TilePos.y + TileSize.y &&
					RB.x >= TilePos.x && RB.y >= TilePos.y)
				{
					SideCollision = true;

					// �󸶳� �İ������� ���Ѵ�.
					float MoveX = TilePos.x - RB.x - 0.001f;

					m_Pos.x += MoveX;
					m_Move.x += MoveX;
					break;
				}
			}

			if (SideCollision)
				break;
		}
	}
}

void CGameObject::CheckMoveLeft()
{
	Vector2	LT = m_Pos - m_Pivot * m_Size;
	Vector2	RB = LT + m_Size;

	Vector2	PrevLT = m_PrevPos - m_Pivot * m_Size;
	Vector2	PrevRB = PrevLT + m_Size;

	CTileMap* TileMap = m_Scene->GetTileMap();

	Vector2	ResultLT, ResultRB;

	ResultLT = LT;

	ResultLT.y = LT.y < PrevLT.y ? LT.y : PrevLT.y;

	ResultRB.x = PrevLT.x;
	ResultRB.y = RB.y > PrevRB.y ? RB.y : PrevRB.y;

	int LeftIndex = TileMap->GetTileOriginIndexX(ResultLT.x);
	int TopIndex = TileMap->GetTileOriginIndexY(ResultLT.y);
	int RightIndex = TileMap->GetTileOriginIndexX(ResultRB.x);
	int BottomIndex = TileMap->GetTileOriginIndexY(ResultRB.y);

	LeftIndex = LeftIndex < 0 ? 0 : LeftIndex;
	TopIndex = TopIndex < 0 ? 0 : TopIndex;
	RightIndex = RightIndex > TileMap->GetCountX() - 1 ? TileMap->GetCountX() - 1 : RightIndex;
	BottomIndex = BottomIndex > TileMap->GetCountY() - 1 ? TileMap->GetCountY() - 1 : BottomIndex;

	if (LeftIndex <= TileMap->GetCountX() - 1 && TopIndex <= TileMap->GetCountY() - 1 &&
		RightIndex >= 0 && BottomIndex >= 0)
	{
		bool	SideCollision = false;

		// ������ �Ʒ��� ���ʷ� �˻縦 �س�����.
		// �Ʒ��������� �ϰ� �Ǹ� ���� ���� ���� ��� �����ϰ� ó���ǹ��� ���� �ֱ� �����̴�.
		for (int i = TopIndex; i <= BottomIndex; ++i)
		{
			for (int j = RightIndex; j >= LeftIndex; --j)
			{
				CTile* Tile = TileMap->GetTile(j, i);

				if (Tile->GetOption() != ETile_Option::ImpossibleToMove ||
					!Tile->GetSideCollision())
					continue;

				Vector2	TilePos = Tile->GetPos();
				Vector2	TileSize = Tile->GetSize();

				if (TilePos.y - 0.001f <= RB.y && RB.y <= TilePos.y + 0.001f)
					continue;

				/*if (TilePos.x + TileSize.x - LT.x > 8.f)
					continue;*/

				// ���� ��ġ�� �簢���� Ÿ���� �浹���Ѽ� �İ������� �Ǵ��Ѵ�.
				if (LT.x <= TilePos.x + TileSize.x && LT.y <= TilePos.y + TileSize.y &&
					RB.x >= TilePos.x && RB.y >= TilePos.y)
				{
					SideCollision = true;

					// �󸶳� �İ������� ���Ѵ�.
					float MoveX = TilePos.x + TileSize.x - LT.x + 0.001f;

					m_Pos.x += MoveX;
					m_Move.x += MoveX;
					break;
				}
			}

			if (SideCollision)
				break;
		}
	}
}
