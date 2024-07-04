#include "Player.h"
#include "Brutus.h"
#include "Os.h"

Player::Player()
{
	m_pBrutus = make_shared<Brutus>();
	m_pOs = make_shared<Os>();
}

Player::~Player()
{
}

void Player::Update()
{
}

void Player::Draw()
{
}
