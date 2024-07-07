#include "Player.h"
#include "Brutus.h"
#include "Os.h"
#include "Input.h"
#include "Camera.h"

Player::Player() :
	m_osFlug(false)
{
	// �e�|�C���^�̍쐬
	m_pBrutus = make_shared<Brutus>();
	m_pOs = make_shared<Os>();

	// �֐��|�C���^�̏�����
	m_updateMode = &Player::BrutusUpdate;
	m_drawMode = &Player::BrutusDraw;
}

Player::~Player()
{
}

void Player::Update()
{
	// ����ύX�{�^���������ꂽ��I�Y�ƃu���[�^�X�̑����ύX����(����Y�{�^��)
	if (Input::getInstance().IsTrigger(INPUT_Y)) {

		// ���݂̑���t���O�𔽓]����
		m_osFlug = !m_osFlug;

		// �I�Y�̏�������
		m_pOs->ChangeInit();

		// ���[�h�ύX
		ChangeMode();

		// �J�����̃��[�h�����킹��
		Camera::getInstance().ChangeMode(m_osFlug);
	}

	// ����؂�ւ�
	(this->*m_updateMode)();
}

void Player::Draw() const
{
	// �`��؂�ւ�
	(this->*m_drawMode)();
}

Vec3 Player::GetPos() const
{
	// ���샂�[�h�ɂ���ĕԂ��l���ς��
	if (m_osFlug) {
		return m_pOs->Position;
	}
	else {
		return m_pBrutus->Position;
	}
}

void Player::BrutusUpdate()
{
	m_pBrutus->Control();
	m_pBrutus->Update();
}

void Player::BrutusDraw() const
{
	m_pBrutus->Draw();
}

void Player::OsUpdate()
{
	m_pOs->Control();
	m_pBrutus->Update();
	m_pOs->Update();
}

void Player::OsDraw() const
{
	m_pBrutus->Draw();
	m_pOs->Draw();
}

void Player::ChangeMode()
{
	// �Ă΂ꂽ�Ƃ��̃I�Y�t���O�Ń��[�h��ύX����
	if (m_osFlug) {
		m_updateMode = &Player::OsUpdate;
		m_drawMode = &Player::OsDraw;
	}
	else {
		m_updateMode = &Player::BrutusUpdate;
		m_drawMode = &Player::BrutusDraw;
	}
}
