#pragma once
#include "Components.h"
#include <vector>
#include <memory>

class StaticObjectManager;
class MapCollisionManager
{
public:
	MapCollisionManager(CapsuleData& cap,StaticObjectManager& manager);
	virtual ~MapCollisionManager();

private:
	CapsuleData& m_playerCapsule;
	StaticObjectManager& m_staticObjectManager;
};

