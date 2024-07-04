#pragma once
#include "Components.h"
#include "Singleton.h"
#include "Constant.h"

// カメラクラス
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

