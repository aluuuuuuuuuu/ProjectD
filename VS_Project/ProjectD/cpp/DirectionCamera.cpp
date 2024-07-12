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
	// カメラのターゲット与えられた座標に変更する
	SetCameraPositionAndTarget_UpVecY(Position.VGet(), pos.VGet());
}
