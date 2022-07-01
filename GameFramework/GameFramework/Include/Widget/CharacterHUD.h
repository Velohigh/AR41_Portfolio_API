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
    CSharedPtr<class CImageWidget>  m_HudFrame;
    CSharedPtr<class CProgressBar>  m_BatteryBar;
    CSharedPtr<class CProgressBar>  m_TimeBar;

    CSharedPtr<class CText>     m_FPSText;

public:
    void SetBatteryBar(float Battery);
    void SetTimeBar(float Time);

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
};

