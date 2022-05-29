#pragma once

#include "../Ref.h"

// UI�� ����� ���� ������ ��ǰ Ŭ����

class CWidget :
    public CRef
{
    friend class CWidgetWindow;

protected:
    CWidget();
    CWidget(const CWidget& widget);
    virtual ~CWidget();

protected:
    class CScene* m_Scene;  // �ڽ��� ���� ��
    class CWidgetWindow* m_Owner;   // �� Widget�� ������ �ִ� WidgetWindow
    int     m_ZOrder;       // Widget ���� ��¼���
    bool    m_Visibility;   // ���������� ����
    Vector2 m_Pos;
    Vector2 m_Size;
    bool    m_MouseHovered; // ���콺�� �ش� Widget�� �ö�Դ��� ����

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
    // UI�� ���콺�� �浹�Ͽ�����
    bool CollisionMouse(const Vector2& Pos);

public:
    // ���콺�� �浹, �������� ���� �Լ�
    virtual void CollisionMouseHoveredCallback(const Vector2& Pos);
    virtual void CollisionMouseReleaseCallback();



};

