#include "Camera.h"
#include <cassert>
#include "StaticFunction.h"

Camera::Camera() 
{
	// �O���t�@�C������萔���擾����
	assert(Function::ConstantsFileLoad("data/constant/Camera.csv", Constants) == 1);

	// �J�����̃j�A�t�@�[�̐ݒ�
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
