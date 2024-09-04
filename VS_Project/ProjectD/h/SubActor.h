#pragma once
#include "CharactorBase.h"
#include <memory>

class EnemyBase;
class SubActor :
	public CharactorBase
{
public:
	SubActor(std::list<std::shared_ptr<EnemyBase>> enemy);
	virtual ~SubActor();

	void Update();
	void Draw() const;

	// �C���^���N�g����G�̃|�C���^��Ԃ�
	std::shared_ptr<EnemyBase> GetEnemyPtr();

	// �����ύX�����Ƃ��̏�������
	void ChangeInit(Vec3 cameraPos, Vec3 mainActorPos);

	void Control(Vec3 cameraRot);
private:
	// �C���^���N�g����G��T���֐�
	std::shared_ptr<EnemyBase> FindEnemy();

	// ���C���A�N�^�[�̍��W
	Vec3 m_mainActorPos;
	
	// �C���^���N�g�ł���G�̍��W
	std::shared_ptr<EnemyBase> m_enemyPtr;

	// �T�C���J�[�u�p�̃t���[��
	float m_flame;

	std::list<std::shared_ptr<EnemyBase>>& m_enemyManager;
};