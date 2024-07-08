#include "SceneTest.h"
#include "DxLib.h"
#include "StaticFunction.h"
#include "Player.h"
#include "Camera.h"
#include "Singleton.h"
#include "EnemyManager.h"
#include "EnemyTest.h"
#include "UI.h"

SceneTest::SceneTest()
{
	m_pPlayer = make_shared<Player>();
	Camera::getInstance().Init(m_pPlayer->GetPos());

	// �G�l�~�[��ǉ�����
	EnemyManager::getInstance().AddEnemy<EnemyTest>(Vec3{ 60,0,60 });
	EnemyManager::getInstance().AddEnemy<EnemyTest>(Vec3{ 60,0,30 });
}

SceneTest::~SceneTest()
{
}

void SceneTest::Update()
{
	// �G�l�~�[�̍X�V
	EnemyManager::getInstance().Update();

	// �v���C���[�̍X�V
	m_pPlayer->Update();

	// �J�����̍X�V
	Camera::getInstance().Update(m_pPlayer->GetPos());

	// UI�̍X�V
	UI::getInstance().Update();
}

void SceneTest::Draw() const
{
	DrawGrid();

	// �G�l�~�[�̕`��
	EnemyManager::getInstance().Draw();

	// �v���C���[�̕`��
	m_pPlayer->Draw();

	// UI�̕`��
	UI::getInstance().Draw();
}

void SceneTest::DrawGrid() const
{
	for (int x = -100; x <= 100; x += 10)
	{
		DrawLine3D(VGet(static_cast<float>(x), 0, -100), VGet(static_cast<float>(x), 0, 100), 0xffff00);
	}
	for (int z = -100; z <= 100; z += 10)
	{
		DrawLine3D(VGet(-100, 0, static_cast<float>(z)), VGet(100, 0, static_cast<float>(z)), 0xff0000);
	}

	// X+-,Z+-�̕�����������₷���悤�ɕ\����ǉ�����
	VECTOR dispPos = ConvWorldPosToScreenPos(VGet(50, 0, 0));
	if (dispPos.z >= 0.0f && dispPos.z <= 1.0f)
	{
		DrawStringF(dispPos.x, dispPos.y, "X+", 0xffffff);
	}

	dispPos = ConvWorldPosToScreenPos(VGet(-50, 0, 0));
	if (dispPos.z >= 0.0f && dispPos.z <= 1.0f)
	{
		DrawStringF(dispPos.x, dispPos.y, "X-", 0xffffff);
	}

	dispPos = ConvWorldPosToScreenPos(VGet(0, 0, 50));
	if (dispPos.z >= 0.0f && dispPos.z <= 1.0f)
	{
		DrawStringF(dispPos.x, dispPos.y, "Z+", 0xffffff);
	}

	dispPos = ConvWorldPosToScreenPos(VGet(0, 0, -50));
	if (dispPos.z >= 0.0f && dispPos.z <= 1.0f)
	{
		DrawStringF(dispPos.x, dispPos.y, "Z-", 0xffffff);
	}
}
