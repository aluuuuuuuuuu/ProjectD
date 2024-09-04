#pragma once
#include "CharactorBase.h"
#include "Components.h"
#include "Constant.h"

class EnemyBase:
	//public CharactorBase
	public Constant,
	public Transform,
	public Model
{
public:
	virtual void Update() = 0;
	virtual void Draw() const = 0;

	// ���S�t���O�𗧂Ă�
	void SetDeadFlag();

	// ���S�����X�^�[�g�t���O�𗧂Ă�
	void SetStartDeadFlag();

	// ���S�t���O�𓾂�
	bool GetDeadFlag();
private:

	// ���S�t���O
	bool m_deadFlag = false;

	// ���S�����J�n�t���O
	bool m_startDeadFlag = false;
};

