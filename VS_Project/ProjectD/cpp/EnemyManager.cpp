#include "EnemyManager.h"
#include "EnemyBase.h"

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

