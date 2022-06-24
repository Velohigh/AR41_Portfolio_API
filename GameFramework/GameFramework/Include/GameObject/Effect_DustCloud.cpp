
#include "Effect_DustCloud.h"
#include "../Resource/ResourceManager.h"
#include <random>

CEffect_DustCloud::CEffect_DustCloud()
{
	SetTypeID<CEffect_DustCloud>();
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

	// Dust_Cloud Animation
	{
		std::vector<std::wstring>	vecFileName;

		for (int i = 0; i <= 6; ++i)
		{
			TCHAR	FileName[MAX_PATH] = {};
			// %d�� i�� ���� ���ԵǾ� ���ڿ��� ��������� �ȴ�.
			wsprintf(FileName, TEXT("Effect/spr_dustcloud/%d.bmp"), i);
			vecFileName.push_back(FileName);
		}

		CResourceManager::GetInst()->CreateAnimationSequence("spr_dustcloud",
			"spr_dustcloud", vecFileName, TEXTURE_PATH);

		for (int i = 0; i <= 6; ++i)
		{
			CResourceManager::GetInst()->AddAnimationFrame("spr_dustcloud", 0.f, 0.f,
				19.f, 19.f);
		}

		CResourceManager::GetInst()->SetColorKey("spr_dustcloud", 255, 255, 255);

		AddAnimation("spr_dustcloud", true, 0.42f);
	}

	ChangeAnimation("spr_dustcloud");

	SetPivot(0.5f, 0.5f);

	// �ܺ� ����̽� ���������� �������� �޾ƿ´�.
	std::random_device rd;
	std::mt19937_64 mt_(rd());	// ���������� �õ带 �����Ѵ�.
	std::uniform_int_distribution<int> IntRange(80, 300);	// ���� ����
	m_MoveSpeed = static_cast<float>(IntRange(mt_));
	std::uniform_real_distribution<float> FloatRange(0, 0.7f);
	m_MoveDir = Vector2{ 0,FloatRange(mt_) };

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

	if (true == m_Animation->IsEndAnimation())
	{
		SetActive(false);
	}
}

void CEffect_DustCloud::PostUpdate(float DeltaTime)
{
	CEffect::PostUpdate(DeltaTime);
}

void CEffect_DustCloud::Render(HDC hDC, float DeltaTime)
{
	CEffect::Render(hDC, DeltaTime);
}
