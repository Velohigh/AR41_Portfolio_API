
#include "WidgetComponent.h"
#include "Widget.h"
#include "../Resource/Texture/Texture.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Scene/Camera.h"
#include "WidgetWindow.h"
#include "../GameObject/GameObject.h"

CWidgetComponent::CWidgetComponent()
{
}

CWidgetComponent::CWidgetComponent(const CWidgetComponent& widget)
{
}

CWidgetComponent::~CWidgetComponent()
{
}

void CWidgetComponent::SetWidget(CWidget* Widget)
{
	m_Widget = Widget;
}

bool CWidgetComponent::Init()
{
	return true;
}

void CWidgetComponent::Update(float DeltaTime)
{
	if (m_Widget)
		m_Widget->Update(DeltaTime);
}

void CWidgetComponent::PostUpdate(float DeltaTime)
{
	if (m_Widget)
		m_Widget->PostUpdate(DeltaTime);
}

void CWidgetComponent::Render(HDC hDC, float DeltaTime)
{
	if (m_Widget)
	{
		Vector2	Pos = m_Pos + m_Owner->GetPos() - m_Scene->GetCamera()->GetPos();

		m_Widget->Render(hDC, Pos, DeltaTime);
	}
}
