#include "Camera.h"
#include <cassert>
#include "StaticFunction.h"
#include "Input.h"

Camera::~Camera()
{
}

void Camera::Init(Vec3 pos)
{
	// �O���t�@�C������萔���擾����
	assert(ConstantsFileLoad("data/constant/Camera.csv", Constants) == 1);

	// �J�����̃j�A�t�@�[�̐ݒ�
	SetCameraNearFar(Constants["CAMERA_NEAR"], Constants["CAMERA_FAR"]);

	Position = Vec3{ pos.x + Constants["CAMERA_BASE_POS_X"],pos.y + Constants["CAMERA_BASE_POS_Y"], pos.z + Constants["CAMERA_BASE_POS_Z"], };

	// ���[�h�̏�����
	m_modeFunc = &Camera::BrutusMode;
}

void Camera::Update(Vec3 pos)
{
	(this->*m_modeFunc)(pos);
}

void Camera::ChangeMode(bool osFlug)
{
	// �t���O��true�̂Ƃ��̓I�Y���[�h�ɕύX
	if (osFlug) {
		m_modeFunc = &Camera::OsMode;
	}
	else {
		m_modeFunc = &Camera::BrutusMode;
	}
}

void Camera::BrutusMode(Vec3 pos)
{
	// ��]
	RotateBrutus(pos);

	// �J�����̈ʒu���Z�b�g����
	SetCameraPositionAndTarget_UpVecY(Position.VGet(), VECTOR{ pos.x,Constants["CAMERA_MARGIN_Y"],pos.z });
}

void Camera::OsMode(Vec3 pos)
{

	// ���W���I�Y�̈ʒu�ɍ��킹��
	Position = pos;

	// ��]
	VECTOR target =  RotateOs(pos).VGet();

	// �J�����̈ʒu���Z�b�g����
	SetCameraPositionAndTarget_UpVecY(Position.VGet(),target);
}

void Camera::RotateBrutus(Vec3 pos)
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

	// ��]�s����쐬
	MATRIX rotMtxX, rotMtxZ;
	rotMtxX = MGetRotY(Angle.y);
	rotMtxZ = MGetRotX(Angle.z);


	// ����W���s��ŕϊ�
	basePos = VTransform(basePos, rotMtxZ);
	basePos = VTransform(basePos, rotMtxX);

	// �J�������W�̓v���C���[���W����ϊ��������W�𑫂����Ƃ���
	Position = VAdd(VGet(pos.x, 0.0f, pos.z), basePos);
}

Vec3 Camera::RotateOs(Vec3 pos)
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

	// ��]�s����쐬
	MATRIX rotMtxX, rotMtxZ;
	rotMtxX = MGetRotY(Angle.y);
	rotMtxZ = MGetRotX(Angle.z);


	// ����W���s��ŕϊ�
	basePos = VTransform(basePos, rotMtxZ);
	basePos = VTransform(basePos, rotMtxX);

	// �^�[�Q�b�g���W�̓J�������W����ϊ��������W�𑫂����Ƃ���
	return VAdd(Position.VGet(), basePos);

	DrawSphere3D(VAdd(Position.VGet(), basePos), 16, 16, 0xff0000, 0xff0000, true);
}
