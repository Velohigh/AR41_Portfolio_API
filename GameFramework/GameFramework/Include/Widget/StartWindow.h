#pragma once
#include "WidgetWindow.h"
class CStartWindow :
    public CWidgetWindow
{
    friend class CScene;

protected:
    CStartWindow();
    virtual ~CStartWindow();

public:
    virtual bool Init();

public:
    void StartButtonCallBack();
    void EndButtonCallBack();

};

