#pragma once
#include "Constant.h"
#include "Components.h"

class Os :
	public Constant,
	Transform
{
public:
	Os();
	~Os();

	void Update();
	void Draw() const;

	void Control();
private:

};