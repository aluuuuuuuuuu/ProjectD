#include "PlayerCamera.h"
#include <cassert>
#include "Input.h"

PlayerCamera::PlayerCamera():
	m_changeFlag(false)
{
	// 外部ファイルから定数を取得する
	ReadCSV("data/constant/PlayerCamera.csv");

	// カメラのニアファーの設定
	SetCameraNearFar(std::get<float>(Constants["CAMERA_NEAR"]), std::get<float>(Constants["CAMERA_FAR"]));

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
	Position = Vec3{ pos.x + std::get<float>(Constants["CAMERA_BASE_POS_X"]),pos.y + std::get<float>(Constants["CAMERA_BASE_POS_Y"]), pos.z + std::get<float>(Constants["CAMERA_BASE_POS_Z"]), };
}

void PlayerCamera::Update(Vec3 pos)
{
	(this->*m_modeFunc)(pos);

	// ライトの回転
	// 基準となるターゲットの座標
	VECTOR basePos = VGet(std::get<float>(Constants["CAMERA_TARGET_POS_X"]), std::get<float>(Constants["CAMERA_TARGET_POS_Y"]), std::get<float>(Constants["CAMERA_TARGET_POS_Z"]));

	SetLightDirection(MakeBasePos(basePos));
}

void PlayerCamera::ChangeMode(int mode, Vec3 pos)
{
	// 引数によってモードを変更する
	if (mode == SUBACTOR_MODE) {

		// 即サブアクターモードに変更する
		m_modeFunc = &PlayerCamera::SubActorMode;

		// 座標を保存する
		m_savePos = Position;
		m_saveTarget = VAdd(Position.VGet(), MakeBasePos(VGet(std::get<float>(Constants["CAMERA_TARGET_POS_X"]), std::get<float>(Constants["CAMERA_TARGET_POS_Y"]), std::get<float>(Constants["CAMERA_TARGET_POS_Z"]))));
		m_saveAngle = Angle;
		return;
	}
	if (mode == MAINACTOR_MODE) {

		// 切り替え中フラグを立てる
		m_changeFlag = true;

		// 保存した座標に移動する処理に移る
		m_modeFunc = &PlayerCamera::ChangeMainActorMode;

		// 元居た座標への単位ベクトルを作成する
		m_unitPos = (m_savePos - Position).GetNormalized();

		// 現在のターゲットを求める
		m_target = VAdd(Position.VGet(), MakeBasePos(VGet(std::get<float>(Constants["CAMERA_TARGET_POS_X"]), std::get<float>(Constants["CAMERA_TARGET_POS_Y"]), std::get<float>(Constants["CAMERA_TARGET_POS_Z"]))));

		// 現在のターゲットからメインアクターに向かうターゲットへの単位ベクトルを作成する
		m_unitTarget = (Vec3{ pos.x,std::get<float>(Constants["CAMERA_MARGIN_Y"]),pos.z } - m_target).GetNormalized();

		return;
	}
}

bool PlayerCamera::IsModeChange()
{
	return m_changeFlag;
}

void PlayerCamera::MainActorMode(Vec3 pos)
{
	// 回転
	Position = RotateMainActorMode(pos);

	// カメラの位置をセットする
	SetCameraPositionAndTarget_UpVecY(Position.VGet(), VECTOR{ pos.x,std::get<float>(Constants["CAMERA_MARGIN_Y"]),pos.z });
}

void PlayerCamera::SubActorMode(Vec3 pos)
{
	// 座標をサブアクターの位置に合わせる
	Position = pos;

	// カメラの位置をセットする
	SetCameraPositionAndTarget_UpVecY(Position.VGet(), RotateSubActorMode(pos).VGet());
}

