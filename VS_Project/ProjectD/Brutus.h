#pragma once
#include "Constant.h"
#include "Components.h"

class Brutus:
	public Constant,
	public Transform
{
public:
	Brutus();
	~Brutus();

	void Update();
	void Draw() const;

	void Control();
private:

};

