#include "ObjectFloor.h"
#include "DxLib.h"

ObjectFloor::ObjectFloor(int modelHandle, Vec3 pos)
{
	m_code = FLOOR_CODE;
	Position = pos;
	ModelHandle = MV1DuplicateModel(modelHandle);
	Scale = Vec3{ 1.2f,0.01f,1.2f };
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