#include "PlayerCamera.h"
#include <cassert>
#include "Input.h"

PlayerCamera::PlayerCamera():
	m_changeFlag(false)
{
	// �O���t�@�C������萔���擾����
	assert(ConstantsFileLoad("data/constant/PlayerCamera.csv", Constants) == 1);

	// �J�����̃j�A�t�@�[�̐ݒ�
	SetCameraNearFar(Constants["CAMERA_NEAR"], Constants["CAMERA_FAR"]);

	// ���[�h�̏�����
	m_modeFunc = &PlayerCamera::MainActorMode;

	// ���C�g�̃J���[�𒲐�����
	SetLightDifColor(GetColorF(0.8f, 0.8f, 0.8f, 0.0f));
}

PlayerCamera::~PlayerCamera()
{
}

void PlayerCamera::Init(Vec3 pos)
{
	// �����ʒu�ɐݒ肷��
	Position = Vec3{ pos.x + Constants["CAMERA_BASE_POS_X"],pos.y + Constants["CAMERA_BASE_POS_Y"], pos.z + Constants["CAMERA_BASE_POS_Z"], };
}

void PlayerCamera::Update(Vec3 pos)
{
	(this->*m_modeFunc)(pos);

	// ���C�g�̉�]
	// ��ƂȂ�^�[�Q�b�g�̍��W
	VECTOR basePos = VGet(Constants["CAMERA_TARGET_POS_X"], Constants["CAMERA_TARGET_POS_Y"], Constants["CAMERA_TARGET_POS_Z"]);

	SetLightDirection(MakeBasePos(basePos));
}

void PlayerCamera::ChangeMode(int mode, Vec3 pos)
{
	// �����ɂ���ă��[�h��ύX����
	if (mode == SUBACTOR_MODE) {

		// ���T�u�A�N�^�[���[�h�ɕύX����
		m_modeFunc = &PlayerCamera::SubActorMode;

		// ���W��ۑ�����
		m_savePos = Position;
		m_saveTarget = VAdd(Position.VGet(), MakeBasePos(VGet(Constants["CAMERA_TARGET_POS_X"], Constants["CAMERA_TARGET_POS_Y"], Constants["CAMERA_TARGET_POS_Z"])));
		m_saveAngle = Angle;
		return;
	}
	if (mode == MAINACTOR_MODE) {

		// �؂�ւ����t���O�𗧂Ă�
		m_changeFlag = true;

		// �ۑ��������W�Ɉړ����鏈���Ɉڂ�
		m_modeFunc = &PlayerCamera::ChangeMainActorMode;

		// ���������W�ւ̒P�ʃx�N�g�����쐬����
		m_unitPos = (m_savePos - Position).GetNormalized();

		// ���݂̃^�[�Q�b�g�����߂�
		m_target = VAdd(Position.VGet(), MakeBasePos(VGet(Constants["CAMERA_TARGET_POS_X"], Constants["CAMERA_TARGET_POS_Y"], Constants["CAMERA_TARGET_POS_Z"])));

		// ���݂̃^�[�Q�b�g���烁�C���A�N�^�[�Ɍ������^�[�Q�b�g�ւ̒P�ʃx�N�g�����쐬����
		m_unitTarget = (Vec3{ pos.x,Constants["CAMERA_MARGIN_Y"],pos.z } - m_target).GetNormalized();

		return;
	}
}

bool PlayerCamera::IsModeChange()
{
	return m_changeFlag;
}

void PlayerCamera::MainActorMode(Vec3 pos)
{
	// ��]
	Position = RotateMainActorMode(pos);

	// �J�����̈ʒu���Z�b�g����
	SetCameraPositionAndTarget_UpVecY(Position.VGet(), VECTOR{ pos.x,Constants["CAMERA_MARGIN_Y"],pos.z });
}

void PlayerCamera::SubActorMode(Vec3 pos)
{
	// ���W���T�u�A�N�^�[�̈ʒu�ɍ��킹��
	Position = pos;

	// �J�����̈ʒu���Z�b�g����
	SetCameraPositionAndTarget_UpVecY(Position.VGet(), RotateSubActorMode(pos).VGet());
}

