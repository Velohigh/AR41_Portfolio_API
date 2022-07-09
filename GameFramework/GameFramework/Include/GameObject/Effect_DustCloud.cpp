
#include "Effect.h"
#include "Effect_DustCloud.h"
#include "../Resource/ResourceManager.h"
#include <random>

CEffect_DustCloud::CEffect_DustCloud()
{
}

CEffect_DustCloud::CEffect_DustCloud(const CEffect_DustCloud& Obj) :
	CEffect(Obj)
{
}

CEffect_DustCloud::~CEffect_DustCloud()
{
}

bool CEffect_DustCloud::Init()
{
	CEffect::Init();

	// �ܺ� ����̽� ���������� �������� �޾ƿ´�.
	std::random_device rd;
	std::mt19937_64 mt_(rd());	// ���������� �õ带 �����Ѵ�.
	std::uniform_int_distribution<int> IntRange(80, 300);	// ���� ����
	m_MoveSpeed = static_cast<float>(IntRange(mt_));
	std::uniform_real_distribution<float> FloatRange(0, 0.7f);
	m_MoveDir = Vector2{ 0,FloatRange(mt_) };
	RandomValueX = Vector2{ FloatRange(mt_) - 0.35f , 0 };
	SetRenderScale(2);

	return true;
}

void CEffect_DustCloud::Update(float DeltaTime)
{
	CEffect::Update(DeltaTime);

	if (m_CurDir == ObjDir::Right)
	{
		MoveDir((Vector2{ 1.f, 0.f } - m_MoveDir));
	}
	else if (m_CurDir == ObjDir::Left)
	{
		MoveDir((Vector2{ -1.f, 0.f } - m_MoveDir));
	}
	else
	{
		MoveDir((Vector2{ RandomValueX.x, 0.f } - m_MoveDir));
	}

	//if (true == m_Animation->IsEndAnimation())
	//{
	//	SetActive(false);
	//}
}

void CEffect_DustCloud::PostUpdate(float DeltaTime)
{
	CEffect::PostUpdate(DeltaTime);
}

void CEffect_DustCloud::Render(HDC hDC, float DeltaTime)
{
	CEffect::Render(hDC, DeltaTime);
}
