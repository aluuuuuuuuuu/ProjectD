#include "EnemyManager.h"
#include "EnemyBase.h"
#include "DxLib.h"
#include "EnemyTest.h"

void EnemyManager::Init()
{
	m_modelHandle = MV1LoadModel("data/model/enemy2.mv1");
}

void EnemyManager::Update()
{
	// エネミーの更新処理
	for (std::shared_ptr<EnemyBase> enemy : m_pEnemy) {
		enemy->Update();
	}
}

void EnemyManager::Draw() const
{
	// エネミーの描画処理
	for (std::shared_ptr<EnemyBase> enemy : m_pEnemy) {
		enemy->Draw();
	}
}

std::list<std::shared_ptr<EnemyBase>> EnemyManager::GetEnemy()
{
	return m_pEnemy;
}

void EnemyManager::AddEnemy(Vec3 pos)
{
	m_pEnemy.push_back(std::make_shared<EnemyTest>(pos, MV1DuplicateModel(m_modelHandle)));
}

