#include "Player.h"
#include "Brutus.h"
#include "Os.h"
#include "Input.h"

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
	// 操作変更ボタンが押されたらオズとブルータスの操作を変更する(現状Yボタン)
	if (Input::getInstance().IsTrigger(INPUT_Y)) {

		// 現在の操作フラグを反転する
		m_osFlug = !m_osFlug;
	}

	// 操作切り替え
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
	// 操作切り替え
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
