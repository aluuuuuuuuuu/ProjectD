#pragma once
#include <memory>
#include "Vec3.h"
#include <list>
#include "Components.h"

class EnemyBase;
class Direction;
class MainActor;
class SubActor;
class PlayerCamera;
// プレイヤークラス
class Player
{
public:
	Player(std::shared_ptr<Direction>& direction, std::list<std::shared_ptr<EnemyBase>>& enemy);
	~Player();

	void Update();
	void Draw() const;

	CapsuleData& GetCupsule();

	Vec3 GetPos() const;

	// 当たり判定後の移動ベクトルを受け取って反映させる
	void CollisionMove(Vec3 vec);

	// 現在サブアクターを操作しているかどうか
	bool IsSubActorControl();

	// 操作モードを変更する関数
	void ChangeMode();

private:

	// 関数ポインタ
	using m_updateMode_t = void (Player::*)();
	using m_drawMode_t = void (Player::*)() const;
	m_updateMode_t m_updateMode = nullptr;
	m_drawMode_t m_drawMode = nullptr;

	// 操作モード
	void MainActorUpdate();	// メインアクター操作時の更新処理
	void MainActorDraw() const;		// メインアクター操作時の描画処理

	void SubActorUpdate();	// サブアクター操作時の更新処理
	void SubActorDraw() const;		// サブアクター操作時の描画処理

	// インタラクトボタンが押されたときの処理
	void InteractFunc();

	// メインアクターとサブアクターのポインタ
	std::shared_ptr<MainActor> m_pMainActor;
	std::shared_ptr<SubActor> m_pSubActor;

	// カメラのポインタ
	std::shared_ptr<PlayerCamera> m_pCamera;

	// ディレクションの参照
	std::shared_ptr<Direction> m_pDirection;

	// サブアクターを操作しているかどうか
	bool m_subActorFlag;

	// メインアクターの
};

