
#include "TitleScene.h"
#include "../GameObject/Player.h"
#include "../GameObject/Monster.h"
#include "../GameObject/BackObj.h"
#include "SceneResource.h"
#include "Camera.h"
#include "../Input.h"
#include "../Widget/StartWindow.h"
#include "../Resource/ResourceManager.h"
#include "../Scene/SceneManager.h"
#include "../Scene/Stage_1.h"

CTitleScene::CTitleScene()	:
	Back(nullptr)
{
}

CTitleScene::~CTitleScene()
{
}

bool CTitleScene::Init()
{


	GetCamera()->SetResolution(1280.f, 720.f);
	GetCamera()->SetWorldResolution(1280.f, 720.f);
	GetCamera()->SetTargetPivot(0.5f, 0.5f);

	// CreateWidgetWindow<CStartWindow>("StartWindow");

	Back = CreateObject<CBackObj>("BackObj");
	CreateAnimationSequence();

	GetSceneResource()->LoadSound("BGM", "TitleBGM", true, "song_rainonbrick.ogg");
	GetSceneResource()->LoadSound("BGM2", "TitleBGM2", true, "sound_ambience_rain_title_01.wav");
	GetSceneResource()->LoadSound("Effect", "sound_menubeep_1", false, "sound_menubeep_1.wav");
	GetSceneResource()->LoadSound("Effect", "sound_menubeep_2", false, "sound_menubeep_2.wav");
	GetSceneResource()->SoundPlay("TitleBGM");
	GetSceneResource()->SoundPlay("TitleBGM2");
	GetSceneResource()->SetVolume("BGM2", 40);

	// 키 입력 함수 포인터
	CInput::GetInst()->AddBindFunction<CTitleScene>("MoveUp",
		Input_Type::Down, this, &CTitleScene::MoveUpPush);

	CInput::GetInst()->AddBindFunction<CTitleScene>("MoveDown",
		Input_Type::Down, this, &CTitleScene::MoveDownPush);

	CInput::GetInst()->AddBindFunction<CTitleScene>("ArrowUp",
		Input_Type::Down, this, &CTitleScene::MoveUpPush);

	CInput::GetInst()->AddBindFunction<CTitleScene>("ArrowDown",
		Input_Type::Down, this, &CTitleScene::MoveDownPush);

	CInput::GetInst()->AddBindFunction<CTitleScene>("Enter",
		Input_Type::Down, this, &CTitleScene::EnterPush);

	return true;
}

void CTitleScene::Update(float DeltaTime)
{
	CScene::Update(DeltaTime);

	//  값이 바뀐경우
	if (m_iSelect != m_iPreSelect)
	{
		if (m_iSelect == 0)
		{
			Back->ChangeAnimation("TitleAnimation_0");
		}
		else if (m_iSelect == 1)
		{
			Back->ChangeAnimation("TitleAnimation_1");
		}

		else if (m_iSelect == 2)
		{
			Back->ChangeAnimation("TitleAnimation_2");
		}
		else if (m_iSelect == 3)
		{
			Back->ChangeAnimation("TitleAnimation_3");
		}
		else if (m_iSelect == 4)
		{
			Back->ChangeAnimation("TitleAnimation_4");
		}

		GetSceneResource()->SoundPlay("sound_menubeep_1");
		m_iPreSelect = m_iSelect;
	}

}

