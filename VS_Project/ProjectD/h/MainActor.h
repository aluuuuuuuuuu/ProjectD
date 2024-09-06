#pragma once
#include "CharactorBase.h"

class MainActor:
	public CharactorBase,
	public CapsuleCollision
{
public:
	MainActor();
	~MainActor();

	void Update();
	void Draw() const;

	void Control(Vec3 angle);
private:

	// 動いていないときは当たり判定のサイズを小さくする
	void MakeSmallerCollision();

	// アニメーション変更
	void AnimationControl();

	// 移動する方向に回転する
	void RotateAngle(float cameraAngle);

};

