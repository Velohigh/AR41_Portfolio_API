#pragma once

#include "../GameInfo.h"
#include "../SingletonMacro.h"

class CCollisionManager
{
private:
	std::unordered_map<std::string, CollisionProfile*>	m_mapProfile;

public:
	bool Init();

	bool CreateProfile(const std::string& Name, ECollision_Channel Channel, bool Enable,
		ECollision_Interaction BaseInteraction = ECollision_Interaction::Collision);
	bool SetCollisionInteraction(const std::string& Name, ECollision_Channel Channel,
		ECollision_Interaction Interaction);
	
	CollisionProfile* FindProfile(const std::string Name);
	
	DECLARE_SINGLE(CCollisionManager)
};

