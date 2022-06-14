
#include "StartScene.h"
#include "../GameObject/Player.h"
#include "../GameObject/Monster.h"
#include "../GameObject/BackObj.h"
#include "SceneResource.h"
#include "Camera.h"
#include "../Input.h"
#include "../Widget/StartWindow.h"
#include "../Resource/ResourceManager.h"

CStartScene::CStartScene()	:	
	Back(nullptr)
{
}

CStartScene::~CStartScene()
{
}

bool CStartScene::Init()
{
	GetCamera()->SetResolution(1280.f, 720.f);
	GetCamera()->SetWorldResolution(1280.f, 720.f);
	GetCamera()->SetTargetPivot(0.5f, 0.5f);

	// CreateWidgetWindow<CStartWindow>("StartWindow");

	Back = CreateObject<CBackObj>("BackObj");
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

		for (int i = 0; i <= 229; ++i)
		{
			CResourceManager::GetInst()->AddAnimationFrame("TitleAnimation_Change", 0.f, 0.f,
				1280.f, 720.f);
		}

		Back->AddAnimation("TitleAnimation_Change", true, 7.59f);
	}

	Back->ChangeAnimation("TitleAnimation_0");

	return true;
}

void CStartScene::Update(float DeltaTime)
{
	CScene::Update(DeltaTime);

	

}
