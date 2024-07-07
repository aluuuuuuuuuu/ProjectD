#include "Os.h"
#include "Camera.h"
#include "Input.h"
#include "DxLib.h"

Os::Os()
{
}

Os::~Os()
{
}

void Os::Update()
{
}

void Os::Draw() const
{
	DrawSphere3D(Position.VGet(), 16, 16, 0xff0000, 0xff0000, true);
}

void Os::ChangeInit()
{
	// ブルータス操作時のカメラの座標がそのままオズの初期座標になる
	Position = Camera::getInstance().Position;
}

void Os::Control()
{
	// インプットのインスタンスを取得
	auto& input = Input::getInstance();
	if (input.GetStickVectorLength(INPUT_LEFT_STICK) > input.Constants["STICK_INVALID_VALUE"]) {

		// 移動ベクトルにスティックの値をそのまま代入する
		m_moveVec = input.GetStickUnitVector(INPUT_LEFT_STICK);

		//// カメラの回転を得る
		//Angle.y = Camera::getInstance().Angle.y;

		//// Y軸回転行列に変換
		//MATRIX rotaMtx = MGetRotY(Angle.y);

		//// 傾きの方向が逆なので反転させる
		//Vec3 inclination = input.GetStickUnitVector(INPUT_LEFT_STICK) * -1;

		//// スティックの傾きをカメラに合わせてY軸回転させる
		//m_moveVec = VTransform(inclination.VGet(), rotaMtx);

		// 現在の座標に移動ベクトルを足す
		Position += m_moveVec;
	}
}
