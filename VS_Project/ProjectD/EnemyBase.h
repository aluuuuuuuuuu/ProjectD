#pragma once
#include "CharactorBase.h"

class EnemyBase:
	public CharactorBase
{
public:
	virtual void Update() = 0;
	virtual void Draw() const = 0;
};

