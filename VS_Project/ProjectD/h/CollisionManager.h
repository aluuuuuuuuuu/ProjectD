#pragma once
#include "Components.h"
#include <vector>
#include <memory>

class CollisionManager
{
public:
	CollisionManager(CapsuleData& cap);
	virtual ~CollisionManager();

private:
	CapsuleData& m_playerCapsule;

};

