#pragma once
#include <memory>
#include "Vec3.h"

class Brutus;
class Os;
// �v���C���[�N���X
class Player
{
public:
	Player();
	~Player();

	void Update();
	void Draw() const;

	Vec3 GetPos() const;
private:

	// �֐��|�C���^
	using m_updateMode_t = void (Player::*)();
	using m_drawMode_t = void (Player::*)() const;
	m_updateMode_t m_updateMode = nullptr;
	m_drawMode_t m_drawMode = nullptr;

	// ���샂�[�h
	void BrutusUpdate();	// �u���[�^�X���쎞�̍X�V����
	void BrutusDraw() const;		// �u���[�^�X���쎞�̕`�揈��

	void OsUpdate();	// �I�Y���쎞�̍X�V����
	void OsDraw() const;		// �I�Y���쎞�̕`�揈��

	// ���샂�[�h��ύX����֐�
	void ChangeMode();

	// �u���[�^�X�ƃI�Y�̃|�C���^
	std::shared_ptr<Brutus> m_pBrutus;
	std::shared_ptr<Os> m_pOs;

	// �I�Y�𑀍삵�Ă��邩�ǂ���
	bool m_osFlug;
};

