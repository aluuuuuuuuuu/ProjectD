#pragma once
#include <memory>
#include "Vec3.h"
#include "Components.h"

class Direction;
class MainActor;
class SubActor;
class PlayerCamera;
// プレイヤークラス
class Player
{
public:
	Player(std::shared_ptr<Direction>& direction);
	~Player();

	void Update();
	void Draw() const;

	CapsuleData& GetCupsule();

	Vec3 GetPos() const;
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

	// 操作モードを変更する関数
	void ChangeMode();

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

	// 操作変更したときのカメラの位置と角度を保存する これはカメラに持たせるべきではby古川
	Vec3 m_changePos;
	Vec3 m_changeAngle;
};

