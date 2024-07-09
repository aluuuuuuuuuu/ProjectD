#include "StaticObjectManager.h"
#include "DxLib.h"
#include "StaticObject.h"

void StaticObjectManager::Init()
{
	// 教会
	{
		model = MV1LoadModel("data/model/Spawn.mv1");
		texture = LoadGraph("data/image/halloweenbits_texture.png");

		m_pObject.push_back(std::make_shared<StaticObject>(Vec3{ 0.0f,-3.0f,175.0f }, Vec3{ 0.07f,0.07f,0.07f }, 0.0f, MV1DuplicateModel(model), texture));
		m_pObject.push_back(std::make_shared<StaticObject>(Vec3{ 0.0f,-3.0f,-175.0f }, Vec3{ 0.07f,0.07f,0.07f }, 3.14159f, MV1DuplicateModel(model), texture));
		m_pObject.push_back(std::make_shared<StaticObject>(Vec3{ 175.0f,-3.0f,0.0f }, Vec3{ 0.07f,0.07f,0.07f }, 1.5708f, MV1DuplicateModel(model), texture));
		m_pObject.push_back(std::make_shared<StaticObject>(Vec3{ -175.0f,-3.0f,0.0f }, Vec3{ 0.07f,0.07f,0.07f }, -1.5708f, MV1DuplicateModel(model), texture));
	}


	// フェンス
	{
		model = MV1LoadModel("data/model/Fence.mv1");

		float num = 35.0f;
		for (int i = 0; i < 4; i++) {
			m_pObject.push_back(std::make_shared<StaticObject>(Vec3{ num,0.0f,150.0f }, Vec3{ 10.0f,10.0f,10.0f }, 0.0f, MV1DuplicateModel(model), texture));
			num += 40;
		}

		num = 35;
		for (int i = 0; i < 4; i++) {
			m_pObject.push_back(std::make_shared<StaticObject>(Vec3{ num,0.0f,-150.0f }, Vec3{ 10.0f,10.0f,10.0f }, 0.0f, MV1DuplicateModel(model), texture));
			num += 40;
		}

		num = 35;
		for (int i = 0; i < 4; i++) {
			m_pObject.push_back(std::make_shared<StaticObject>(Vec3{ 150.0f,0.0f,num }, Vec3{ 10.0f,10.0f,10.0f }, 1.5708f, MV1DuplicateModel(model), texture));
			num += 40;
		}

		num = 35;
		for (int i = 0; i < 4; i++) {
			m_pObject.push_back(std::make_shared<StaticObject>(Vec3{ -150.0f,0.0f,num }, Vec3{ 10.0f,10.0f,10.0f }, 1.5708f, MV1DuplicateModel(model), texture));
			num += 40;
		}

		num = -35;
		for (int i = 0; i < 4; i++) {
			m_pObject.push_back(std::make_shared<StaticObject>(Vec3{ num,0.0f,150.0f }, Vec3{ 10.0f,10.0f,10.0f }, 0.0f, MV1DuplicateModel(model), texture));
			num -= 40;
		}

		num = -35;
		for (int i = 0; i < 4; i++) {
			m_pObject.push_back(std::make_shared<StaticObject>(Vec3{ num,0.0f,-150.0f }, Vec3{ 10.0f,10.0f,10.0f }, 0.0f, MV1DuplicateModel(model), texture));
			num -= 40;
		}

		num = -35;
		for (int i = 0; i < 4; i++) {
			m_pObject.push_back(std::make_shared<StaticObject>(Vec3{ 150.0f,0.0f,num }, Vec3{ 10.0f,10.0f,10.0f }, 1.5708f, MV1DuplicateModel(model), texture));
			num -= 40;
		}

		num = -35;
		for (int i = 0; i < 4; i++) {
			m_pObject.push_back(std::make_shared<StaticObject>(Vec3{ -150.0f,0.0f,num }, Vec3{ 10.0f,10.0f,10.0f }, 1.5708f, MV1DuplicateModel(model), texture));
			num -= 40;
		}
	}

	// 周囲の木々
	{
		// 黄色木大
		{
			model = MV1LoadModel("data/model/Tree_Yellow_Big.mv1");
			m_pObject.push_back(std::make_shared<StaticObject>(Vec3{ 180.0f,0.0f,60.0f }, Vec3{ 0.1f,0.1f,0.1f }, 0.0f, MV1DuplicateModel(model), texture));
			m_pObject.push_back(std::make_shared<StaticObject>(Vec3{ 180.0f,0.0f,150.0f }, Vec3{ 0.1f,0.1f,0.1f }, 0.0f, MV1DuplicateModel(model), texture));
			m_pObject.push_back(std::make_shared<StaticObject>(Vec3{ 170.0f,0.0f,-70.0f }, Vec3{ 0.1f,0.1f,0.1f }, 0.0f, MV1DuplicateModel(model), texture));
			m_pObject.push_back(std::make_shared<StaticObject>(Vec3{ 175.0f,0.0f,-170.0f }, Vec3{ 0.1f,0.1f,0.1f }, 0.0f, MV1DuplicateModel(model), texture));
			m_pObject.push_back(std::make_shared<StaticObject>(Vec3{ 180.0f,0.0f,-100.0f }, Vec3{ 0.1f,0.1f,0.1f }, 0.0f, MV1DuplicateModel(model), texture));

			m_pObject.push_back(std::make_shared<StaticObject>(Vec3{ -180.0f,0.0f,60.0f }, Vec3{ 0.1f,0.1f,0.1f }, 0.0f, MV1DuplicateModel(model), texture));
			m_pObject.push_back(std::make_shared<StaticObject>(Vec3{ -180.0f,0.0f,150.0f }, Vec3{ 0.1f,0.1f,0.1f }, 0.0f, MV1DuplicateModel(model), texture));
			m_pObject.push_back(std::make_shared<StaticObject>(Vec3{ -170.0f,0.0f,-70.0f }, Vec3{ 0.1f,0.1f,0.1f }, 0.0f, MV1DuplicateModel(model), texture));
			m_pObject.push_back(std::make_shared<StaticObject>(Vec3{ -180.0f,0.0f,-100.0f }, Vec3{ 0.1f,0.1f,0.1f }, 0.0f, MV1DuplicateModel(model), texture));

			m_pObject.push_back(std::make_shared<StaticObject>(Vec3{ 86.0f,0.0f,-180.0f }, Vec3{ 0.1f,0.1f,0.1f }, 0.0f, MV1DuplicateModel(model), texture));
			m_pObject.push_back(std::make_shared<StaticObject>(Vec3{ 58.0f,0.0f,-175.0f }, Vec3{ 0.1f,0.1f,0.1f }, 0.0f, MV1DuplicateModel(model), texture));
			m_pObject.push_back(std::make_shared<StaticObject>(Vec3{ -80.0f,0.0f,-180.0f }, Vec3{ 0.1f,0.1f,0.1f }, 0.0f, MV1DuplicateModel(model), texture));
			m_pObject.push_back(std::make_shared<StaticObject>(Vec3{ -173.0f,0.0f,-185.0f }, Vec3{ 0.1f,0.1f,0.1f }, 0.0f, MV1DuplicateModel(model), texture));

			m_pObject.push_back(std::make_shared<StaticObject>(Vec3{ 32.0f,0.0f,180.0f }, Vec3{ 0.1f,0.1f,0.1f }, 0.0f, MV1DuplicateModel(model), texture));
			m_pObject.push_back(std::make_shared<StaticObject>(Vec3{ 84.0f,0.0f,175.0f }, Vec3{ 0.1f,0.1f,0.1f }, 0.0f, MV1DuplicateModel(model), texture));
			m_pObject.push_back(std::make_shared<StaticObject>(Vec3{ -75.0f,0.0f,170.0f }, Vec3{ 0.1f,0.1f,0.1f }, 0.0f, MV1DuplicateModel(model), texture));
			m_pObject.push_back(std::make_shared<StaticObject>(Vec3{ -137.0f,0.0f,185.0f }, Vec3{ 0.1f,0.1f,0.1f }, 0.0f, MV1DuplicateModel(model), texture));

		}

		// 赤色木々
		{
			model = MV1LoadModel("data/model/Tree_Orange_Small.mv1");
			m_pObject.push_back(std::make_shared<StaticObject>(Vec3{ 180.0f,0.0f,88.0f }, Vec3{ 0.1f,0.1f,0.1f }, 0.0f, MV1DuplicateModel(model), texture));
			m_pObject.push_back(std::make_shared<StaticObject>(Vec3{ 108.0f,0.0f,180.0f }, Vec3{ 0.1f,0.1f,0.1f }, 0.0f, MV1DuplicateModel(model), texture));
			m_pObject.push_back(std::make_shared<StaticObject>(Vec3{ -170.0f,0.0f,122.0f }, Vec3{ 0.1f,0.1f,0.1f }, 0.0f, MV1DuplicateModel(model), texture));
			m_pObject.push_back(std::make_shared<StaticObject>(Vec3{ -175.0f,0.0f,102.0f }, Vec3{ 0.1f,0.1f,0.1f }, 0.0f, MV1DuplicateModel(model), texture));
			m_pObject.push_back(std::make_shared<StaticObject>(Vec3{ -43.0f,0.0f,-176.0f }, Vec3{ 0.1f,0.1f,0.1f }, 0.0f, MV1DuplicateModel(model), texture));
		}
	}

	// 壁となる岩々
	{
		model = MV1LoadModel("data/model/Rock.mv1");
		m_pObject.push_back(std::make_shared<StaticObject>(Vec3{ 270.0f,-30.0f,0.0f }, Vec3{ 1.0f,1.0f,0.5f }, 1.5708f, MV1DuplicateModel(model), texture));
		m_pObject.push_back(std::make_shared<StaticObject>(Vec3{ 270.0f,-30.0f,150.0f }, Vec3{ 1.0f,1.0f,0.5f }, 1.5708f, MV1DuplicateModel(model), texture));
		m_pObject.push_back(std::make_shared<StaticObject>(Vec3{ 270.0f,-30.0f,-150.0f }, Vec3{ 1.0f,1.0f,0.5f }, 1.5708f, MV1DuplicateModel(model), texture));

		m_pObject.push_back(std::make_shared<StaticObject>(Vec3{ -270.0f,-30.0f,0.0f }, Vec3{ 1.0f,1.0f,0.5f }, 1.5708f, MV1DuplicateModel(model), texture));
		m_pObject.push_back(std::make_shared<StaticObject>(Vec3{ -270.0f,-30.0f,150.0f }, Vec3{ 1.0f,1.0f,0.5f }, 1.5708f, MV1DuplicateModel(model), texture));
		m_pObject.push_back(std::make_shared<StaticObject>(Vec3{ -270.0f,-30.0f,-150.0f }, Vec3{ 1.0f,1.0f,0.5f }, 1.5708f, MV1DuplicateModel(model), texture));

		m_pObject.push_back(std::make_shared<StaticObject>(Vec3{ 0.0f,-30.0f,-270.0f }, Vec3{ 1.0f,1.0f,0.5f }, 0.0f, MV1DuplicateModel(model), texture));
		m_pObject.push_back(std::make_shared<StaticObject>(Vec3{ 150.0f,-30.0f,-270.0f }, Vec3{ 1.0f,1.0f,0.5f }, 0.0f, MV1DuplicateModel(model), texture));
		m_pObject.push_back(std::make_shared<StaticObject>(Vec3{ -150.0f,-30.0f,-270.0f }, Vec3{ 1.0f,1.0f,0.5f }, 0.0f, MV1DuplicateModel(model), texture));

		m_pObject.push_back(std::make_shared<StaticObject>(Vec3{ 0.0f,-30.0f,270.0f }, Vec3{ 1.0f,1.0f,0.5f }, 0.0f, MV1DuplicateModel(model), texture));
		m_pObject.push_back(std::make_shared<StaticObject>(Vec3{ 150.0f,-30.0f,270.0f }, Vec3{ 1.0f,1.0f,0.5f }, 0.0f, MV1DuplicateModel(model), texture));
		m_pObject.push_back(std::make_shared<StaticObject>(Vec3{ -150.0f,-30.0f,270.0f }, Vec3{ 1.0f,1.0f,0.5f }, 0.0f, MV1DuplicateModel(model), texture));

		m_pObject.push_back(std::make_shared<StaticObject>(Vec3{ 270.0f,-30.0f,270.0f }, Vec3{ 1.0f,1.0f,0.5f }, 0.785398f, MV1DuplicateModel(model), texture));
		m_pObject.push_back(std::make_shared<StaticObject>(Vec3{ -270.0f,-30.0f,270.0f }, Vec3{ 1.0f,1.0f,0.5f }, 2.35619, MV1DuplicateModel(model), texture));
		m_pObject.push_back(std::make_shared<StaticObject>(Vec3{ 270.0f,-30.0f,-270.0f }, Vec3{ 1.0f,1.0f,0.5f }, 2.35619, MV1DuplicateModel(model), texture));
		m_pObject.push_back(std::make_shared<StaticObject>(Vec3{ -270.0f,-30.0f,-270.0f }, Vec3{ 1.0f,1.0f,0.5f }, 0.785398f, MV1DuplicateModel(model), texture));
	}
}

void StaticObjectManager::Update()
{
	for (std::shared_ptr<StaticObject> object : m_pObject) {
		object->Update();
	}
}

void StaticObjectManager::Draw() const
{
	for (std::shared_ptr<StaticObject> object : m_pObject) {
		object->Draw();
	}
}
