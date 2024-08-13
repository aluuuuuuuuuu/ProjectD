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
	void Init();
	void Update();
	void Draw() const;

	std::list<std::shared_ptr<EnemyBase>> GetEnemy();

	// �w�肳�ꂽ��ނ̓G��z��ɒǉ�����
	void AddEnemy(Vec3 pos);
private:
	// �v���C�x�[�g�R���X�g���N�^
	EnemyManager() {};

	// �G�l�~�[���i�[���郊�X�g�z��
	std::list<std::shared_ptr<EnemyBase>> m_pEnemy;

	// �G�l�~�[�̃��f���n���h��
	int m_modelHandle;
};
