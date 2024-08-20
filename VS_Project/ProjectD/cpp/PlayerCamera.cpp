#include "PlayerCamera.h"
#include <cassert>
#include "Input.h"

PlayerCamera::PlayerCamera()
{
    // 外部ファイルから定数を取得する
    assert(ConstantsFileLoad("data/constant/PlayerCamera.csv", Constants) == 1);

	// カメラのニアファーの設定
	SetCameraNearFar(Constants["CAMERA_NEAR"], Constants["CAMERA_FAR"]);

	// モードの初期化
	m_modeFunc = &PlayerCamera::MainActorMode;

	// ライトのカラーを調整する
	SetLightDifColor(GetColorF(0.8f, 0.8f, 0.8f, 0.0f));
}

PlayerCamera::~PlayerCamera()
{
}

void PlayerCamera::Init(Vec3 pos)
{
	// 初期位置に設定する
	Position = Vec3{ pos.x + Constants["CAMERA_BASE_POS_X"],pos.y + Constants["CAMERA_BASE_POS_Y"], pos.z + Constants["CAMERA_BASE_POS_Z"], };
}

void PlayerCamera::Update(Vec3 pos)
{
	(this->*m_modeFunc)(pos);

	// ライトの回転
	// 基準となるターゲットの座標
	VECTOR basePos = VGet(Constants["CAMERA_TARGET_POS_X"], Constants["CAMERA_TARGET_POS_Y"], Constants["CAMERA_TARGET_POS_Z"]);

	SetLightDirection(MakeBasePos(basePos));
}

void PlayerCamera::ChangeMode(int mode)
{
	// 引数によってモードを変更する
	if (mode == SUBACTOR_MODE) {
		m_modeFunc = &PlayerCamera::SubActorMode;
		return;
	}
	if (mode == MAINACTOR_MODE) {
		m_modeFunc = &PlayerCamera::MainActorMode;
		return;
	}
}

void PlayerCamera::MainActorMode(Vec3 pos)
{
	// 回転
	Position =  RotateMainActorMode(pos);

	// カメラの位置をセットする
	SetCameraPositionAndTarget_UpVecY(Position.VGet(), VECTOR{ pos.x,Constants["CAMERA_MARGIN_Y"],pos.z });
}

void PlayerCamera::SubActorMode(Vec3 pos)
{
	// 座標をサブアクターの位置に合わせる
	Position = pos;

	// カメラの位置をセットする
	SetCameraPositionAndTarget_UpVecY(Position.VGet(), RotateSubActorMode(pos).VGet());
}

Vec3 PlayerCamera::RotateMainActorMode(Vec3 pos)
{
	// インプットのインスタンスを取得
	auto& input = Input::getInstance();

	// 右スティックで回転
	if (input.GetStickVectorLength(INPUT_RIGHT_STICK) > input.Constants["STICK_INVALID_VALUE"]) {

		// スティックを傾けた方向の回転の値を増減させる
		if (input.GetStickVector(INPUT_RIGHT_STICK).x != 0) {
			Angle.y += Constants["CAMERA_ANGLE_VARIATION"] * (input.GetStickThumbX(INPUT_RIGHT_STICK));
		}
		if (input.GetStickVector(INPUT_RIGHT_STICK).z != 0) {
			Angle.z += Constants["CAMERA_ANGLE_VARIATION"] * (input.GetStickThumbY(INPUT_RIGHT_STICK));
		}
	}

	// 最大値と最低値を調整する
	if (Angle.z <= -Constants["CAMERA_ANGLE_RANGE"]) {
		Angle.z = -Constants["CAMERA_ANGLE_RANGE"];
	}
	else if (Angle.z >= Constants["CAMERA_ANGLE_RANGE"]) {
		Angle.z = Constants["CAMERA_ANGLE_RANGE"];
	}

	// 基準となるカメラの座標
	VECTOR basePos = VGet(Constants["CAMERA_BASE_POS_X"], Constants["CAMERA_BASE_POS_Y"], Constants["CAMERA_BASE_POS_Z"]);

	// カメラ座標はプレイヤー座標から変換した座標を足したところ
	return VAdd(VGet(pos.x, 0.0f, pos.z), MakeBasePos(basePos));
}

Vec3 PlayerCamera::RotateSubActorMode(Vec3 pos)
{
	// インプットのインスタンスを取得
	auto& input = Input::getInstance();

	// 右スティックで回転
	if (input.GetStickVectorLength(INPUT_RIGHT_STICK) > input.Constants["STICK_INVALID_VALUE"]) {

		// スティックを傾けた方向の回転の値を増減させる
		if (input.GetStickVector(INPUT_RIGHT_STICK).x != 0) {
			Angle.y += Constants["CAMERA_ANGLE_VARIATION"] * (input.GetStickThumbX(INPUT_RIGHT_STICK));
		}
		if (input.GetStickVector(INPUT_RIGHT_STICK).z != 0) {
			Angle.z += Constants["CAMERA_ANGLE_VARIATION"] * (input.GetStickThumbY(INPUT_RIGHT_STICK));
		}
	}

	// 最大値と最低値を調整する
	if (Angle.z <= -Constants["CAMERA_ANGLE_RANGE"]) {
		Angle.z = -Constants["CAMERA_ANGLE_RANGE"];
	}
	else if (Angle.z >= Constants["CAMERA_ANGLE_RANGE"]) {
		Angle.z = Constants["CAMERA_ANGLE_RANGE"];
	}

	// 基準となるターゲットの座標
	VECTOR basePos = VGet(Constants["CAMERA_TARGET_POS_X"], Constants["CAMERA_TARGET_POS_Y"], Constants["CAMERA_TARGET_POS_Z"]);

	// ターゲット座標はカメラ座標から変換した座標を足したところ
	return VAdd(Position.VGet(), MakeBasePos(basePos));
}

VECTOR PlayerCamera::MakeBasePos(VECTOR base)
{
	// 回転行列を作成
	MATRIX rotMtxX, rotMtxZ;
	rotMtxX = MGetRotY(Angle.y);
	rotMtxZ = MGetRotX(Angle.z);

	// 基準座標を行列で変換
	base = VTransform(base, rotMtxZ);
	base = VTransform(base, rotMtxX);

	return base;
}
