#include "Camera.h"
#include <cassert>
#include "StaticFunction.h"
#include "Input.h"

Camera::~Camera()
{
}

void Camera::Init(Vec3 pos)
{
	// 外部ファイルから定数を取得する
	assert(Function::ConstantsFileLoad("data/constant/Camera.csv", Constants) == 1);

	// カメラのニアファーの設定
	SetCameraNearFar(Constants["CAMERA_NEAR"], Constants["CAMERA_FAR"]);

	Position = Vec3{ pos.x + Constants["CAMERA_BASE_POS_X"],pos.y + Constants["CAMERA_BASE_POS_Y"], pos.z + Constants["CAMERA_BASE_POS_Z"], };
}

void Camera::Update(Vec3 pos)
{
	(this->*m_modeFunc)(pos);
}

void Camera::BrutusMode(Vec3 pos)
{
	// 回転
	RotateBrutus(pos);

	// カメラの位置をセットする
	SetCameraPositionAndTarget_UpVecY(Position.VGet(), VECTOR{ pos.x,Constants["CAMERA_MARGIN_Y"],pos.z });
}

void Camera::OsMode(Vec3 pos)
{
}

void Camera::RotateBrutus(Vec3 pos)
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

	// 回転行列を作成
	MATRIX rotMtxX, rotMtxZ;
	rotMtxX = MGetRotY(Angle.y);
	rotMtxZ = MGetRotX(Angle.z);


	// 基準座標を行列で変換
	basePos = VTransform(basePos, rotMtxZ);
	basePos = VTransform(basePos, rotMtxX);

	// カメラ座標はプレイヤー座標から変換した座標を足したところ
	Position = VAdd(VGet(pos.x, 0.0f, pos.z), basePos);
}

void Camera::ChangeMode(bool osFlug)
{
	// フラグがtrueのときはオズモードに変更
	if (osFlug) {
		m_modeFunc = &Camera::OsMode;
	}
	else {
		m_modeFunc = &Camera::BrutusMode;
	}
}
