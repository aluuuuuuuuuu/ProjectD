#pragma once
#include <memory>

class Brutus;
class Os;
// プレイヤークラス
class Player
{
public:
	Player();
	~Player();

	void Update();
	void Draw();
private:
	std::shared_ptr<Brutus> m_pBrutus;
	std::shared_ptr<Os> m_pOs;
};

