#include "StaticObjectManager.h"
#include "StaticObjectBase.h"
#include "ObjectWall.h"
#include "DxLib.h"

StaticObjectManager::StaticObjectManager()
{
	m_wallHandle = MV1LoadModel("data/model/object/Wall.mv1");
}

StaticObjectManager::~StaticObjectManager()
{
}

// �e�X�g�X�e�[�W�ł̃I�u�W�F�N�g�̐���
void StaticObjectManager::InitTest()
{
	m_pStaticObject.push_back(std::make_shared<ObjectWall>(m_wallHandle));
}

void StaticObjectManager::InitStage1()
{
}

void StaticObjectManager::Draw(Vec3 plPos) const
{
	// �I�u�W�F�N�g�̕`��	
	for (std::shared_ptr<StaticObjectBase> obj : m_pStaticObject) {
		obj->Draw();
	}
}
