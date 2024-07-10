#pragma once
#include "Singleton.h"
#include "Vec3.h"

class Sequence :
	public Singleton<Sequence>
{
	friend class Singleton<Sequence>;

public:
	void Init();
	void Update();
	void Draw();

	// 気絶シーケンスを再生する
	void PlayFaintSequ();

	// 気絶させる敵の座標をセットする
	void SetEnemyPos(Vec3 pos);

	// シーケンスを抜ける
	void StopSequence();

	// シーケンスが再生中であるか
	bool IsPlaySequ();

private:
	// プライベートコンストラクタ
	Sequence() {};

	// 関数ポインタ
	using m_updateFunc_t = void (Sequence::*)();
	using m_drawFunc_t = void (Sequence::*)() const;
	m_updateFunc_t m_updateFunc = nullptr;
	m_drawFunc_t m_drawFunc = nullptr;

	// null
	void NullUpdate();
	void NullDraw() const;

	// 気絶シーケンス処理
	void FaintUpdate();
	void FaintDraw() const;

	// シーケンスを再生するフラグ
	bool m_playFlag = false;

	// 気絶させる敵の座標
	Vec3 m_enemyPos;
};

