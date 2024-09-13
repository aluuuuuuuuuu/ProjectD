#include "MainActor.h"
#include "DxLib.h"
#include "Input.h"
#include <cassert>

MainActor::MainActor()
{
	// �O���t�@�C������萔���擾����
	ReadCSV("data/constant/MainActor.csv");

	// �����ʒu�̐ݒ�
	Position = Vec3{ 0.0f,0.0f,0.0f };

	// �g��̐ݒ�
	Scale = Vec3{ 0.2f,0.2f,0.2f };

	// ���f���̏�������
	InitModel(MV1LoadModel("data/model/MainActor.mv1"));

	// �A�j���[�V�����̏�������
	InitAnimation(ModelHandle, std::get<int>(Constants["ANIM_IDLE"]), 0.15f);

	// �J�v�Z���̏���������
	InitCapsule(Position, 10, 10);
}

MainActor::~MainActor()
{
}

void MainActor::Update()
{
	AnimationControl();
	UpdateAnimation(ModelHandle);
	UpdateModel(GetTransformInstance());
	MakeSmallerCollision();

	// �J�v�Z���̍X�V
	Set(Position);

	// �ړ��x�N�g���̏�����
	m_moveVec = 0;
}

void MainActor::Draw() const
{
	// ���f���̕`��
	DrawModel();

	// �J�v�Z���̃e�X�g�`��
	DrawCapsule();
}

void MainActor::Control(Vec3 angle)
{
	// �C���v�b�g�̃C���X�^���X���擾
	auto& input = Input::getInstance();
	if (input.GetStickVectorLength(INPUT_LEFT_STICK) > std::get<float>(input.GetConstant("STICK_INVALID_VALUE"))) {

		// �ړ��x�N�g���ɃX�e�B�b�N�̒l�����̂܂ܑ������
		m_moveVec = input.GetStickUnitVector(INPUT_LEFT_STICK);

		// �J�����ɍ��킹�ĉ�]����
		RotateAngle(angle.y);

		// ���݂̍��W�Ɉړ��x�N�g���𑫂�
		Position += m_moveVec * std::get<float>(Constants["WALK_SPEED"]);
	}
}

void MainActor::MakeSmallerCollision()
{
	// �ړ������ǂ������肷��
	if (m_moveVec.Length() == 0.0f) {
		// �ړ����Ă��Ȃ�
		SetHeight(5.0f);
	}
	else {
		SetHeight(10.0f);
	}
}

void MainActor::AnimationControl()
{
	if (m_moveVec.Length() == 0.0f) {
		ChangeAnimation(ModelHandle, std::get<int>(Constants["ANIM_CROUCH"]), true, 0.05f);
	}
	else if (m_moveVec.Length() != 0.0f) {
		ChangeAnimation(ModelHandle, std::get<int>(Constants["ANIM_WALK"]), true, 0.15f);
	}
}

void MainActor::RotateAngle(float cameraAngle)
{
	// Y����]�s��ɕϊ�
	MATRIX rotaMtx = MGetRotY(cameraAngle);

	// �X���̕������t�Ȃ̂Ŕ��]������
	Vec3 inclination = Input::getInstance().GetStickUnitVector(INPUT_LEFT_STICK) * -1;

	// �X�e�B�b�N�̌X�����J�����ɍ��킹��Y����]������
	m_moveVec = VTransform(inclination.VGet(), rotaMtx);

	// �ړ���������̊p�x�����߂�
	Vec3 targetPos = Position + m_moveVec;
	float x = targetPos.x - Position.x;
	float z = targetPos.z - Position.z;
	float targetAngle = atan2f(x, z);
	targetAngle = targetAngle + static_cast<float>(DX_PI);
	DX_TWO_PI;

	// �ړ���������ɏ��X�ɉ�]����

	// ���W�A���p�𐳋K������
	Angle.y = fmodf(Angle.y, static_cast<float>(DX_TWO_PI));
	if (Angle.y < 0.0f) Angle.y += static_cast<float>(DX_TWO_PI);

	// �����ړ��ʂ�菬�����Ȃ�����ڕW�̒l��������
	if (fabsf(Angle.y - targetAngle) > std::get<float>(Constants["ANGLE_ROTATE_SCALE"])) {
		// ���₷�̂ƌ��炷�̂łǂ��炪�߂������f����
		float add = targetAngle - Angle.y;	// �����ꍇ�̉�]��
		if (add < 0.0f) add += static_cast<float>(DX_TWO_PI);	// �����ꍇ�̉�]�ʂ����̐��������ꍇ���K������
		float sub = static_cast<float>(DX_TWO_PI) - add;	// �����ꍇ�̉�]��

		// ��]�ʂ��ׂď��Ȃ�����I������
		if (add < sub) {
			Angle.y += std::get<float>(Constants["ANGLE_ROTATE_SCALE"]);
		}
		else {
			Angle.y -= std::get<float>(Constants["ANGLE_ROTATE_SCALE"]);
		}

		// �����ɂ���Ĕ͈͊O�ɂȂ����ꍇ�̐��K��
		Angle.y = fmodf(Angle.y, static_cast<float>(DX_TWO_PI));
		if (Angle.y < 0.0f) Angle.y += static_cast<float>(DX_TWO_PI);
	}
	else {
		Angle.y = targetAngle;
	}
}
