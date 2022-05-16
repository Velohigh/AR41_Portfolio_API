#pragma once

#include "../GameInfo.h"

// ������ �ִϸ��̼��� ���۽����� Ŭ����
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
	class CAnimationInfo* m_CurrentAnimation; // ���� �������� �ִϸ��̼� �ּ�

};

