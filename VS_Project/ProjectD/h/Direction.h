#pragma once
#include "Vec3.h"
#include <memory>
#include "Constant.h"

struct tama
{
	Vec3 pos;
	Vec3 moveVec;
	float moveScale;
};

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

	// �C�₳����G�̍��W���Z�b�g����
	void SetEnemyPos(Vec3 pos);

	// �V�[�P���X�𔲂���
	void StopSequence();

	// �V�[�P���X���Đ����ł��邩
	bool IsPlaySequ();
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

	// �C�₳����G�̍��W
	Vec3 m_enemyPos;

	// �E�̋�
	tama m_right;

	// ���̒e
	tama m_left;
};

