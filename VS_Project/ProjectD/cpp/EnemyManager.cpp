#include "EnemyManager.h"
#include "EnemyBase.h"
#include "DxLib.h"
#include "EnemyTest.h"

EnemyManager::EnemyManager():
	m_modelHandle(0)
{
	m_modelHandle = MV1LoadModel("data/model/enemy2.mv1");
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::Update()
{
	// �G�l�~�[�̍X�V����
	for (auto enemy : m_pEnemy) {
		enemy->Update();
	}

	// �G�l�~�[�����S���Ă�����폜����
	for (auto it = m_pEnemy.begin(); it != m_pEnemy.end();) {
		if ((*it)->GetDeadFlag()) {
			it = m_pEnemy.erase(it);	//�v�f���폜�����̗v�f���w���C�e���[�^���擾
		}
		else {
			it++;
		}
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

void EnemyManager::AddEnemy(Vec3 pos)
{
	m_pEnemy.push_back(std::make_shared<EnemyTest>(pos, MV1DuplicateModel(m_modelHandle)));
}

