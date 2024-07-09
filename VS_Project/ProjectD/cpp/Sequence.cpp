#include "Sequence.h"

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
}

void Sequence::FaintDraw() const
{
}
