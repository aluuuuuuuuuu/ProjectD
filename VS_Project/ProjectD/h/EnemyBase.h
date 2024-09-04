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

	// 死亡フラグを立てる
	void SetDeadFlag();

	// 死亡処理スタートフラグを立てる
	void SetStartDeadFlag();

	// 死亡フラグを得る
	bool GetDeadFlag();
private:

	// 死亡フラグ
	bool m_deadFlag = false;

	// 死亡処理開始フラグ
	bool m_startDeadFlag = false;
};

