
#include "WidgetWindow.h"

CWidgetWindow::CWidgetWindow()	:
	m_Visibility(true),
	m_Scene(nullptr),
	m_ZOrder(0)
{
}

CWidgetWindow::~CWidgetWindow()
{
}

bool CWidgetWindow::Init()
{
	return true;
}

void CWidgetWindow::Update(float DeltaTime)
{
	size_t Size = m_vecWidget.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecWidget[i]->Update(DeltaTime);
	}
}

void CWidgetWindow::PostUpdate(float DeltaTime)
{
	size_t Size = m_vecWidget.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecWidget[i]->PostUpdate(DeltaTime);
	}
}

void CWidgetWindow::Render(HDC hDC, float DeltaTime)
{
	size_t Size = m_vecWidget.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecWidget[i]->Render(hDC, DeltaTime);
	}
}
