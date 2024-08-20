#pragma once
#include "Components.h"

class StaticObjectBase :
	public Transform,
	public Model
{
public:
	StaticObjectBase();
	virtual ~StaticObjectBase() {};

	virtual void Draw() const = 0;
protected:
	bool m_throughFlag = false;
};

