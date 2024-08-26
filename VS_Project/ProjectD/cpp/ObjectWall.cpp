#include "ObjectWall.h"
#include "DxLib.h"

ObjectWall::ObjectWall(int modelHandle)
{
	ModelHandle = MV1DuplicateModel(modelHandle);
	Scale = 0.1f;
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
