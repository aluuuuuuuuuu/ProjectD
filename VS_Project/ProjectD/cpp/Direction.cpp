#include "Direction.h"
#include "DxLib.h"
#include "DirectionCamera.h"
#include "Input.h"
#include <cassert>
#include "EnemyBase.h"

Direction::Direction() :
	m_playFlag(false),
	m_faintFlag(false),
	m_flame(0)
{
	// �O���t�@�C������萔���擾����
	assert(ConstantsFileLoad("data/constant/Direction.csv", Constants) == 1);

	m_updateFunc = &Direction::NullUpdate;
	m_drawFunc = &Direction::NullDraw;

	// �f�B���N�V�����J�����̍쐬
	m_pCamera = std::make_shared<DirectionCamera>();
}

Direction::~Direction()
{
}

void Direction::Init()
{
}

void Direction::Update()
{
	(this->*m_updateFunc)();
}

void Direction::Draw()
{
	(this->*m_drawFunc)();
}

void Direction::PlayFaintSequ(Vec3 cameraPos)
{
	// �֐��|�C���^�̐ݒ�
	m_updateFunc = &Direction::FaintUpdate;
	m_drawFunc = &Direction::FaintDraw;

	// �J�����̍��W���󂯎��
	m_pCamera->Position = cameraPos;

	// ���o���s���Ă���t���O�𗧂Ă�
	m_playFlag = true;

	// ���E�̋ʂ̍��W�̐ݒ�
	m_left.pos = Vec3{ Constants["FAINT_LEFT_POS_X"],0.0f,Constants["FAINT_LEFT_POS_Z"] };
	m_right.pos = Vec3{ Constants["FAINT_RIGHT_POS_X"],0.0f,Constants["FAINT_RIGHT_POS_Z"] };

	// �^�[�Q�b�g�̍��W�̐ݒ�
	m_target = Vec3{ Constants["FAINT_TARGET_POS_X"],0.0f,Constants["FAINT_TARGET_POS_Y"] };
}

void Direction::SetEnemyPtr(std::shared_ptr<EnemyBase> enemy)
{
	m_enemyPtr = enemy;
}

void Direction::StopSequence()
{
	m_updateFunc = &Direction::NullUpdate;
	m_drawFunc = &Direction::NullDraw;
	m_playFlag = false;
}

bool Direction::IsPlaySequ()
{
	return m_playFlag;
}

bool Direction::IsFaintEnemy()
{
	return m_faintFlag;
}

void Direction::NullUpdate()
{
}

void Direction::NullDraw() const
{
}

