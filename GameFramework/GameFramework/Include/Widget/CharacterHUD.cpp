
#include "CharacterHUD.h"
#include "Button.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../GameManager.h"
#include "../Scene/MainScene.h"
#include "../Scene/SceneManager.h"
#include "../Input.h"
#include "ProgressBar.h"
#include "ImageWidget.h"

CCharacterHUD::CCharacterHUD()
{
}

CCharacterHUD::~CCharacterHUD()
{
}

void CCharacterHUD::SetHP(float HP)
{
	m_HPBar->SetValue(HP);
}

bool CCharacterHUD::Init()
{
	if (!CWidgetWindow::Init())
		return false;

	/*m_Scene->GetSceneResource()->LoadSound("UI", "ButtonHovered", false,
		"1Up.wav");
	m_Scene->GetSceneResource()->LoadSound("UI", "ButtonClick", false,
		"Stun.wav");*/

	SetSize(210.f, 110.f);
	SetPos(50.f, 50.f);

	m_HPBarFrame = CreateWidget<CImageWidget>("HPBarFrame");

	m_HPBarFrame->SetTexture("BarFrame", TEXT("BarBack.bmp"));
	m_HPBarFrame->SetColorKey(255, 0, 255);

	m_HPBarFrame->SetSize(220.f, 50.f);

	m_HPBar = CreateWidget<CProgressBar>("HPBar");

	m_HPBar->SetTexture(EProgressBar_Texture_Type::Bar, "HPBar", TEXT("BarDefault.bmp"));

	m_HPBar->SetSize(200.f, 30.f);
	m_HPBar->SetPos(10.f, 10.f);
	m_HPBar->SetBarDir(EProgressBar_Dir::LeftToRight);

	return true;
}
