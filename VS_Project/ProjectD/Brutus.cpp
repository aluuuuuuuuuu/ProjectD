#include "Brutus.h"
#include "DxLib.h"
#include "Input.h"

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

	}
}
