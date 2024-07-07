#include "Os.h"
#include "Camera.h"
#include "Input.h"
#include "DxLib.h"

Os::Os()
{
}

Os::~Os()
{
}

void Os::Update()
{
}

void Os::Draw() const
{
	DrawSphere3D(Position.VGet(), 16, 16, 0xff0000, 0xff0000, true);
}

void Os::ChangeInit()
{
	// �u���[�^�X���쎞�̃J�����̍��W�����̂܂܃I�Y�̏������W�ɂȂ�
	Position = Camera::getInstance().Position;
}

void Os::Control()
{
	// �C���v�b�g�̃C���X�^���X���擾
	auto& input = Input::getInstance();
	if (input.GetStickVectorLength(INPUT_LEFT_STICK) > input.Constants["STICK_INVALID_VALUE"]) {

		// �ړ��x�N�g���ɃX�e�B�b�N�̒l�����̂܂ܑ������
		m_moveVec = input.GetStickUnitVector(INPUT_LEFT_STICK);

		//// �J�����̉�]�𓾂�
		//Angle.y = Camera::getInstance().Angle.y;

		//// Y����]�s��ɕϊ�
		//MATRIX rotaMtx = MGetRotY(Angle.y);

		//// �X���̕������t�Ȃ̂Ŕ��]������
		//Vec3 inclination = input.GetStickUnitVector(INPUT_LEFT_STICK) * -1;

		//// �X�e�B�b�N�̌X�����J�����ɍ��킹��Y����]������
		//m_moveVec = VTransform(inclination.VGet(), rotaMtx);

		// ���݂̍��W�Ɉړ��x�N�g���𑫂�
		Position += m_moveVec;
	}
}
