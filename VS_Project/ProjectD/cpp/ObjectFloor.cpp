#include "ObjectFloor.h"
#include "DxLib.h"

ObjectFloor::ObjectFloor(int modelHandle) 
{
	ModelHandle = MV1DuplicateModel(modelHandle);
	Scale = Vec3{ 0.5f,0.01f,1.2f };
	UpdateModel(GetTransformInstance());
}

ObjectFloor::~ObjectFloor()
{
	MV1DeleteModel(ModelHandle);
}

void ObjectFloor::Draw() const
{
	// ƒ‚ƒfƒ‹‚Ì•`‰æ
	DrawModel();
}