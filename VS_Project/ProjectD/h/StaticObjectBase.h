#pragma once
#include "Components.h"

#define WALL_CODE 0
#define FLOOR_CODE 1

class StaticObjectBase :
	public Transform,
	public Model
{
public:
	StaticObjectBase();
	virtual ~StaticObjectBase() {};

	virtual void Draw() const = 0;

	// �I�u�W�F�N�g�R�[�h
	int m_code;

protected:
	bool m_throughFlag = false;
};

