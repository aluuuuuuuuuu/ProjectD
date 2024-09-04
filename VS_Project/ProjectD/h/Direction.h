#pragma once
#include "Vec3.h"
#include <memory>
#include "Constant.h"

struct tama
{
	Vec3 pos;
	Vec3 moveVec;

	float length;
};

class EnemyBase;
class DirectionCamera;
class Direction:
	public Constant
{
public:
	Direction();
	virtual ~Direction();

	void Init();
	void Update();
	void Draw();

	// 気絶シーケンスを再生する
	void PlayFaintSequ(Vec3 cameraPos);

	// 気絶させる敵のポインタをセットする
	void SetEnemyPtr(std::shared_ptr<EnemyBase> enemy);

	// シーケンスを抜ける
	void StopSequence();

	// シーケンスが再生中であるか
	bool IsPlaySequ();

	// 気絶させたかどうか
	bool IsFaintEnemy();
private:

	// 関数ポインタ
	using m_updateFunc_t = void (Direction::*)();
	using m_drawFunc_t = void (Direction::*)() const;
	m_updateFunc_t m_updateFunc = nullptr;
	m_drawFunc_t m_drawFunc = nullptr;

	// null
	void NullUpdate();
	void NullDraw() const;

	// 気絶シーケンス処理
	void FaintUpdate();
	void FaintDraw() const;

	// ディレクションカメラのポインタ
	std::shared_ptr<DirectionCamera> m_pCamera;

	// ディレクションを再生するフラグ
	bool m_playFlag = false;

	// 気絶させる敵のポインタ
	std::shared_ptr<EnemyBase> m_enemyPtr;

	// 右の玉
	tama m_right;

	// 左の弾
	tama m_left;

	// 目標地点
	Vec3 m_target;

	// 気絶させたフラグ
	bool m_faintFlag;

	// フレームカウンタ
	int m_flame;
};

