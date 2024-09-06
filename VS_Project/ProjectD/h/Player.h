#pragma once
#include <memory>
#include "Vec3.h"
#include <list>
#include "Components.h"

class EnemyBase;
class Direction;
class MainActor;
class SubActor;
class PlayerCamera;
// �v���C���[�N���X
class Player
{
public:
	Player(std::shared_ptr<Direction>& direction, std::list<std::shared_ptr<EnemyBase>>& enemy);
	~Player();

	void Update();
	void Draw() const;

	CapsuleData& GetCupsule();

	Vec3 GetPos() const;

	// �����蔻���̈ړ��x�N�g�����󂯎���Ĕ��f������
	void CollisionMove(Vec3 vec);

	// ���݃T�u�A�N�^�[�𑀍삵�Ă��邩�ǂ���
	bool IsSubActorControl();

	// ���샂�[�h��ύX����֐�
	void ChangeMode();

private:

	// �֐��|�C���^
	using m_updateMode_t = void (Player::*)();
	using m_drawMode_t = void (Player::*)() const;
	m_updateMode_t m_updateMode = nullptr;
	m_drawMode_t m_drawMode = nullptr;

	// ���샂�[�h
	void MainActorUpdate();	// ���C���A�N�^�[���쎞�̍X�V����
	void MainActorDraw() const;		// ���C���A�N�^�[���쎞�̕`�揈��

	void SubActorUpdate();	// �T�u�A�N�^�[���쎞�̍X�V����
	void SubActorDraw() const;		// �T�u�A�N�^�[���쎞�̕`�揈��

	// �C���^���N�g�{�^���������ꂽ�Ƃ��̏���
	void InteractFunc();

	// ���C���A�N�^�[�ƃT�u�A�N�^�[�̃|�C���^
	std::shared_ptr<MainActor> m_pMainActor;
	std::shared_ptr<SubActor> m_pSubActor;

	// �J�����̃|�C���^
	std::shared_ptr<PlayerCamera> m_pCamera;

	// �f�B���N�V�����̎Q��
	std::shared_ptr<Direction> m_pDirection;

	// �T�u�A�N�^�[�𑀍삵�Ă��邩�ǂ���
	bool m_subActorFlag;

	// ���C���A�N�^�[��
};

