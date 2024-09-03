#include "Player.h"
#include "MainActor.h"
#include "SubActor.h"
#include "Input.h"
#include "PlayerCamera.h"
#include "UI.h"
#include "Direction.h"
#include "EffekseerForDXLib.h"
#include "DxLib.h"

Player::Player(std::shared_ptr<Direction>& direction) :
	m_subActorFlag(false),
	m_pDirection(direction)
{
	// 各ポインタの作成
	m_pMainActor = std::make_shared<MainActor>();
	m_pSubActor = std::make_shared<SubActor>();
	m_pCamera = std::make_shared<PlayerCamera>();

	// 関数ポインタの初期化
	m_updateMode = &Player::MainActorUpdate;
	m_drawMode = &Player::MainActorDraw;

	// カメラの初期処理
	m_pCamera->Init(GetPos());
}

Player::~Player()
{
}

void Player::Update()
{
	if (!m_pDirection->IsPlaySequ()) {

		// 操作切り替え
		(this->*m_updateMode)();

		// 操作変更ボタンが押されたらサブアクターとメインアクターとの操作を変更する(現状Yボタン)
		if (Input::getInstance().IsTrigger(INPUT_Y)) {
			// モード変更
			ChangeMode();
		}

		// カメラの更新
		m_pCamera->Update(GetPos());

	}

	// インタラクトボタンが押されたときの処理
	if (Input::getInstance().IsTrigger(INPUT_X)) {
		// インタラクト処理
		InteractFunc();
	}
}

void Player::Draw() const
{
	// 描画切り替え
	(this->*m_drawMode)();
}

Vec3 Player::GetPos() const
{
	// 操作モードによって返す値が変わる
	if (m_subActorFlag) {
		return m_pSubActor->Position;
	}
	else {
		return m_pMainActor->Position;
	}
}

void Player::CollisionMove(Vec3 vec)
{
	// 当たり判定後の座標に移動する
	m_pMainActor->Position += vec;

	// 移動した後にメインアクターのカプセルとカメラを更新する
	m_pCamera->Update(GetPos());
	m_pMainActor->Set(m_pMainActor->Position);
}

bool Player::IsSubActorControl()
{
	return m_subActorFlag;
}

CapsuleData& Player::GetCupsule()
{
	return m_pMainActor->m_data;
}

void Player::MainActorUpdate()
{
	m_pMainActor->Control(m_pCamera->Angle);
	m_pMainActor->Update();
}

void Player::MainActorDraw() const
{
	m_pMainActor->Draw();
}

void Player::SubActorUpdate()
{
	m_pSubActor->Control(m_pCamera->Angle);
	m_pMainActor->Update();
	m_pSubActor->Update();
}

void Player::SubActorDraw() const
{
	m_pMainActor->Draw();
	m_pSubActor->Draw();
}

void Player::ChangeMode()
{
	// 操作フラグを反転する
	m_subActorFlag = !m_subActorFlag;

	// 呼ばれたときのサブアクターフラグでモードを変更する
	if (m_subActorFlag) {
		m_updateMode = &Player::SubActorUpdate;
		m_drawMode = &Player::SubActorDraw;

		// サブアクターに変更するときは初期処理を呼ぶ
		m_pSubActor->ChangeInit(m_pCamera->Position, m_pMainActor->Position);

		// 変更時のカメラの位置と角度を保存しておく
		m_changePos = m_pCamera->Position;
		m_changeAngle = m_pCamera->Angle;

		// カメラのモードを変更する
		m_pCamera->ChangeMode(SUBACTOR_MODE);
	}
	else {
		m_updateMode = &Player::MainActorUpdate;
		m_drawMode = &Player::MainActorDraw;

		// メインアクターに変更するときは保存した座標にカメラを置く
		m_pCamera->Position = m_changePos;
		m_pCamera->Angle = m_changeAngle;

		// メインアクターに切り替えたとき敵に対するボタン表示をオフにする
		UI::getInstance().SetEnemyInteractFlag(false);

		// カメラのモードを変更する
		m_pCamera->ChangeMode(MAINACTOR_MODE);
	}
}

void Player::InteractFunc()
{
	// 気絶シーケンスが再生されていたらシーケンスを抜ける
	if (m_pDirection->IsPlaySequ()) {
		m_pDirection->StopSequence();
	}
	// エネミーインタラクトが可能の場合
	else if (UI::getInstance().GetEnemyInteractFlag()) {
		// 気絶させるシーケンスに入る
		m_pDirection->PlayFaintSequ(m_pCamera->Position);
		m_pDirection->SetEnemyPos(m_pSubActor->GetEnemyPos());
		// インタラクトボタンを非表示にする
		UI::getInstance().SetEnemyInteractFlag(false);
	}
}
