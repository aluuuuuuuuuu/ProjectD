#include "MainActor.h"
#include "DxLib.h"
#include "Input.h"
#include <cassert>

MainActor::MainActor()
{
	// �O���t�@�C������萔���擾����
	assert(ConstantsFileLoad("data/constant/MainActor.csv", Constants) == 1);

	// �����ʒu�̐ݒ�
	Position = Vec3{ 0.0f,0.0f,0.0f };

	// �g��̐ݒ�
	Scale = Vec3{ 0.2f,0.2f,0.2f };

	// ���f���̏�������
	InitModel(MV1LoadModel("data/model/MainActor.mv1"));

	// �A�j���[�V�����̏�������
	InitAnimation(ModelHandle, Constants["ANIM_IDLE"], 0.15);
}

MainActor::~MainActor()
{
}

void MainActor::Update()
{
	ChangeAnimation();
	UpdateAnimation(ModelHandle);
	UpdateModel(GetTransformInstance());

	// �ړ��x�N�g���̏�����
	m_moveVec = 0;
}

void MainActor::Draw() const
{
	DrawModel();

}

void MainActor::Control(Vec3 angle)
{
	// �C���v�b�g�̃C���X�^���X���擾
	auto& input = Input::getInstance();
	if (input.GetStickVectorLength(INPUT_LEFT_STICK) > input.Constants["STICK_INVALID_VALUE"]) {

		// �ړ��x�N�g���ɃX�e�B�b�N�̒l�����̂܂ܑ������
		m_moveVec = input.GetStickUnitVector(INPUT_LEFT_STICK);

		// �J�����ɍ��킹�ĉ�]����
		RotateAngle(angle.y);

		// ���݂̍��W�Ɉړ��x�N�g���𑫂�
		Position += m_moveVec * Constants["WALK_SPEED"];
	}
}

void MainActor::ChangeAnimation()
{
	if (m_moveVec.Length() == 0.0f) {
		Animation::ChangeAnimation(ModelHandle, Constants["ANIM_CROUCH"], true, 0.05);
	}
	else if (m_moveVec.Length() != 0.0f) {
		Animation::ChangeAnimation(ModelHandle, Constants["ANIM_WALK"], true, 0.15f);
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

	// �ړ���������ɏ��X�ɉ�]����

	// ���g��Y���̉�]�l���R�U�O�x���Ɏ��߂�
	Angle.y = fmodf(Angle.y, 360.0f);



	//// ������x�܂ŉ�]������҂�����ƍ��킹��
	//if (abs(Angle.y - targetAngle) > 0.01f) {
	//	Angle.y -= 0.1f;
	//	//// ���₷�̂ƌ��炷�̂łǂ��炪�߂������f����
	//	//float add = abs(Angle.y + targetAngle);
	//	//float sub = abs(Angle.y - targetAngle);

	//	//if (add > sub) {
	//	//	Angle.y -= 0.1f;//
	//	//}
	//	//else {
	//	//	Angle.y += 0.1f;
	//	//}
	//}
	//else {
	//	Angle.y = targetAngle;
	//}
}
