#pragma once
#include "Components.h"

class StaticObjectBase :
	public Transform,
	public Model
{
public:
	StaticObjectBase();
	virtual ~StaticObjectBase() {};

	virtual void Update() = 0;
	virtual void Draw() const = 0;
private:
	bool m_throughFlag = false;
};

