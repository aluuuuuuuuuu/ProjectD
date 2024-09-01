#include "MapCollisionManager.h"
#include "StaticObjectManager.h"
#include "StaticObjectBase.h"

MapCollisionManager::MapCollisionManager(CapsuleData& cap, StaticObjectManager& manager):
	m_playerCapsule(cap),
	m_staticObjectManager(manager)
{
}

MapCollisionManager::~MapCollisionManager()
{

}
