#pragma once
#include <memory>
#include "Vec3.h"

class Brutus;
class Os;
// プレイヤークラス
class Player
{
public:
	Player();
	~Player();

	void Update();
	void Draw() const;

	Vec3 GetPos() const;
private:

	// 関数ポインタ
	using m_updateMode_t = void (Player::*)();
	using m_drawMode_t = void (Player::*)() const;
	m_updateMode_t m_updateMode = nullptr;
	m_drawMode_t m_drawMode = nullptr;

	// 操作モード
	void BrutusUpdate();	// ブルータス操作時の更新処理
	void BrutusDraw() const;		// ブルータス操作時の描画処理

	void OsUpdate();	// オズ操作時の更新処理
	void OsDraw() const;		// オズ操作時の描画処理

	// 操作モードを変更する関数
	void ChangeMode();

	// ブルータスとオズのポインタ
	std::shared_ptr<Brutus> m_pBrutus;
	std::shared_ptr<Os> m_pOs;

	// オズを操作しているかどうか
	bool m_osFlug;
};

