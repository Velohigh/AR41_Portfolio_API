#pragma once

#include "../GameInfo.h"

class CSceneCollision
{
	friend class CScene;

private:
	CSceneCollision();
	~CSceneCollision();

private:
	std::vector<class CCollider*>	m_vecCollider;
	class CCollider* m_MouseCollision;

public:
	void AddCollider(class CCollider* Collider);
	void CollisionMouse(float DeltaTime);
	void Collision(float DeltaTime);
	
private:
	static bool SortY(class CCollider* Src, class CCollider* Dest);

};

