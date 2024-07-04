#pragma once
#include <memory>

class Brutus;
class Os;
// �v���C���[�N���X
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

