#include "Player.h"
#include "MainActor.h"
#include "SubActor.h"
#include "Input.h"
#include "PlayerCamera.h"
#include "UI.h"
#include "Direction.h"
#include "EffekseerForDXLib.h"
#include "DxLib.h"

Player::Player(std::shared_ptr<Direction>& direction) :
	m_subActorFlag(false),
	m_pDirection(direction)
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
	if (!m_pDirection->IsPlaySequ()) {

		// ����؂�ւ�
		(this->*m_updateMode)();

		// ����ύX�{�^���������ꂽ��T�u�A�N�^�[�ƃ��C���A�N�^�[�Ƃ̑����ύX����(����Y�{�^��)
		if (Input::getInstance().IsTrigger(INPUT_Y)) {
			// ���[�h�ύX
			ChangeMode();
		}

		// �J�����̍X�V
		m_pCamera->Update(GetPos());

	}

	// �C���^���N�g�{�^���������ꂽ�Ƃ��̏���
	if (Input::getInstance().IsTrigger(INPUT_X)) {
		// �C���^���N�g����
		InteractFunc();
	}
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

void Player::CollisionMove(Vec3 vec)
{
	// �����蔻���̍��W�Ɉړ�����
	m_pMainActor->Position += vec;

	// �ړ�������Ƀ��C���A�N�^�[�̃J�v�Z���ƃJ�������X�V����
	m_pCamera->Update(GetPos());
	m_pMainActor->Set(m_pMainActor->Position);
}

bool Player::IsSubActorControl()
{
	return m_subActorFlag;
}

CapsuleData& Player::GetCupsule()
{
	return m_pMainActor->m_data;
}

void Player::MainActorUpdate()
{
	m_pMainActor->Control(m_pCamera->Angle);
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
		m_pCamera->ChangeMode(SUBACTOR_MODE);
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
		m_pCamera->ChangeMode(MAINACTOR_MODE);
	}
}

void Player::InteractFunc()
{
	// �C��V�[�P���X���Đ�����Ă�����V�[�P���X�𔲂���
	if (m_pDirection->IsPlaySequ()) {
		m_pDirection->StopSequence();
	}
	// �G�l�~�[�C���^���N�g���\�̏ꍇ
	else if (UI::getInstance().GetEnemyInteractFlag()) {
		// �C�₳����V�[�P���X�ɓ���
		m_pDirection->PlayFaintSequ(m_pCamera->Position);
		m_pDirection->SetEnemyPos(m_pSubActor->GetEnemyPos());
		// �C���^���N�g�{�^�����\���ɂ���
		UI::getInstance().SetEnemyInteractFlag(false);
	}
}