void CTitleScene::CreateAnimationSequence()
{
	Back->CreateAnimation();

	// Title Animation0
	{
		std::vector<std::wstring>	vecFileName;

		for (int i = 0; i <= 229; ++i)
		{
			TCHAR	FileName[MAX_PATH] = {};
			// %d에 i의 값이 대입되어 문자열이 만들어지게 된다.
			wsprintf(FileName, TEXT("Title/TitleAnimation_0/%d.bmp"), i);
			vecFileName.push_back(FileName);
		}

		CResourceManager::GetInst()->CreateAnimationSequence("TitleAnimation_0",
			"TitleAnimation_0", vecFileName, TEXTURE_PATH);

		for (int i = 0; i <= 229; ++i)
		{
			CResourceManager::GetInst()->AddAnimationFrame("TitleAnimation_0", 0.f, 0.f,
				1280.f, 720.f);
		}

		Back->AddAnimation("TitleAnimation_0", true, 7.59f);
	}

	// Title Animation1
	{
		std::vector<std::wstring>	vecFileName;

		for (int i = 0; i <= 229; ++i)
		{
			TCHAR	FileName[MAX_PATH] = {};
			// %d에 i의 값이 대입되어 문자열이 만들어지게 된다.
			wsprintf(FileName, TEXT("Title/TitleAnimation_1/%d.bmp"), i);
			vecFileName.push_back(FileName);
		}

		CResourceManager::GetInst()->CreateAnimationSequence("TitleAnimation_1",
			"TitleAnimation_1", vecFileName, TEXTURE_PATH);

		for (int i = 0; i <= 229; ++i)
		{
			CResourceManager::GetInst()->AddAnimationFrame("TitleAnimation_1", 0.f, 0.f,
				1280.f, 720.f);
		}

		Back->AddAnimation("TitleAnimation_1", true, 7.59f);
	}

	// Title Animation2
	{
		std::vector<std::wstring>	vecFileName;

		for (int i = 0; i <= 229; ++i)
		{
			TCHAR	FileName[MAX_PATH] = {};
			// %d에 i의 값이 대입되어 문자열이 만들어지게 된다.
			wsprintf(FileName, TEXT("Title/TitleAnimation_2/%d.bmp"), i);
			vecFileName.push_back(FileName);
		}

		CResourceManager::GetInst()->CreateAnimationSequence("TitleAnimation_2",
			"TitleAnimation_2", vecFileName, TEXTURE_PATH);

		for (int i = 0; i <= 229; ++i)
		{
			CResourceManager::GetInst()->AddAnimationFrame("TitleAnimation_2", 0.f, 0.f,
				1280.f, 720.f);
		}

		Back->AddAnimation("TitleAnimation_2", true, 7.59f);
	}

	// Title Animation3
	{
		std::vector<std::wstring>	vecFileName;

		for (int i = 0; i <= 229; ++i)
		{
			TCHAR	FileName[MAX_PATH] = {};
			// %d에 i의 값이 대입되어 문자열이 만들어지게 된다.
			wsprintf(FileName, TEXT("Title/TitleAnimation_3/%d.bmp"), i);
			vecFileName.push_back(FileName);
		}

		CResourceManager::GetInst()->CreateAnimationSequence("TitleAnimation_3",
			"TitleAnimation_3", vecFileName, TEXTURE_PATH);

		for (int i = 0; i <= 229; ++i)
		{
			CResourceManager::GetInst()->AddAnimationFrame("TitleAnimation_3", 0.f, 0.f,
				1280.f, 720.f);
		}

		Back->AddAnimation("TitleAnimation_3", true, 7.59f);
	}

	// Title Animation4
	{
		std::vector<std::wstring>	vecFileName;

		for (int i = 0; i <= 229; ++i)
		{
			TCHAR	FileName[MAX_PATH] = {};
			// %d에 i의 값이 대입되어 문자열이 만들어지게 된다.
			wsprintf(FileName, TEXT("Title/TitleAnimation_4/%d.bmp"), i);
			vecFileName.push_back(FileName);
		}

		CResourceManager::GetInst()->CreateAnimationSequence("TitleAnimation_4",
			"TitleAnimation_4", vecFileName, TEXTURE_PATH);

		for (int i = 0; i <= 229; ++i)
		{
			CResourceManager::GetInst()->AddAnimationFrame("TitleAnimation_4", 0.f, 0.f,
				1280.f, 720.f);
		}

		Back->AddAnimation("TitleAnimation_4", true, 7.59f);
	}

	// Title Animation_Change
	{
		std::vector<std::wstring>	vecFileName;

		for (int i = 0; i <= 39; ++i)
		{
			TCHAR	FileName[MAX_PATH] = {};
			// %d에 i의 값이 대입되어 문자열이 만들어지게 된다.
			wsprintf(FileName, TEXT("Title/TitleAnimation_Change/%d.bmp"), i);
			vecFileName.push_back(FileName);
		}

		CResourceManager::GetInst()->CreateAnimationSequence("TitleAnimation_Change",
			"TitleAnimation_Change", vecFileName, TEXTURE_PATH);

		for (int i = 0; i <= 39; ++i)
		{
			CResourceManager::GetInst()->AddAnimationFrame("TitleAnimation_Change", 0.f, 0.f,
				1280.f, 720.f);
		}

		Back->AddAnimation("TitleAnimation_Change", true, 1.287f);
	}

	Back->ChangeAnimation("TitleAnimation_0");
}

void CTitleScene::MoveUpPush()
{
	if (m_iSelect > 0)
		m_iSelect -= 1;

}

void CTitleScene::MoveDownPush()
{
	if (m_iSelect < 4)
		m_iSelect += 1;

}

void CTitleScene::EnterPush()
{
	if (m_iSelect == 0)
	{
		Back->ChangeAnimation("TitleAnimation_Change");
		GetSceneResource()->SoundPlay("sound_menubeep_2");
		Back->SetEndFunction<CTitleScene>("TitleAnimation_Change", this, &CTitleScene::SceneChange);
	}

}

void CTitleScene::SceneChange()
{
	if (m_iSelect == 0)
	{
		CInput::GetInst()->ClearCallback();
		CSceneManager::GetInst()->CreateScene<CStage_1>();
	}
}
