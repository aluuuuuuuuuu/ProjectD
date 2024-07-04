#pragma once
#include "Components.h"

class StaticObject
{
public:
	StaticObject(Vec3 pos,Vec3 Scale,float angle,int model,int texture);
	~StaticObject();

	void Update();
	void Draw() const;
private:
	Transform m_transform;
	Model m_model;
	
};

