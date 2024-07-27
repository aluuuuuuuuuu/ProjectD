#include "MainActor.h"
#include "DxLib.h"
#include "Input.h"
#include <cassert>

MainActor::MainActor()
{
	// 外部ファイルから定数を取得する
	assert(ConstantsFileLoad("data/constant/MainActor.csv", Constants) == 1);

	// 初期位置の設定
	Position = Vec3{ 0.0f,0.0f,0.0f };

	// 拡大の設定
	Scale = Vec3{ 0.2f,0.2f,0.2f };

	// モデルの初期処理
	InitModel(MV1LoadModel("data/model/MainActor.mv1"));

	// アニメーションの初期処理
	InitAnimation(ModelHandle, Constants["ANIM_IDLE"], 0.15);
}

MainActor::~MainActor()
{
}

void MainActor::Update()
{
	ChangeAnimation();
	UpdateAnimation(ModelHandle);
	UpdateModel(GetTransformInstance());

	// 移動ベクトルの初期化
	m_moveVec = 0;
}

void MainActor::Draw() const
{
	DrawModel();

}

void MainActor::Control(Vec3 angle)
{
	// インプットのインスタンスを取得
	auto& input = Input::getInstance();
	if (input.GetStickVectorLength(INPUT_LEFT_STICK) > input.Constants["STICK_INVALID_VALUE"]) {

		// 移動ベクトルにスティックの値をそのまま代入する
		m_moveVec = input.GetStickUnitVector(INPUT_LEFT_STICK);

		// カメラに合わせて回転する
		RotateAngle(angle.y);

		// 現在の座標に移動ベクトルを足す
		Position += m_moveVec * Constants["WALK_SPEED"];
	}
}

void MainActor::ChangeAnimation()
{
	if (m_moveVec.Length() == 0.0f) {
		Animation::ChangeAnimation(ModelHandle, Constants["ANIM_CROUCH"], true, 0.05);
	}
	else if (m_moveVec.Length() != 0.0f) {
		Animation::ChangeAnimation(ModelHandle, Constants["ANIM_WALK"], true, 0.15f);
	}
}

void MainActor::RotateAngle(float cameraAngle)
{
	// Y軸回転行列に変換
	MATRIX rotaMtx = MGetRotY(cameraAngle);

	// 傾きの方向が逆なので反転させる
	Vec3 inclination = Input::getInstance().GetStickUnitVector(INPUT_LEFT_STICK) * -1;

	// スティックの傾きをカメラに合わせてY軸回転させる
	m_moveVec = VTransform(inclination.VGet(), rotaMtx);

	// 移動する方向の角度を求める
	Vec3 targetPos = Position + m_moveVec;
	float x = targetPos.x - Position.x;
	float z = targetPos.z - Position.z;
	float targetAngle = atan2f(x, z);
	targetAngle = targetAngle + static_cast<float>(DX_PI);
	DX_TWO_PI;

	// 移動する方向に徐々に回転する

	// ラジアン角を正規化する
	Angle.y = fmodf(Angle.y, static_cast<float>(DX_TWO_PI));
	if (Angle.y < 0.0f) Angle.y += static_cast<float>(DX_TWO_PI);

	// 差が移動量より小さくなったら目標の値を代入する
	if (fabsf(Angle.y - targetAngle) > Constants["ANGLE_ROTATE_SCALE"]) {
		// 増やすのと減らすのでどちらが近いか判断する
		float add = targetAngle - Angle.y;	// 足す場合の回転量
		if (add < 0.0f) add += static_cast<float>(DX_TWO_PI);	// 足す場合の回転量が負の数だった場合正規化する
		float sub = static_cast<float>(DX_TWO_PI) - add;	// 引く場合の回転量

		// 回転量を比べて少ない方を選択する
		if (add < sub) {
			Angle.y += Constants["ANGLE_ROTATE_SCALE"];
		}
		else {
			Angle.y -= Constants["ANGLE_ROTATE_SCALE"];
		}

		// 増減によって範囲外になった場合の正規化
		Angle.y = fmodf(Angle.y, static_cast<float>(DX_TWO_PI));
		if (Angle.y < 0.0f) Angle.y += static_cast<float>(DX_TWO_PI);
	}
	else {
		Angle.y = targetAngle;
	}
}
