#include "Player.h"
#include "Brutus.h"
#include "Os.h"

Player::Player():

	m_osFlug(false)
{
	m_pBrutus = make_shared<Brutus>();
	m_pOs = make_shared<Os>();
}

Player::~Player()
{
}

void Player::Update()
{
	// ‘€ìØ‚è‘Ö‚¦
	if (m_osFlug) {
		m_pOs->Control();
		m_pBrutus->Update();
		m_pOs->Update();
	}
	else {
		m_pBrutus->Control();
		m_pBrutus->Update();
	}
}

void Player::Draw() const
{
	// ‘€ìØ‚è‘Ö‚¦
	if (m_osFlug) {
		m_pBrutus->Draw();
		m_pOs->Draw();
	}
	else {
		m_pBrutus->Draw();
	}
}

Vec3 Player::GetPos() const
{
	return m_pBrutus->Position;
}
