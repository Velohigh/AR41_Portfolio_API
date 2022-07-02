
#include "Effect_Hit_Lazer.h"
#include "../Scene/Scene.h"
#include "../GameManager.h"

extern Vector2 g_AttackDir;

CEffect_Hit_Lazer::CEffect_Hit_Lazer()
{
}

CEffect_Hit_Lazer::CEffect_Hit_Lazer(const CEffect_Hit_Lazer& Obj) :
	CEffect(Obj)
{
}

CEffect_Hit_Lazer::~CEffect_Hit_Lazer()
{
}

bool CEffect_Hit_Lazer::Init()
{
	//CEffect::Init();

	SetPivot(0.5f, 0.5f);
	SetMoveDir(g_AttackDir);
	SetPos(m_Scene->GetPlayer()->GetPos() - g_AttackDir * 2200.f);
	SetSpeed(25000.f);
	m_Time = 0.f;
	m_RenderLayer = ERender_Layer::Effect;

	SetRenderScale(2);

	return true;
}

void CEffect_Hit_Lazer::Update(float DeltaTime)
{
	CEffect::Update(DeltaTime);

	Move(m_MoveDir * DELTA_TIME * m_MoveSpeed);
	m_Time += DELTA_TIME;
	if (m_Time >= 2.f)
		SetActive(false);
}

void CEffect_Hit_Lazer::PostUpdate(float DeltaTime)
{
	CEffect::PostUpdate(DeltaTime);


}

void CEffect_Hit_Lazer::Render(HDC hDC, float DeltaTime)
{
	CEffect::Render(hDC, DeltaTime);
}
