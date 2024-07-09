#include "StaticObject.h"
#include "DxLib.h"

StaticObject::StaticObject(Vec3 pos, Vec3 Scale, float angle, int model, int texture)
{
	m_transform.Position = pos;
	m_transform.Scale = Scale;
	m_transform.Angle.y = angle;
	m_model.InitModel(MV1DuplicateModel(model),texture);

	m_model.UpdateModel(m_transform);
}

StaticObject::~StaticObject()
{
}

void StaticObject::Update()
{
	m_model.UpdateModel(m_transform);
}

void StaticObject::Draw() const
{
	m_model.DrawModel();
}