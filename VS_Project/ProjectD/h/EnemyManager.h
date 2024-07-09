#pragma once
#include <memory>
#include <list>
#include "Singleton.h"
#include "Vec3.h"

class EnemyBase;
// �G�l�~�[�S�̂��Ǘ�����V���O���g���N���X
class EnemyManager : public Singleton<EnemyManager>
{
	friend class Singleton<EnemyManager>;

public:

	void Update();
	void Draw() const;

	std::list<std::shared_ptr<EnemyBase>> GetEnemy();

	// �w�肳�ꂽ��ނ̓G��z��ɒǉ�����
	template<typename T>
	void AddEnemy(Vec3 pos) { m_pEnemy.push_back(std::make_shared<T>(pos)); };
private:
	// �v���C�x�[�g�R���X�g���N�^
	EnemyManager() {};

	// �G�l�~�[���i�[���郊�X�g�z��
	std::list<std::shared_ptr<EnemyBase>> m_pEnemy;
};
