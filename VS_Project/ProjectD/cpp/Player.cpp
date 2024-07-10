#include "Player.h"
#include "MainActor.h"
#include "SubActor.h"
#include "Input.h"
#include "PlayerCamera.h"
#include "UI.h"
#include "Sequence.h"

Player::Player() :
	m_subActorFlag(false)
{
	// �e�|�C���^�̍쐬
	m_pMainActor = std::make_shared<MainActor>();
	m_pSubActor = std::make_shared<SubActor>();
	m_pCamera = std::make_shared<PlayerCamera>();

	// �֐��|�C���^�̏�����
	m_updateMode = &Player::MainActorUpdate;
	m_drawMode = &Player::MainActorDraw;

	// �J�����̏�������
	m_pCamera->Init(GetPos());
}

Player::~Player()
{
}

void Player::Update()
{
	if (!Sequence::getInstance().IsPlaySequ()) {
		// ����؂�ւ�
		(this->*m_updateMode)();

		// ����ύX�{�^���������ꂽ��T�u�A�N�^�[�ƃ��C���A�N�^�[�Ƃ̑����ύX����(����Y�{�^��)
		if (Input::getInstance().IsTrigger(INPUT_Y)) {
			// ���[�h�ύX
			ChangeMode();
		}
	}
	
	// �C���^���N�g�{�^���������ꂽ�Ƃ��̏���
	if (Input::getInstance().IsTrigger(INPUT_X)) {
		// �C���^���N�g����
		InteractFunc();
	}

	// �J�����̍X�V
	m_pCamera->Update(GetPos());
}

void Player::Draw() const
{
	// �`��؂�ւ�
	(this->*m_drawMode)();
}

Vec3 Player::GetPos() const
{
	// ���샂�[�h�ɂ���ĕԂ��l���ς��
	if (m_subActorFlag) {
		return m_pSubActor->Position;
	}
	else {
		return m_pMainActor->Position;
	}
}

void Player::MainActorUpdate()
{
	m_pMainActor->Control();
	m_pMainActor->Update();
}

void Player::MainActorDraw() const
{
	m_pMainActor->Draw();
}

void Player::SubActorUpdate()
{
	m_pSubActor->Control(m_pCamera->Angle);
	m_pMainActor->Update();
	m_pSubActor->Update();
}

void Player::SubActorDraw() const
{
	m_pMainActor->Draw();
	m_pSubActor->Draw();
}

void Player::ChangeMode()
{
	// ����t���O�𔽓]����
	m_subActorFlag = !m_subActorFlag;
	
	// �Ă΂ꂽ�Ƃ��̃T�u�A�N�^�[�t���O�Ń��[�h��ύX����
	if (m_subActorFlag) {
		m_updateMode = &Player::SubActorUpdate;
		m_drawMode = &Player::SubActorDraw;

		// �T�u�A�N�^�[�ɕύX����Ƃ��͏����������Ă�
		m_pSubActor->ChangeInit(m_pCamera->Position, m_pMainActor->Position);

		// �ύX���̃J�����̈ʒu�Ɗp�x��ۑ����Ă���
		m_changePos = m_pCamera->Position;
		m_changeAngle = m_pCamera->Angle;

		// �J�����̃��[�h��ύX����
		m_pCamera->ChangeMode(OS_MODE);
	}
	else {
		m_updateMode = &Player::MainActorUpdate;
		m_drawMode = &Player::MainActorDraw;

		// ���C���A�N�^�[�ɕύX����Ƃ��͕ۑ��������W�ɃJ������u��
		m_pCamera->Position = m_changePos;
		m_pCamera->Angle = m_changeAngle;

		// ���C���A�N�^�[�ɐ؂�ւ����Ƃ��G�ɑ΂���{�^���\�����I�t�ɂ���
		UI::getInstance().SetEnemyInteractFlag(false);

		// �J�����̃��[�h��ύX����
		m_pCamera->ChangeMode(BRUTUS_MODE);
	}
}

void Player::InteractFunc()
{
	// �C��V�[�P���X���Đ�����Ă�����V�[�P���X�𔲂���
	if (Sequence::getInstance().IsPlaySequ()) {
		Sequence::getInstance().StopSequence();
	}
	// �G�l�~�[�C���^���N�g���\�̏ꍇ
	else if (UI::getInstance().GetEnemyInteractFlag()) {
		// �C�₳����V�[�P���X�ɓ���
		Sequence::getInstance().PlayFaintSequ();

		// �C���^���N�g�{�^�����\���ɂ���
		UI::getInstance().SetEnemyInteractFlag(false);
	}
}
