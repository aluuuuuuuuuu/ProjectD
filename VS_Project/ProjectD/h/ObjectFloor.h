#pragma once
#include "StaticObjectBase.h"

class ObjectFloor:
	public StaticObjectBase
{
public:
	ObjectFloor(int modelHandle);
	virtual ~ObjectFloor();

	void Draw() const;
};

