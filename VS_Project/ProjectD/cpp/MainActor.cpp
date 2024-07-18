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
	InitAnimation(ModelHandle, Constants["ANIM_IDLE"]);
}

MainActor::~MainActor()
{
}

void MainActor::Update()
{
	UpdateAnimation(ModelHandle);
	UpdateModel(GetTransformInstance());
}

void MainActor::Draw() const
{
	DrawModel();
	//DrawSphere3D(Position.VGet(), 8, 16, 0x0000ff, 0x0000ff, true);
}

void MainActor::Control(Vec3 angle)
{
	// �C���v�b�g�̃C���X�^���X���擾
	auto& input = Input::getInstance();
	if (input.GetStickVectorLength(INPUT_LEFT_STICK) > input.Constants["STICK_INVALID_VALUE"]) {

		// �ړ��x�N�g���ɃX�e�B�b�N�̒l�����̂܂ܑ������
		m_moveVec = input.GetStickUnitVector(INPUT_LEFT_STICK);

		// �J�����̉�]�𓾂�
		Angle.y = angle.y;

		// Y����]�s��ɕϊ�
		MATRIX rotaMtx = MGetRotY(Angle.y);

		// �X���̕������t�Ȃ̂Ŕ��]������
		Vec3 inclination = input.GetStickUnitVector(INPUT_LEFT_STICK) * -1;

		// �X�e�B�b�N�̌X�����J�����ɍ��킹��Y����]������
		m_moveVec = VTransform(inclination.VGet(), rotaMtx);

		// ���݂̍��W�Ɉړ��x�N�g���𑫂�
		Position += m_moveVec;
	}
}
