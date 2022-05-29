#pragma once

#include "../Ref.h"
#include "Widget.h"

class CWidgetWindow :
    public CRef
{
    friend class CScene;

protected:
    CWidgetWindow();
    virtual ~CWidgetWindow();

protected:
    class CScene* m_Scene;
    int         m_ZOrder;
    std::vector<CSharedPtr<class CWidget>>  m_vecWidget;

    bool        m_Visibility;
    Vector2     m_Pos;
    Vector2     m_Size;

public:
    class CWidget* GetWidget(int Index)
    {
        return m_vecWidget[Index];
    }

    int GetWidgetCount() const
    {
        return m_vecWidget.size();
    }

    const Vector2& GetPos() const
    {
        return m_Pos;
    }

    const Vector2& GetSize() const
    {
        return m_Size;
    }

    bool GetVisibility() const
    {
        return m_Visibility;
    }

    int GetZOrder() const
    {
        return m_ZOrder;
    }

public:
    void SetPos(float x, float y)
    {
        m_Pos.x = x;
        m_Pos.y = y;
    }

    void SetPos(const Vector2& Pos)
    {
        m_Pos = Pos;
    }

    void SetSize(float x, float y)
    {
        m_Size.x = x;
        m_Size.y = y;
    }

    void SetSize(const Vector2& Size)
    {
        m_Size = Size;
    }

    void SetVisibility(bool Visible)
    {
        m_Visibility = Visible;
    }

    void SetZOrder(int ZOrder)
    {
        m_ZOrder = ZOrder;
    }

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render(HDC hDC, float DeltaTime);

public:
    template <typename T>
    T* FindWidget(const std::string& Name)
    {
        size_t Size = m_vecWidget.size();

        for (size_t i = 0; i < Size; ++i)
        {
            if (m_vecWidget[i]->GetName() == Name)
				return (T*)m_vecWidget[i];
        }

        return nullptr;
    }

    template <typename T>
    T* CreateWidget(const std::string& Name)
    {
        T* Widget = new T;

        Widget->SetName(Name);
        Widget->m_Scene = m_Scene;
        Widget->m_Owner = this;

        if (!Widget->Init())
        {
            SAFE_DELETE(Widget);
            return nullptr;
        }

        m_vecWidget.push_back(Widget);
        return (T*)Widget;
    }

};

