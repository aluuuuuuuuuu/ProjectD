#include "Brutus.h"
#include "DxLib.h"

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
	DrawSphere3D(Position.VGet(), 16, 16, 0x0000ff, 0x0000ff, true);
}
