#pragma once
#include "Constant.h"
#include "Components.h"

class CharactorBase:
	public Constant,
	public Transform
{
protected:

	// 移動ベクトル
	Vec3 m_moveVec;
};

