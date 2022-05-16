#pragma once

#include "../GameInfo.h"

// 실제로 애니메이션을 동작시켜줄 클래스
class CAnimation
{
	friend class CGameObject;

private:
	CAnimation();
	~CAnimation();

private:
	class CGameObject* m_Owner;
	class CScene* m_Scene;
	std::unordered_map<std::string, class CAnimationInfo*> m_mapAnimation;
	class CAnimationInfo* m_CurrentAnimation; // 현재 동작중인 애니메이션 주소

};

