#include "Player.h"
#include "Brutus.h"
#include "Os.h"
#include "Input.h"
#include "Camera.h"
#include "UI.h"

Player::Player() :
	m_osFlag(false)
{
	// �e�|�C���^�̍쐬
	m_pBrutus = std::make_shared<Brutus>();
	m_pOs = std::make_shared<Os>();

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
		// ���[�h�ύX
		ChangeMode();
	}

	// �C���^���N�g�{�^���������ꂽ�Ƃ��̏���
	if (Input::getInstance().IsTrigger(INPUT_X)) {
		// �C���^���N�g����
		InteractFunc();
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
	if (m_osFlag) {
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
	// ����t���O�𔽓]����
	m_osFlag = !m_osFlag;

	// �Ă΂ꂽ�Ƃ��̃I�Y�t���O�Ń��[�h��ύX����
	if (m_osFlag) {
		m_updateMode = &Player::OsUpdate;
		m_drawMode = &Player::OsDraw;

		// �I�Y�ɕύX����Ƃ��͏����������Ă�
		m_pOs->ChangeInit(m_pBrutus->Position);

		// �ύX���̃J�����̈ʒu�Ɗp�x��ۑ����Ă���
		m_changePos = Camera::getInstance().Position;
		m_changeAngle = Camera::getInstance().Angle;

		// �J�����̃��[�h��ύX����
		Camera::getInstance().ChangeMode(OS_MODE);
	}
	else {
		m_updateMode = &Player::BrutusUpdate;
		m_drawMode = &Player::BrutusDraw;

		// �u���[�^�X�ɕύX����Ƃ��͕ۑ��������W�ɃJ������u��
		Camera::getInstance().Position = m_changePos;
		Camera::getInstance().Angle = m_changeAngle;

		// �u���[�^�X�ɐ؂�ւ����Ƃ��G�ɑ΂���{�^���\�����I�t�ɂ���
		UI::getInstance().SetEnemyInteractFlag(false);

		// �J�����̃��[�h��ύX����
		Camera::getInstance().ChangeMode(BRUTUS_MODE);
	}
}

void Player::InteractFunc()
{
	// �G�l�~�[�C���^���N�g���\�̏ꍇ
	if (UI::getInstance().GetEnemyInteractFlag()) {
		// �C�₳����V�[�P���X�ɓ���
	}
}
