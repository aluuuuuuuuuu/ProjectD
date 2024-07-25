#pragma once
#include "CharactorBase.h"

class MainActor:
	public CharactorBase,
	private Model,
	private Animation
{
public:
	MainActor();
	~MainActor();

	void Update();
	void Draw() const;

	void Control(Vec3 angle);
private:

	// アニメーション変更
	void ChangeAnimation();

	// 移動する方向に回転する
	void RotateAngle(float cameraAngle);

};

