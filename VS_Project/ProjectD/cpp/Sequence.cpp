#include "Sequence.h"
#include "DxLib.h"

void Sequence::Init()
{
	m_updateFunc = &Sequence::NullUpdate;
	m_drawFunc = &Sequence::NullDraw;
}

void Sequence::Update()
{
	(this->*m_updateFunc)();
}

void Sequence::Draw()
{
	(this->*m_drawFunc)();
}

void Sequence::PlayFaintSequ()
{
	m_updateFunc = &Sequence::FaintUpdate;
	m_drawFunc = &Sequence::FaintDraw;
	m_playFlag = true;
}

void Sequence::SetEnemyPos(Vec3 pos)
{
	m_enemyPos = pos;
}

void Sequence::StopSequence()
{
	m_updateFunc = &Sequence::NullUpdate;
	m_drawFunc = &Sequence::NullDraw;
	m_playFlag = false;
}

bool Sequence::IsPlaySequ()
{
	return m_playFlag;
}

void Sequence::NullUpdate()
{
}

void Sequence::NullDraw() const
{
}

void Sequence::FaintUpdate()
{ 
	// カメラのターゲットを敵の位置にする
	SetCameraPositionAndTarget_UpVecY(Camera::getInstance().Position.VGet(), m_enemyPos.VGet());
}

void Sequence::FaintDraw() const
{
	DrawString(10, 10, "気絶させます", 0xff0000);
}
