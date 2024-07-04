#pragma once
#include "Components.h"
#include "Singleton.h"
#include "Constant.h"

// ƒJƒƒ‰ƒNƒ‰ƒX
class Camera :
	public Transform,
	Constant
{
	friend class Singleton<Camera>;

public:
	~Camera();

	void Init();
	void Update();

private:
	Camera();
};

