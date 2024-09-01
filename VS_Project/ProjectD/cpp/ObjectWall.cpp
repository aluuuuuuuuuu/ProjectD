#include "ObjectWall.h"
#include "DxLib.h"

ObjectWall::ObjectWall(int modelHandle, Vec3 pos)
{
	m_code = WALL_CODE;
	Position = pos;
	ModelHandle = MV1DuplicateModel(modelHandle);
	Scale = Vec3{ 0.01f,0.4f,0.4f };
	UpdateModel(GetTransformInstance());

}

ObjectWall::~ObjectWall()
{
	MV1DeleteModel(ModelHandle);

}

void ObjectWall::Draw() const
{
	// モデルの描画
	DrawModel();
}
