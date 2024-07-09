#pragma once
#include "Constant.h"
#include "Components.h"

class CharactorBase:
	public Constant,
	public Transform
{
protected:

	// ˆÚ“®ƒxƒNƒgƒ‹
	Vec3 m_moveVec;
};

