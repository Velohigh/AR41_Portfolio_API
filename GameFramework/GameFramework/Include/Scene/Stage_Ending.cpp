
#include "Stage_Ending.h"

#include "../GameObject/Player.h"
#include "../GameObject/Monster.h"
#include "../GameObject/BackObj.h"
#include "SceneResource.h"
#include "Camera.h"
#include "../Resource/Texture/Texture.h"
#include "../Input.h"
#include "../Widget/StartWindow.h"
#include "../Resource/ResourceManager.h"
#include "../Scene/SceneManager.h"
#include "../Scene/Stage_1.h"
#include "../GameManager.h"

CStage_Ending::CStage_Ending() :
	Back(nullptr)
{
}

CStage_Ending::~CStage_Ending()
{
}

bool CStage_Ending::Init()
{
	CScene::Init();

	GetCamera()->SetResolution(1280.f, 720.f);
	GetCamera()->SetWorldResolution(1280.f, 720.f);
	GetCamera()->SetTargetPivot(0.5f, 0.5f);

	// CreateWidgetWindow<CStartWindow>("StartWindow");

	Back = CreateObject<CBackObj>("BackObj");
	CreateAnimationSequence();

	GetSceneResource()->LoadSound("BGM", "bgm_ending", true, "bgm_ending.mp3");
	GetSceneResource()->SoundPlay("bgm_ending");


	CInput::GetInst()->AddBindFunction<CStage_Ending>("Enter",
		Input_Type::Down, this, &CStage_Ending::EnterPush);

	return true;
}

void CStage_Ending::Update(float DeltaTime)
{
	CScene::Update(DeltaTime);

}

void CStage_Ending::CreateAnimationSequence()
{
	Back->CreateAnimation();

	// Ending Animation
	{
		std::vector<std::wstring>	vecFileName;

		for (int i = 0; i <= 138; ++i)
		{
			TCHAR	FileName[MAX_PATH] = {};
			// %d에 i의 값이 대입되어 문자열이 만들어지게 된다.
			wsprintf(FileName, TEXT("Ending/Ending_ThanksForWatching/%d.bmp"), i);
			vecFileName.push_back(FileName);
		}

		CResourceManager::GetInst()->CreateAnimationSequence("Ending_ThanksForWatching",
			"Ending_ThanksForWatching", vecFileName, TEXTURE_PATH);

		for (int i = 0; i <= 138; ++i)
		{
			CResourceManager::GetInst()->AddAnimationFrame("Ending_ThanksForWatching", 0.f, 0.f,
				1280.f, 720.f);
		}

		Back->AddAnimation("Ending_ThanksForWatching", true, 5.f);
	}

	Back->ChangeAnimation("Ending_ThanksForWatching");
}

void CStage_Ending::EnterPush()
{
	DestroyWindow(CGameManager::GetInst()->GetWindowHandle());
}
