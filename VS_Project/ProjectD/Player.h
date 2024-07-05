#pragma once
#include <memory>
#include "Vec3.h"

class Brutus;
class Os;
// �v���C���[�N���X
class Player
{
public:
	Player();
	~Player();

	void Update();
	void Draw() const;

	Vec3 GetPos() const;
private:

	// �u���[�^�X�ƃI�Y�̃|�C���^
	std::shared_ptr<Brutus> m_pBrutus;
	std::shared_ptr<Os> m_pOs;

	// �I�Y�𑀍삵�Ă��邩�ǂ���
	bool m_osFlug;
};

