#pragma once
#include "CharactorBase.h"

class Brutus:
	public CharactorBase
{
public:
	Brutus();
	~Brutus();

	void Update();
	void Draw() const;

	void Control();
private:

};

