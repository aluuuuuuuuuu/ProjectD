#include "DirectionCamera.h"

DirectionCamera::DirectionCamera()
{
}

DirectionCamera::~DirectionCamera()
{
}

void DirectionCamera::Init()
{
}

void DirectionCamera::Update(Vec3 pos)
{
	// �J�����̃^�[�Q�b�g�^����ꂽ���W�ɕύX����
	SetCameraPositionAndTarget_UpVecY(Position.VGet(), pos.VGet());
}
