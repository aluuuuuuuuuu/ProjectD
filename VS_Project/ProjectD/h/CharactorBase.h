#pragma once
#include "Constant.h"
#include "Components.h"

class CharactorBase:
	public Constant,
	public Transform,
	public Model,
	public Animation
{
protected:

	// �ړ��x�N�g��
	Vec3 m_moveVec;
};

