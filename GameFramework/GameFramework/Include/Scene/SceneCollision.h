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

public:
	void AddCollider(class CCollider* Collider);
	void Collision(float DeltaTime);

};

