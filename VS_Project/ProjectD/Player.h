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

	// ブルータスとオズのポインタ
	std::shared_ptr<Brutus> m_pBrutus;
	std::shared_ptr<Os> m_pOs;

	// オズを操作しているかどうか
	bool m_osFlug;
};

