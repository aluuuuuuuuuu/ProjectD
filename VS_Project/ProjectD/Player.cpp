#include "Player.h"
#include "DxLib.h"

Player::Player()
{
	// ‰ŠúˆÊ’u‚Ìİ’è
	Position = Vec3{ 0.0f,0.0f,0.0f };
}

Player::~Player()
{
}

void Player::Update()
{
}

void Player::Draw() const
{
	DrawSphere3D(Position.VGet(), 16, 16, 0xff0000, 0xff0000, true);
}
