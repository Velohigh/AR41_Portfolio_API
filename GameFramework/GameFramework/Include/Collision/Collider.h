#pragma once

#include "../Ref.h"

class CCollider :
    public CRef
{
    friend class CGameObject;   // 충돌체는 오브젝트에 달아줄것이다.

protected:
    CCollider();
    CCollider(const CCollider& collider);
    virtual ~CCollider() = 0;

protected:
    class CScene*       m_Scene;        // 충돌체가 속하는 씬
    class CGameObject*  m_Owner;        // 충돌체를 가진 오브젝트
    ECollider_Type      m_ColliderType; // 사각형 충돌체냐, 원형 충돌체냐
    Vector2             m_Offset;       // Owner로부터 얼마만큼 떨어져 있을지.
    CollisionProfile*   m_Profile;      // 이 충돌체가 어떤 프로파일을 쓰는지
    Vector2             m_HitPoint;
    // 함수 포인터에서  CCollider* 2개를 받는 이유는 서로 충돌된 두 물체를 인자로 넘겨주기 위해서이다.
    std::function<void(CCollider*, CCollider*)> m_CollisionBegin;
    std::function<void(CCollider*, CCollider*)> m_CollisionEnd;
    
    /*
    현재 프레임에 두 물체가 충돌되고 다음 프레임에도 두 물체가 충돌이 되었다면 계속 충돌이 되고 있는 상태로
    판단해야 한다.
    그런데 이런 파단을 하기 위해서는 이전 프레임에서 두 물체가 충돌이 되었는지에 대한 정보가 필요할 것이다.
    그러므로 충돌체는 이전 프레임에 충돌되었던 충돌체를 담아둘 필요가 있다.
    */
    std::list<CSharedPtr<CCollider>>    m_CollisionList;


public:
    void SetOffset(const Vector2& Offset)
    {
        m_Offset = Offset;
    }

    void SetOffset(float x, float y)
    {
        m_Offset = Vector2(x, y);
    }

public:
    class CGameObject* GetOwner() const
    {
        return m_Owner;
    }

    class CScene* GetScene() const
    {
        return m_Scene;
    }

    ECollider_Type GetColliderType() const
    {
        return m_ColliderType;
    }

    const CollisionProfile* GetProfile() const
    {
        return m_Profile;
    }

public:
    void SetCollisionProfile(const std::string& Name);
    void AddCollisionList(CCollider* Collider);
    bool CheckCollisionList(CCollider* Collider);
    void DeleteCollisionList(CCollider* Collider);
    void ClearCollisionList();
    void CallCollisionBegin(CCollider* Dest);
    void CallCollisionEnd(CCollider* Dest);

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render(HDC hDC, float DeltaTime);
    virtual bool Collision(CCollider* Dest);

public:
    // 함수포인터에 충돌시작시 발동할 함수주소 지정
    template <typename T>
    void SetCollisionBeginFunction(T* Obj, void(T::* Func)(CCollider*, CCollider*))
    {
        m_CollisionBegin = std::bind(Func, Obj, std::placeholders::_1, std::placeholders::_2);
    }

    // 함수포인터에 충돌종료시 발동할 함수주소 지정
    template <typename T>
    void SetCollisionEndFunction(T* Obj, void(T::* Func)(CCollider*, CCollider*))
    {
        m_CollisionEnd = std::bind(Func, Obj, std::placeholders::_1, std::placeholders::_2);
    }
};

