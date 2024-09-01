#pragma once
#include "StaticObjectBase.h"

class ObjectFloor:
	public StaticObjectBase
{
public:
	ObjectFloor(int modelHandle, Vec3 pos);
	virtual ~ObjectFloor();

	void Draw() const;
};

