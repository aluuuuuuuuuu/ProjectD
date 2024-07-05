#pragma once
#include "Components.h"
#include "Singleton.h"
#include "Constant.h"

// カメラクラス
class Camera :
	public Transform,
	public Constant,
	public Singleton<Camera>
{
	friend class Singleton<Camera>;

public:
	~Camera();

	void Init();
	void Update(Vec3 pos);

private:
	Camera() {};

	// 回転
	void Rotate(Vec3 pos);

	// 動く前の座標
	Vec3 m_beforePos;
};

