#pragma once
#include "Constant.h"
#include "Components.h"

class Player:
	public Constant,
	Transform
{
public:
	Player();
	~Player();

	void Update();
	void Draw() const;
private:

};

