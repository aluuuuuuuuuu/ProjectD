#pragma once
#include "Components.h"
#include "Singleton.h"

class Camera :
	public Transform
{
	friend class Singleton<Camera>;

public:
	~Camera();

	void Update();

private:

};

