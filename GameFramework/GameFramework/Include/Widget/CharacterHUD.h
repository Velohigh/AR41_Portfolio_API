#pragma once
#include "WidgetWindow.h"
class CCharacterHUD :
    public CWidgetWindow
{
    friend class CScene;

protected:
    CCharacterHUD();
    virtual ~CCharacterHUD();

protected:
    CSharedPtr<class CProgressBar>  m_HPBar;
    CSharedPtr<class CImageWidget>  m_HPBarFrame;

public:
    void SetHP(float HP);

public:
    virtual bool Init();
};

