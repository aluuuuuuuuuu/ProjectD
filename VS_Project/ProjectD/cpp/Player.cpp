#include "Player.h"
#include "Brutus.h"
#include "Os.h"
#include "Input.h"
#include "Camera.h"
#include "UI.h"

Player::Player() :
	m_osFlag(false)
{
	// 各ポインタの作成
	m_pBrutus = std::make_shared<Brutus>();
	m_pOs = std::make_shared<Os>();

	// 関数ポインタの初期化
	m_updateMode = &Player::BrutusUpdate;
	m_drawMode = &Player::BrutusDraw;
}

Player::~Player()
{
}

void Player::Update()
{
	// 操作変更ボタンが押されたらオズとブルータスの操作を変更する(現状Yボタン)
	if (Input::getInstance().IsTrigger(INPUT_Y)) {
		// モード変更
		ChangeMode();
	}

	// インタラクトボタンが押されたときの処理
	if (Input::getInstance().IsTrigger(INPUT_X)) {
		// インタラクト処理
		InteractFunc();
	}

	// 操作切り替え
	(this->*m_updateMode)();
}

void Player::Draw() const
{
	// 描画切り替え
	(this->*m_drawMode)();
}

Vec3 Player::GetPos() const
{
	// 操作モードによって返す値が変わる
	if (m_osFlag) {
		return m_pOs->Position;
	}
	else {
		return m_pBrutus->Position;
	}
}

void Player::BrutusUpdate()
{
	m_pBrutus->Control();
	m_pBrutus->Update();
}

void Player::BrutusDraw() const
{
	m_pBrutus->Draw();
}

void Player::OsUpdate()
{
	m_pOs->Control();
	m_pBrutus->Update();
	m_pOs->Update();
}

void Player::OsDraw() const
{
	m_pBrutus->Draw();
	m_pOs->Draw();
}

void Player::ChangeMode()
{
	// 操作フラグを反転する
	m_osFlag = !m_osFlag;

	// 呼ばれたときのオズフラグでモードを変更する
	if (m_osFlag) {
		m_updateMode = &Player::OsUpdate;
		m_drawMode = &Player::OsDraw;

		// オズに変更するときは初期処理を呼ぶ
		m_pOs->ChangeInit(m_pBrutus->Position);

		// 変更時のカメラの位置と角度を保存しておく
		m_changePos = Camera::getInstance().Position;
		m_changeAngle = Camera::getInstance().Angle;

		// カメラのモードを変更する
		Camera::getInstance().ChangeMode(OS_MODE);
	}
	else {
		m_updateMode = &Player::BrutusUpdate;
		m_drawMode = &Player::BrutusDraw;

		// ブルータスに変更するときは保存した座標にカメラを置く
		Camera::getInstance().Position = m_changePos;
		Camera::getInstance().Angle = m_changeAngle;

		// ブルータスに切り替えたとき敵に対するボタン表示をオフにする
		UI::getInstance().SetEnemyInteractFlag(false);

		// カメラのモードを変更する
		Camera::getInstance().ChangeMode(BRUTUS_MODE);
	}
}

void Player::InteractFunc()
{
	// エネミーインタラクトが可能の場合
	if (UI::getInstance().GetEnemyInteractFlag()) {
		// 気絶させるシーケンスに入る
	}
}
