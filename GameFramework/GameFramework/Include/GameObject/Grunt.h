#pragma once

#include "Character.h"

class CGrunt :
    public CCharacter
{
    friend class CScene;

protected:
    CGrunt();
    CGrunt(const CGrunt& Obj);
    virtual ~CGrunt();

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render(HDC hDC, float DeltaTime);
    virtual float InflictDamage(float Damage);

private:
    void CollisionBegin(CCollider* Src, CCollider* Dest);
    void CollisionEnd(CCollider* Src, CCollider* Dest);



};

