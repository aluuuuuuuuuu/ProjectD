#include "StaticObjectManager.h"
#include "StaticObjectBase.h"
#include "ObjectFloor.h"
#include "ObjectWall.h"
#include "DxLib.h"

StaticObjectManager::StaticObjectManager()
{
	m_wallHandle = MV1LoadModel("data/model/object/Wall.mv1");
	m_floorHandle = MV1LoadModel("data/model/object/Floor.mv1");
}

StaticObjectManager::~StaticObjectManager()
{
}

// テストステージでのオブジェクトの生成
void StaticObjectManager::InitTest()
{
	m_pStaticObject.push_back(std::make_shared<ObjectWall>(m_wallHandle, Vec3{ 20.0f,0.0f,30.0f },false));

	m_pStaticObject.push_back(std::make_shared<ObjectWall>(m_wallHandle, Vec3{ 30.0f,0.0f,0.0f },true));

	m_pStaticObject.push_back(std::make_shared <ObjectFloor>(m_floorHandle, Vec3{ 0.0f,-2.0f,0.0f }));
}

void StaticObjectManager::InitStage1()
{
}

void StaticObjectManager::Draw(Vec3 plPos) const
{
	// オブジェクトの描画	
	for (std::shared_ptr<StaticObjectBase> obj : m_pStaticObject) {
		obj->Draw();
	}
}
