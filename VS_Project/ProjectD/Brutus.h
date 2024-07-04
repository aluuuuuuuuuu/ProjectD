#pragma once
#include "Constant.h"
#include "Components.h"

class Brutus:
	public Constant,
	Transform
{
public:
	Brutus();
	~Brutus();

	void Update();
	void Draw() const;
private:

};

