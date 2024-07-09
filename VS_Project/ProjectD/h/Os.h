#pragma once
#include "CharactorBase.h"
#include <memory>

class EnemyBase;
class Os :
	public CharactorBase
{
public:
	Os();
	~Os();

	void Update();
	void Draw() const;

	// �����ύX�����Ƃ��̏�������
	void ChangeInit(Vec3 pos);

	void Control();
private:
	// �C���^���N�g����G��T���֐�
	std::shared_ptr<EnemyBase> FindEnemy();

	// �u���[�^�X�̍��W
	Vec3 m_brutusPos;
};