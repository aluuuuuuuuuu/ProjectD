#include "Brutus.h"
#include "DxLib.h"
#include "Input.h"
#include "Camera.h"

Brutus::Brutus()
{
	// 初期位置の設定
	Position = Vec3{ 0.0f,0.0f,0.0f };
}

Brutus::~Brutus()
{
}

void Brutus::Update()
{
}

void Brutus::Draw() const
{
	DrawSphere3D(Position.VGet(), 8, 16, 0x0000ff, 0x0000ff, true);
}

void Brutus::Control()
{
	// インプットのインスタンスを取得
	auto& input = Input::getInstance();
	if (input.GetStickVectorLength(INPUT_LEFT_STICK) > input.Constants["STICK_INVALID_VALUE"]) {

		// 移動ベクトルにスティックの値をそのまま代入する
		m_moveVec = input.GetStickUnitVector(INPUT_LEFT_STICK);

		// カメラの回転を得る
		Angle.y = Camera::getInstance().Angle.y;

		// Y軸回転行列に変換
		MATRIX rotaMtx = MGetRotY(Angle.y);

		// 傾きの方向が逆なので反転させる
		Vec3 inclination = input.GetStickUnitVector(INPUT_LEFT_STICK) * -1;

		// スティックの傾きをカメラに合わせてY軸回転させる
		m_moveVec = VTransform(inclination.VGet(), rotaMtx);

		// 現在の座標に移動ベクトルを足す
		Position += m_moveVec;
	}
}
