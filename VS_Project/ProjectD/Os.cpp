#include "Os.h"
#include "Camera.h"

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
}

void Os::ChangeInit()
{
	// ブルータス操作時のカメラの座標がそのままオズの初期座標になる
	Position = Camera::getInstance().Position;
}

void Os::Control()
{
}