void PlayerCamera::ChangeMainActorMode(Vec3 pos)
{
	bool a  = false;
	bool b = false;
	if ((Vec3{ pos.x,std::get<float>(Constants["CAMERA_MARGIN_Y"]),pos.z } - m_target).Length() > 2.0f) {
		// 単位ベクトルの方向にターゲットを移動する
		m_target += m_unitTarget * std::get<float>(Constants["CAMERA_TARGET_MOVE_SCALE"]);
	}
	else {
		a = true;
	}
	if ((Position - m_savePos).Length() > 5.0f) {
		// 単位ベクトルの方向に一定の速度で移動する
		Position += m_unitPos * std::get<float>(Constants["CAMERA_MOVE_SCALE"]);
	}
	else {
		b = true;
	}

	// カメラの位置をセットする
	SetCameraPositionAndTarget_UpVecY(Position.VGet(), m_target.VGet());

	// 座標とターゲットがどちらも目標に到達したらメインアクターモードに切り替える
	if (a && b) {

		// 切り替え中フラグを下げる
		m_changeFlag = false;

		// 保存したアングルにしておく
		Angle = m_saveAngle;

		// 切り替え
		m_modeFunc = &PlayerCamera::MainActorMode;
	}
}

Vec3 PlayerCamera::RotateMainActorMode(Vec3 pos)
{
	// インプットのインスタンスを取得
	auto& input = Input::getInstance();

	// 右スティックで回転
	if (input.GetStickVectorLength(INPUT_RIGHT_STICK) > std::get<float>(input.GetConstant("STICK_INVALID_VALUE"))) {

		// スティックを傾けた方向の回転の値を増減させる
		if (input.GetStickVector(INPUT_RIGHT_STICK).x != 0) {
			Angle.y += std::get<float>(Constants["CAMERA_ANGLE_VARIATION"]) * (input.GetStickThumbX(INPUT_RIGHT_STICK));
		}
		if (input.GetStickVector(INPUT_RIGHT_STICK).z != 0) {
			Angle.z += std::get<float>(Constants["CAMERA_ANGLE_VARIATION"]) * (input.GetStickThumbY(INPUT_RIGHT_STICK));
		}
	}

	// 最大値と最低値を調整する
	if (Angle.z <= -std::get<float>(Constants["CAMERA_ANGLE_RANGE"])) {
		Angle.z = -std::get<float>(Constants["CAMERA_ANGLE_RANGE"]);
	}
	else if (Angle.z >= std::get<float>(Constants["CAMERA_ANGLE_RANGE"])) {
		Angle.z = std::get<float>(Constants["CAMERA_ANGLE_RANGE"]);
	}

	// 基準となるカメラの座標
	VECTOR basePos = VGet(std::get<float>(Constants["CAMERA_BASE_POS_X"]), std::get<float>(Constants["CAMERA_BASE_POS_Y"]), std::get<float>(Constants["CAMERA_BASE_POS_Z"]));

	// カメラ座標はプレイヤー座標から変換した座標を足したところ
	return VAdd(VGet(pos.x, 0.0f, pos.z), MakeBasePos(basePos));
}

Vec3 PlayerCamera::RotateSubActorMode(Vec3 pos)
{
	// インプットのインスタンスを取得
	auto& input = Input::getInstance();

	// 右スティックで回転
	if (input.GetStickVectorLength(INPUT_RIGHT_STICK) > std::get<float>(input.GetConstant("STICK_INVALID_VALUE"))) {

		// スティックを傾けた方向の回転の値を増減させる
		if (input.GetStickVector(INPUT_RIGHT_STICK).x != 0) {
			Angle.y += std::get<float>(Constants["CAMERA_ANGLE_VARIATION"]) * (input.GetStickThumbX(INPUT_RIGHT_STICK));
		}
		if (input.GetStickVector(INPUT_RIGHT_STICK).z != 0) {
			Angle.z += std::get<float>(Constants["CAMERA_ANGLE_VARIATION"]) * (input.GetStickThumbY(INPUT_RIGHT_STICK));
		}
	}

	// 最大値と最低値を調整する
	if (Angle.z <= -std::get<float>(Constants["CAMERA_ANGLE_RANGE"])) {
		Angle.z = -std::get<float>(Constants["CAMERA_ANGLE_RANGE"]);
	}
	else if (Angle.z >= std::get<float>(Constants["CAMERA_ANGLE_RANGE"])) {
		Angle.z = std::get<float>(Constants["CAMERA_ANGLE_RANGE"]);
	}

	// 基準となるターゲットの座標
	VECTOR basePos = VGet(std::get<float>(Constants["CAMERA_TARGET_POS_X"]), std::get<float>(Constants["CAMERA_TARGET_POS_Y"]), std::get<float>(Constants["CAMERA_TARGET_POS_Z"]));

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
