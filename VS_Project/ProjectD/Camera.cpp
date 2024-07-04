#include "Camera.h"
#include <cassert>
#include "StaticFunction.h"

Camera::Camera() 
{
	// 外部ファイルから定数を取得する
	assert(Function::ConstantsFileLoad("data/constant/Camera.csv", Constants) == 1);

	// カメラのニアファーの設定
	SetCameraNearFar(Constants["CAMERA_NEAR"], Constants["CAMERA_FAR"]);
}

Camera::~Camera()
{
}

void Camera::Init()
{
	Position = Vec3{};
}

void Camera::Update()
{
}
