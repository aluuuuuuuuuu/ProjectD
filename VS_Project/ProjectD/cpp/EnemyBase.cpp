#include "EnemyBase.h"

void EnemyBase::SetDeadFlag()
{
	m_deadFlag = true;
}

void EnemyBase::SetStartDeadFlag()
{
	m_startDeadFlag = true;
}

bool EnemyBase::GetDeadFlag()
{
	return m_deadFlag;
}
