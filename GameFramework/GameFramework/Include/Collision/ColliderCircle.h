#pragma once

#include "Collider.h"

class CColliderCircle :
    public CCollider
{
    friend class CGameObject;   // 충돌체는 오브젝트에 달아줄것이다.

protected:
    CColliderCircle();
    CColliderCircle(const CColliderCircle& collider);
    virtual ~CColliderCircle();

protected:
    CircleInfo m_Info;


public:
    CircleInfo GetInfo() const
    {
        return m_Info;
    }

    void SetRadius(float Radius)
    {
        m_Info.Radius = Radius;
    }

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render(HDC hDC, float DeltaTime);
    virtual bool Collision(CCollider* Dest);

};

