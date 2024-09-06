#pragma once
#include "EnemyBase.h"
#include "Components.h"
#include <memory>

class StaticObjectManager;
class Player;
class EnemyTest :
	public EnemyBase
{
public:
	EnemyTest(Vec3 pos, int modelhandle, std::shared_ptr<Player>& pl,std::shared_ptr<StaticObjectManager>& obj);
	virtual ~EnemyTest();

	void Update();
	void Draw() const;

private:

	// プレイヤーを認識したか
	bool IsPlayerDetected();

	// プレイヤーが一定の距離内にいるか
	bool IsPlayerInRange();

	// プレイヤーが視覚内にいるか
	bool IsPlayerInSight();

	// プレイヤーとの間に障害物があるか
	bool IsPlayerObstructed();

	// プレイヤーが触れるほどの距離にいるか
	bool IsPlayerWithinReach();

	// プレイヤーの参照
	std::shared_ptr<Player>& m_pPlayer;

	// スタティックオブジェクトマネージャーの参照
	std::shared_ptr<StaticObjectManager>& m_pObject;


























	// アニメーション

	// アニメーション初期処理
	void InitAnimation(int tag, float rate);

	// アニメーション更新処理
	void UpdateAnimation();

	// アニメーション変更
	void ChangeAnimation(int tag, bool loop, float blendRate);

	// 連続でアニメを切り替えたい場合のアニメーション変更
	void ChangeAnimationConnect(int tag1, int tag2, float rate1, float rate2);

	// アニメーション終了フラグを返す
	bool GetEndAnimFlag();

	// 現行のアニメーションタグを返す
	int GetAnimTag();






	// アニメーション変数
	// デフォルトのブレンドレート
	float m_defaultRate = 0.0f;

	// コネクト先のブレンドレートを保存する
	float m_rate2 = 0.0f;

	// ブレンドレート
	float m_blendRateSave = 0.0f;

	// 再生時間
	float m_flameCount = 0.0f;

	// 総フレーム数
	float m_maxFlame = 0.0f;

	// アニメーションインデックス
	int m_attachIndex1 = 0;
	int m_attachIndex2 = 0;

	// 再生中のアニメーション
	int m_playAnimation = 0;

	// 連続で再生するアニメーション
	std::vector<int> m_connectAnimation;

	// 連続で再生するアニメーションの進行状況
	int m_animationState = 0;

	// 現行のアニメーションタグ
	int m_runTag = 0;

	// ループ再生フラグ
	bool m_loopFlag = false;

	// デフォルトアニメーションタグ
	int m_defaultTag = 0;

	// アニメーションコネクトフラグ
	bool m_connectFlag = false;

	// アニメーションブレンドレート
	float m_blendRate = 0.0f;

	// アニメーション終了フラグ
	bool m_endAnimFlag = true;


};

