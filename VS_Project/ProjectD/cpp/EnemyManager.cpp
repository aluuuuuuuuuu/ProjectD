#include "EnemyManager.h"
#include "EnemyBase.h"

void EnemyManager::Update()
{
	// �G�l�~�[�̍X�V����
	for (std::shared_ptr<EnemyBase> enemy : m_pEnemy) {
		enemy->Update();
	}
}

void EnemyManager::Draw() const
{
	// �G�l�~�[�̕`�揈��
	for (std::shared_ptr<EnemyBase> enemy : m_pEnemy) {
		enemy->Draw();
	}
}

std::list<std::shared_ptr<EnemyBase>> EnemyManager::GetEnemy()
{
	return m_pEnemy;
}

