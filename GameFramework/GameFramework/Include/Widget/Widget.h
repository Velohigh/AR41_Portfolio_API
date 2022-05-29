#pragma once

#include "../Ref.h"

// UI를 만들기 위한 일종의 부품 클래스

class CWidget :
    public CRef
{
    friend class CWidgetWindow;

protected:
    CWidget();
    CWidget(const CWidget& widget);
    virtual ~CWidget();

protected:
    class CScene* m_Scene;  // 자신이 속한 씬
    class CWidgetWindow* m_Owner;   // 이 Widget을 가지고 있는 WidgetWindow
    int     m_ZOrder;       // Widget 끼리 출력순서
    bool    m_Visibility;   // 보여지는지 여부
    Vector2 m_Pos;
    Vector2 m_Size;
    bool    m_MouseHovered; // 마우스가 해당 Widget에 올라왔는지 여부

public:
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
    virtual void Render(HDC hDC, const Vector2& Pos, float DeltaTime);

public:
    // UI와 마우스가 충돌하였는지
    bool CollisionMouse(const Vector2& Pos);

public:
    // 마우스가 충돌, 떨어질때 콜할 함수
    virtual void CollisionMouseHoveredCallback(const Vector2& Pos);
    virtual void CollisionMouseReleaseCallback();



};

