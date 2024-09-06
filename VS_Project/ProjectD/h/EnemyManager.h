#pragma once
#include <memory>
#include <list>
#include "Vec3.h"

class StaticObjectManager;
class Player;
class EnemyBase;
// �G�l�~�[�S�̂��Ǘ�����V���O���g���N���X
class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();

	void Update();
	void Draw() const;

	std::list<std::shared_ptr<EnemyBase>>& GetEnemy();

	// �w�肳�ꂽ��ނ̓G��z��ɒǉ�����
	void AddEnemy(Vec3 pos,std::shared_ptr<Player>& pl,std::shared_ptr<StaticObjectManager>& obj);
private:

	// �G�l�~�[���i�[���郊�X�g�z��
	std::list<std::shared_ptr<EnemyBase>> m_pEnemy;

	// �G�l�~�[�̃��f���n���h��
	int m_modelHandle;
};