void Direction::FaintUpdate()
{
	// �G���C�₳���Ă����牽�����Ȃ�
	if (m_faintFlag) {

		// ���t���[����������ʏ�̏����Ɉڍs����
		if (m_flame >= Constants["END_FLAME"]) {
			m_playFlag = false;
			m_flame = 0;
		}
		else {
			m_flame++;
		}
	}
	else {
		// �C���v�b�g�̃C���X�^���X���擾
		auto& input = Input::getInstance();

		// �J�����̃^�[�Q�b�g��G�̈ʒu�ɌŒ肷��
		m_pCamera->Update(m_enemyPtr->Position.VGet());

		float moveScaleLeft = 1.0f;
		float moveScaleRight = 1.0f;

		// ���܂ɋ߂Â��ɘA��ړ����x���x���Ȃ��Ă���

		// �ڕW�Ƃ̋�����ۑ�����
		m_left.length = (m_left.pos - m_target).Length();
		m_right.length = (m_right.pos - m_target).Length();

		// ��
		if (m_left.length <= Constants["TARGET_RANGE"]) {
			moveScaleLeft = static_cast<float>(1.0 - (1 - m_left.length / Constants["TARGET_RANGE"]));
		}
		// �E
		if (m_right.length <= Constants["TARGET_RANGE"]) {
			moveScaleRight = static_cast<float>(1.0 - (1 - m_right.length / Constants["TARGET_RANGE"]));
		}

		// �~���^�[�Q�b�g�ɋ߂Â��ɂ�U�����傫���Ȃ�
		int vibe = 0;
		// ��
		if (m_left.length <= Constants["TARGET_RANGE"]) {
			vibe += static_cast<int>(500 * (1 - m_left.length / Constants["TARGET_RANGE"]));
		}
		// �E
		if (m_right.length <= Constants["TARGET_RANGE"]) {
			vibe += static_cast<int>(500 * (1 - m_right.length / Constants["TARGET_RANGE"]));
		}

		//���E�̃X�e�B�b�N���͂ŋʂ𓮂���
		// ��
		if (input.GetStickVectorLength(INPUT_LEFT_STICK) > input.Constants["STICK_INVALID_VALUE"]) {

			// �ړ��x�N�g�����쐬
			m_left.moveVec = input.GetStickUnitVector(INPUT_LEFT_STICK);
			m_left.moveVec.z *= -1;

			// ���W���ړ�
			m_left.pos += m_left.moveVec * moveScaleLeft * Constants["MOVE_SCALE"];

			// �R���g���[���[��U��������
			StartJoypadVibration(DX_INPUT_PAD1, vibe, 10);
		}

		// �X�e�B�b�N�𗣂����猳�̏ꏊ�ɖ߂�
		else {

			// ������x�߂Â��Ă�����ړ����~�߂�
			if ((m_left.pos - Vec3{ Constants["FAINT_LEFT_POS_X"],0.0f,Constants["FAINT_LEFT_POS_Z"] }).Length() <= Constants["MOVE_STOP_RANGE"]) {
				m_left.pos = Vec3{ Constants["FAINT_LEFT_POS_X"],0.0f,Constants["FAINT_LEFT_POS_Z"] };
			}
			else {
				m_left.moveVec = (Vec3{ Constants["FAINT_LEFT_POS_X"],0.0f,Constants["FAINT_LEFT_POS_Z"] } - m_left.pos).GetNormalized();
				m_left.pos += m_left.moveVec * Constants["RETURN_MOVE_SCALE"];
			}
		}
		// �E
		if (input.GetStickVectorLength(INPUT_RIGHT_STICK) > input.Constants["STICK_INVALID_VALUE"]) {

			// �ړ��x�N�g�����쐬
			m_right.moveVec = input.GetStickUnitVector(INPUT_RIGHT_STICK);
			m_right.moveVec.z *= -1;

			// ���W���ړ�
			m_right.pos += m_right.moveVec * moveScaleRight * Constants["MOVE_SCALE"];

			// �R���g���[���[��U��������
			StartJoypadVibration(DX_INPUT_PAD1, vibe, 10);
		}

		// �X�e�B�b�N�𗣂����猳�̏ꏊ�ɖ߂�
		else {

			// ������x�߂Â��Ă�����ړ����~�߂�
			if ((m_right.pos - Vec3{ Constants["FAINT_RIGHT_POS_X"],0.0f,Constants["FAINT_RIGHT_POS_Z"] }).Length() <= Constants["MOVE_STOP_RANGE"]) {
				m_right.pos = Vec3{ Constants["FAINT_RIGHT_POS_X"],0.0f,Constants["FAINT_RIGHT_POS_Z"] };
			}
			else {
				m_right.moveVec = (Vec3{ Constants["FAINT_RIGHT_POS_X"],0.0f,Constants["FAINT_RIGHT_POS_Z"] } - m_right.pos).GetNormalized();
				m_right.pos += m_right.moveVec * Constants["RETURN_MOVE_SCALE"];
			}
		}

		// �ڕW�ɂ�����x�߂Â�����
		if (m_left.length <= Constants["ENEMY_FAINT_LENGTH"] && m_right.length <= Constants["ENEMY_FAINT_LENGTH"]) {
			// �G���L�����鏈�����J�n������
			m_enemyPtr->SetStartDeadFlag();

			// �C�₳�����t���O�𗧂Ă�
			m_faintFlag = true;
		}
	}
	

}

void Direction::FaintDraw() const
{
	// �G���C�₳���Ă�����\�����Ȃ�
	if (m_faintFlag) {

	}
	else {
		// �ڕW�̋ʂ�`��
		DrawCircle(m_target.intX(), m_target.intZ(), 30, 0xffff00, true);

		// �E�̋ʂ�`��
		DrawCircle(m_right.pos.intX(), m_right.pos.intZ(), static_cast<int>(Constants.at("CIRCLE_RADIUS")), 0x00ff00, true);

		// ���̋ʂ�`��
		DrawCircle(m_left.pos.intX(), m_left.pos.intZ(), static_cast<int>(Constants.at("CIRCLE_RADIUS")), 0x00ff00, true);
	}
}
