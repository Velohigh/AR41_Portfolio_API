
#include "CharacterHUD.h"
#include "Button.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../GameManager.h"
#include "../Scene/Stage_1.h"
#include "../Scene/SceneManager.h"
#include "../Input.h"
#include "ProgressBar.h"
#include "ImageWidget.h"
#include "Text.h"

CCharacterHUD::CCharacterHUD()
{
}

CCharacterHUD::~CCharacterHUD()
{
}

void CCharacterHUD::SetBatteryBar(float Battery)
{
	m_BatteryBar->SetValue(Battery);
}

void CCharacterHUD::SetTimeBar(float Time)
{
	m_TimeBar->SetValue(Time);
}

bool CCharacterHUD::Init()
{
	if (!CWidgetWindow::Init())
		return false;

	//m_Scene->GetSceneResource()->LoadSound("UI", "ButtonHovered", false,
	//	"1Up.wav");
	//m_Scene->GetSceneResource()->LoadSound("UI", "ButtonClick", false,
	//	"Stun.wav");

	SetSize(1280.f, 46.f);
	SetPos(0.f, 0.f);

	m_HudFrame = CreateWidget<CImageWidget>("Hud_Collapse");

	m_HudFrame->SetTexture("Hud_Collapse", TEXT("hud_collapse.bmp"));
	m_HudFrame->SetColorKey(255, 0, 255);

	m_HudFrame->SetSize(1280.f, 46.f);

	m_BatteryBar = CreateWidget<CProgressBar>("BatteryBar");
	m_BatteryBar->SetTexture(EProgressBar_Texture_Type::Bar, "BatteryBar", TEXT("effect_battery.bmp"));
	m_BatteryBar->SetSize(110.f, 20.f);
	m_BatteryBar->SetPos(24.f, 14.f);
	m_BatteryBar->SetBarDir(EProgressBar_Dir::LeftToRight);
	m_BatteryBar->SetColorKey(EProgressBar_Texture_Type::Bar, 255, 0, 255);

	m_TimeBar = CreateWidget<CProgressBar>("TimeBar");
	m_TimeBar->SetTexture(EProgressBar_Texture_Type::Bar, "TimeBar", TEXT("effect_timer.bmp"));
	m_TimeBar->SetSize(188.f, 22.f);
	m_TimeBar->SetPos(551.f, 6.f);
	m_TimeBar->SetBarDir(EProgressBar_Dir::LeftToRight);
	m_TimeBar->SetColorKey(EProgressBar_Texture_Type::Bar, 255, 0, 255);

	m_katana = CreateWidget<CImageWidget>("Katana_Icon");
	m_katana->SetTexture("Katana_Icon", TEXT("spr_katanaicons.bmp"));
	m_katana->SetColorKey(255, 255, 255);
	m_katana->SetSize(40.f, 40.f);
	m_katana->SetPos(1148, 3);

	//m_FPSText = CreateWidget<CText>("Text");

	//m_FPSText->SetText(TEXT("FPS"));
	//m_FPSText->SetPos(900.f, 50.f);
	//m_FPSText->SetTextColor(255, 0, 0);

	//m_FPSText->EnableShadow(true);
	//m_FPSText->SetShadowOffset(2.f, 2.f);

	return true;
}

void CCharacterHUD::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);

	//float FPS = CGameManager::GetInst()->GetFPS();

	//char	Text[256] = {};
	//sprintf_s(Text, "FPS : %.5f", FPS);

	//TCHAR	Unicode[256] = {};
	//int Length = MultiByteToWideChar(CP_ACP, 0, Text, -1, 0, 0);
	//MultiByteToWideChar(CP_ACP, 0, Text, -1, Unicode, Length);

	//m_FPSText->SetText(Unicode);
}
