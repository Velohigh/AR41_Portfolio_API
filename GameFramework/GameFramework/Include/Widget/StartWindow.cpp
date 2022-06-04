

#include "StartWindow.h"
#include "Button.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../GameManager.h"
#include "../Scene/MainScene.h"
#include "../Scene/SceneManager.h"
#include "../Input.h"
#include "ImageWidget.h"

CStartWindow::CStartWindow()
{
}

CStartWindow::~CStartWindow()
{
}

bool CStartWindow::Init()
{
	if (!CWidgetWindow::Init())
		return false;

	m_Scene->GetSceneResource()->LoadSound("UI", "ButtonHovered", false,
		"1Up.wav");
	m_Scene->GetSceneResource()->LoadSound("UI", "ButtonClick", false,
		"Stun.wav");

	SetSize(1280.f, 720.f);

	CImageWidget* Back = CreateWidget<CImageWidget>("Back");

	Back->SetTexture("StartBack", TEXT("GameBack.bmp"));

	Back->SetSize(1280.f, 720.f);

	CButton* StartButton = CreateWidget<CButton>("StartButton");

	StartButton->SetTexture("StartButton", TEXT("StartButton.bmp"));
	StartButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(200.f, 100.f));
	StartButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(200.f, 0.f), Vector2(400.f, 100.f));
	StartButton->SetButtonStateData(EButton_State::Click, Vector2(400.f, 0.f), Vector2(600.f, 100.f));
	StartButton->SetButtonStateData(EButton_State::Disable, Vector2(600.f, 0.f), Vector2(800.f, 100.f));

	StartButton->SetSound(EButton_Sound_State::MouseHovered, "ButtonHovered");
	StartButton->SetSound(EButton_Sound_State::Click, "ButtonClick");

	StartButton->SetPos(540.f, 210.f);
	StartButton->SetZOrder(1);

	StartButton->SetCallback<CStartWindow>(EButton_Sound_State::Click,
		this, &CStartWindow::StartButtonCallback);

	CButton* EndButton = CreateWidget<CButton>("EndButton");

	EndButton->SetTexture("EndButton", TEXT("EditButton.bmp"));
	EndButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(200.f, 100.f));
	EndButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(200.f, 0.f), Vector2(400.f, 100.f));
	EndButton->SetButtonStateData(EButton_State::Click, Vector2(400.f, 0.f), Vector2(600.f, 100.f));
	EndButton->SetButtonStateData(EButton_State::Disable, Vector2(600.f, 0.f), Vector2(800.f, 100.f));

	EndButton->SetSound(EButton_Sound_State::MouseHovered, "ButtonHovered");
	EndButton->SetSound(EButton_Sound_State::Click, "ButtonClick");

	EndButton->SetPos(540.f, 410.f);
	EndButton->SetZOrder(1);

	EndButton->SetCallback<CStartWindow>(EButton_Sound_State::Click,
		this, &CStartWindow::EndButtonCallback);


	return true;
}

void CStartWindow::StartButtonCallback()
{
	CInput::GetInst()->ClearCallback();
	CSceneManager::GetInst()->CreateScene<CMainScene>();
}

void CStartWindow::EndButtonCallback()
{
	CGameManager::GetInst()->Exit();
}
