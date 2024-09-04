#pragma once
#include "Vec3.h"
#include <memory>
#include "Constant.h"

struct tama
{
	Vec3 pos;
	Vec3 moveVec;

	float length;
};

class EnemyBase;
class DirectionCamera;
class Direction:
	public Constant
{
public:
	Direction();
	virtual ~Direction();

	void Init();
	void Update();
	void Draw();

	// �C��V�[�P���X���Đ�����
	void PlayFaintSequ(Vec3 cameraPos);

	// �C�₳����G�̃|�C���^���Z�b�g����
	void SetEnemyPtr(std::shared_ptr<EnemyBase> enemy);

	// �V�[�P���X�𔲂���
	void StopSequence();

	// �V�[�P���X���Đ����ł��邩
	bool IsPlaySequ();

	// �C�₳�������ǂ���
	bool IsFaintEnemy();
private:

	// �֐��|�C���^
	using m_updateFunc_t = void (Direction::*)();
	using m_drawFunc_t = void (Direction::*)() const;
	m_updateFunc_t m_updateFunc = nullptr;
	m_drawFunc_t m_drawFunc = nullptr;

	// null
	void NullUpdate();
	void NullDraw() const;

	// �C��V�[�P���X����
	void FaintUpdate();
	void FaintDraw() const;

	// �f�B���N�V�����J�����̃|�C���^
	std::shared_ptr<DirectionCamera> m_pCamera;

	// �f�B���N�V�������Đ�����t���O
	bool m_playFlag = false;

	// �C�₳����G�̃|�C���^
	std::shared_ptr<EnemyBase> m_enemyPtr;

	// �E�̋�
	tama m_right;

	// ���̒e
	tama m_left;

	// �ڕW�n�_
	Vec3 m_target;

	// �C�₳�����t���O
	bool m_faintFlag;

	// �t���[���J�E���^
	int m_flame;
};