void PlayerCamera::ChangeMainActorMode(Vec3 pos)
{
	bool a  = false;
	bool b = false;
	if ((Vec3{ pos.x,Constants["CAMERA_MARGIN_Y"],pos.z } - m_target).Length() > 2.0f) {
		// �P�ʃx�N�g���̕����Ƀ^�[�Q�b�g���ړ�����
		m_target += m_unitTarget * Constants["CAMERA_TARGET_MOVE_SCALE"];
	}
	else {
		a = true;
	}
	if ((Position - m_savePos).Length() > 5.0f) {
		// �P�ʃx�N�g���̕����Ɉ��̑��x�ňړ�����
		Position += m_unitPos * Constants["CAMERA_MOVE_SCALE"];
	}
	else {
		b = true;
	}

	// �J�����̈ʒu���Z�b�g����
	SetCameraPositionAndTarget_UpVecY(Position.VGet(), m_target.VGet());

	// ���W�ƃ^�[�Q�b�g���ǂ�����ڕW�ɓ��B�����烁�C���A�N�^�[���[�h�ɐ؂�ւ���
	if (a && b) {

		// �؂�ւ����t���O��������
		m_changeFlag = false;

		// �ۑ������A���O���ɂ��Ă���
		Angle = m_saveAngle;

		// �؂�ւ�
		m_modeFunc = &PlayerCamera::MainActorMode;
	}
}

Vec3 PlayerCamera::RotateMainActorMode(Vec3 pos)
{
	// �C���v�b�g�̃C���X�^���X���擾
	auto& input = Input::getInstance();

	// �E�X�e�B�b�N�ŉ�]
	if (input.GetStickVectorLength(INPUT_RIGHT_STICK) > input.Constants["STICK_INVALID_VALUE"]) {

		// �X�e�B�b�N���X���������̉�]�̒l�𑝌�������
		if (input.GetStickVector(INPUT_RIGHT_STICK).x != 0) {
			Angle.y += Constants["CAMERA_ANGLE_VARIATION"] * (input.GetStickThumbX(INPUT_RIGHT_STICK));
		}
		if (input.GetStickVector(INPUT_RIGHT_STICK).z != 0) {
			Angle.z += Constants["CAMERA_ANGLE_VARIATION"] * (input.GetStickThumbY(INPUT_RIGHT_STICK));
		}
	}

	// �ő�l�ƍŒ�l�𒲐�����
	if (Angle.z <= -Constants["CAMERA_ANGLE_RANGE"]) {
		Angle.z = -Constants["CAMERA_ANGLE_RANGE"];
	}
	else if (Angle.z >= Constants["CAMERA_ANGLE_RANGE"]) {
		Angle.z = Constants["CAMERA_ANGLE_RANGE"];
	}

	// ��ƂȂ�J�����̍��W
	VECTOR basePos = VGet(Constants["CAMERA_BASE_POS_X"], Constants["CAMERA_BASE_POS_Y"], Constants["CAMERA_BASE_POS_Z"]);

	// �J�������W�̓v���C���[���W����ϊ��������W�𑫂����Ƃ���
	return VAdd(VGet(pos.x, 0.0f, pos.z), MakeBasePos(basePos));
}

Vec3 PlayerCamera::RotateSubActorMode(Vec3 pos)
{
	// �C���v�b�g�̃C���X�^���X���擾
	auto& input = Input::getInstance();

	// �E�X�e�B�b�N�ŉ�]
	if (input.GetStickVectorLength(INPUT_RIGHT_STICK) > input.Constants["STICK_INVALID_VALUE"]) {

		// �X�e�B�b�N���X���������̉�]�̒l�𑝌�������
		if (input.GetStickVector(INPUT_RIGHT_STICK).x != 0) {
			Angle.y += Constants["CAMERA_ANGLE_VARIATION"] * (input.GetStickThumbX(INPUT_RIGHT_STICK));
		}
		if (input.GetStickVector(INPUT_RIGHT_STICK).z != 0) {
			Angle.z += Constants["CAMERA_ANGLE_VARIATION"] * (input.GetStickThumbY(INPUT_RIGHT_STICK));
		}
	}

	// �ő�l�ƍŒ�l�𒲐�����
	if (Angle.z <= -Constants["CAMERA_ANGLE_RANGE"]) {
		Angle.z = -Constants["CAMERA_ANGLE_RANGE"];
	}
	else if (Angle.z >= Constants["CAMERA_ANGLE_RANGE"]) {
		Angle.z = Constants["CAMERA_ANGLE_RANGE"];
	}

	// ��ƂȂ�^�[�Q�b�g�̍��W
	VECTOR basePos = VGet(Constants["CAMERA_TARGET_POS_X"], Constants["CAMERA_TARGET_POS_Y"], Constants["CAMERA_TARGET_POS_Z"]);

	// �^�[�Q�b�g���W�̓J�������W����ϊ��������W�𑫂����Ƃ���
	return VAdd(Position.VGet(), MakeBasePos(basePos));
}

VECTOR PlayerCamera::MakeBasePos(VECTOR base)
{
	// ��]�s����쐬
	MATRIX rotMtxX, rotMtxZ;
	rotMtxX = MGetRotY(Angle.y);
	rotMtxZ = MGetRotX(Angle.z);

	// ����W���s��ŕϊ�
	base = VTransform(base, rotMtxZ);
	base = VTransform(base, rotMtxX);

	return base;
}
