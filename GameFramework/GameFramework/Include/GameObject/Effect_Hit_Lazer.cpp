
#include "Effect_Hit_Lazer.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../GameManager.h"
#include "../Scene/Camera.h"
#include "../Scene/SceneManager.h"
#include "../Resource/Texture/Texture.h"
#include "../Collision/Collider.h"

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
	//SetSpeed(100.f);
	m_Time = 0.f;
	m_RenderLayer = ERender_Layer::Effect;

	SetRenderScale(1);

	m_Scene->GetSceneResource()->LoadTexture("Plg", TEXT("Plg.bmp"));
	m_PlgTexture = m_Scene->GetSceneResource()->FindTexture("Plg");

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

	float fCenterX = (float)(m_Texture->GetWidth() >> 1);
	float fCenterY = (float)(m_Texture->GetHeight() >> 1);
	float fDis = sqrtf(fCenterX * fCenterX + fCenterY * fCenterY);

	m_ptPos[0].x = (LONG)(fCenterX + cosf((135.f + m_Angle) * PI / 180.f) * fDis);
	m_ptPos[0].y = (LONG)(fCenterX - sinf((135.f + m_Angle) * PI / 180.f) * fDis);

	m_ptPos[1].x = (LONG)(fCenterX + cosf((45.f + m_Angle) * PI / 180.f) * fDis);
	m_ptPos[1].y = (LONG)(fCenterX - sinf((45.f + m_Angle) * PI / 180.f) * fDis);

	m_ptPos[2].x = (LONG)(fCenterX + cosf((225.f + m_Angle) * PI / 180.f) * fDis);
	m_ptPos[2].y = (LONG)(fCenterX - sinf((225.f + m_Angle) * PI / 180.f) * fDis);

}

void CEffect_Hit_Lazer::Render(HDC hDC, float DeltaTime)
{
	//CEffect::Render(hDC, DeltaTime);

	HDC hPlgDC = m_PlgTexture->GetDC();

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

	PlgBlt(hPlgDC,
		m_ptPos,
		m_Texture->GetDC(),
		0, 0,
		900, 4,
		NULL, NULL, NULL);

	GdiTransparentBlt(hDC,
		Pos.x - (m_Size.x / 2.f),
		Pos.y - (m_Size.y / 2.f),
		m_Size.x, m_Size.y,
		hPlgDC,
		0, 0,
		300, 300,
		RGB(255, 0, 255));


	m_PrevPos = m_Pos;

}
