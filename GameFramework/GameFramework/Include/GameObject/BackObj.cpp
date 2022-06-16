
#include "BackObj.h"
#include "../Input.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Scene/SceneManager.h"

CBackObj::CBackObj()
{
	SetTypeID<CBackObj>();
	m_RenderLayer = ERender_Layer::Back;
}

CBackObj::CBackObj(const CBackObj& Obj)	:
	CGameObject(Obj)
{
}

CBackObj::~CBackObj()
{
}

bool CBackObj::Init()
{
	SetPos(0.f, 0.f);
	SetSize(1500.f, 1200.f);
	SetPivot(0.f, 0.f);

	SetTexture("TitleBackGround", TEXT("TitleBackGround.bmp"));

	// 키 입력 함수 포인터
	CInput::GetInst()->AddBindFunction<CBackObj>("MoveUp",
		Input_Type::Down, this, &CBackObj::MoveUpPush);

	CInput::GetInst()->AddBindFunction<CBackObj>("MoveDown",
		Input_Type::Down, this, &CBackObj::MoveDownPush);

	CInput::GetInst()->AddBindFunction<CBackObj>("ArrowUp",
		Input_Type::Down, this, &CBackObj::MoveUpPush);

	CInput::GetInst()->AddBindFunction<CBackObj>("ArrowDown",
		Input_Type::Down, this, &CBackObj::MoveDownPush);

	CInput::GetInst()->AddBindFunction<CBackObj>("Enter",
		Input_Type::Down, this, &CBackObj::EnterPush);


	return true;
}

void CBackObj::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	//  값이 바뀐경우
	if (m_iSelect != m_iPreSelect)
	{
		if (m_iSelect == 0)
		{
			ChangeAnimation("TitleAnimation_0");
		}
		else if (m_iSelect == 1)
		{
			ChangeAnimation("TitleAnimation_1");
		}

		else if (m_iSelect == 2)
		{
			ChangeAnimation("TitleAnimation_2");
		}
		else if (m_iSelect == 3)
		{
			ChangeAnimation("TitleAnimation_3");
		}
		else if (m_iSelect == 4)
		{
			ChangeAnimation("TitleAnimation_4");
		}

		m_Scene->GetSceneResource()->SoundPlay("sound_menubeep_1");
		m_iPreSelect = m_iSelect;
	}
}

void CBackObj::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);
}

void CBackObj::MoveUpPush()
{
	if (m_iSelect > 0)
		m_iSelect -= 1;

}

void CBackObj::MoveDownPush()
{
	if (m_iSelect < 4)
		m_iSelect += 1;

}

void CBackObj::EnterPush()
{
	if (m_iSelect == 0)
	{
		ChangeAnimation("TitleAnimation_Change");
		m_Scene->GetSceneResource()->SoundPlay("sound_menubeep_2");
		SetEndFunction<CBackObj>("TitleAnimation_Change", this, &CBackObj::SceneChange);
	}

}

void CBackObj::SceneChange()
{
	if (m_iSelect == 0)
	{
		CInput::GetInst()->ClearCallback();
		CSceneManager::GetInst()->CreateScene<CBackObj>();
	}
}
