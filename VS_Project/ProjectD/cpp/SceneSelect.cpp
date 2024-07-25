#include "SceneSelect.h"
#include "DxLib.h"
#include "SceneManager.h"
#include "SceneTest.h"
#include "Input.h"
#include "EffekseerForDXLib.h"
#include <cassert>

SceneSelect::SceneSelect() :
	m_flame(60),
	m_stage(1),
	m_flameLeftButton(0),
	m_flameRightButton(0),
	m_flameLeftStick(10),
	m_flameRightStick(10)
{
	// 外部ファイルから定数を取得する
	assert(ConstantsFileLoad("data/constant/SceneSelect.csv", Constants) == 1);

	// 画像のロード
	m_waveGraphHandle = LoadGraph("data/image/string.png");
	m_stringGraphHandle = LoadGraph("data/image/SelectStage.png");

	// 背景色の設定
	SetBackgroundColor(240, 240, 240);

	// 関数ポインタの初期化
	m_updateFunc = &SceneSelect::FadeInUpdate;
	m_drawFunc = &SceneSelect::FadeDraw;
}

SceneSelect::~SceneSelect()
{
	// 画像のデリート
	DeleteGraph(m_waveGraphHandle);
	DeleteGraph(m_stringGraphHandle);
}

void SceneSelect::Update()
{
	// 更新の関数ポインタを実行
	(this->*m_updateFunc)();
}

void SceneSelect::Draw() const
{
	// 描画の関数ポインタを実行
	(this->*m_drawFunc)();
}

void SceneSelect::NormalUpdate()
{
	// Aボタンが押されたらフェードアウト処理に移行する
	if (Input::getInstance().IsTrigger(INPUT_A)) {
		m_updateFunc = &SceneSelect::FadeOutUpdate;
		m_drawFunc = &SceneSelect::FadeDraw;
	}

	// 選択ステージを切り替える
	StageSelect();
}

void SceneSelect::NormalDraw() const
{
	// テストでステージ数を表示
	DrawFormatString(20, 20, 0xff0000, "%d", m_stage);

	DrawGraph(0, 0, m_waveGraphHandle, true);

	DrawGraph(150, 900, m_stringGraphHandle, true);
}

void SceneSelect::FadeInUpdate()
{
	m_flame--;
	if (m_flame <= 0) {
		m_updateFunc = &SceneSelect::NormalUpdate;
		m_drawFunc = &SceneSelect::NormalDraw;
	}
}

void SceneSelect::FadeOutUpdate()
{
	m_flame++;
	if (m_flame >= 120) {
		ChangeScene();
	}
}

void SceneSelect::FadeDraw() const
{
	// 通常の描画も同時に行う
	NormalDraw();

	//フェード暗幕
	int alpha = (int)(255 * ((float)m_flame / 60));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 1980, 1080, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SceneSelect::ChangeScene()
{
	// 選択したステージに移行する
	if (m_stage == 1) {
		SceneManager::getInstance().ChangeScene(std::make_shared<SceneTest>());
	}
	else if (m_stage == 2) {
		SceneManager::getInstance().ChangeScene(std::make_shared<SceneTest>());
	}
	else if (m_stage == 3) {
		SceneManager::getInstance().ChangeScene(std::make_shared<SceneTest>());
	}
	else if (m_stage == 4) {
		SceneManager::getInstance().ChangeScene(std::make_shared<SceneTest>());
	}
	else if (m_stage == 5) {
		SceneManager::getInstance().ChangeScene(std::make_shared<SceneTest>());
	}
	else if (m_stage == 6) {
		SceneManager::getInstance().ChangeScene(std::make_shared<SceneTest>());
	}
	else if (m_stage == 7) {
		SceneManager::getInstance().ChangeScene(std::make_shared<SceneTest>());
	}
	else if (m_stage == 8) {
		SceneManager::getInstance().ChangeScene(std::make_shared<SceneTest>());
	}
	else if (m_stage == 9) {
		SceneManager::getInstance().ChangeScene(std::make_shared<SceneTest>());
	}
	else if (m_stage == 10) {
		SceneManager::getInstance().ChangeScene(std::make_shared<SceneTest>());
	}
}

void SceneSelect::StageSelect()
{
	// 左右ボタンで選択ステージを切り替える
	StageSelectTriggerButton();

	// 左右ボタン長押しで選択ステージを切り替える
	StageSelectHoldButton();

	// スティックの左右入力で選択ステージを切り替える
	StageSelectStick();
}

void SceneSelect::StageSelectTriggerButton()
{
	// 左右ボタンで選択ステージを切り替える
	if (Input::getInstance().IsTrigger(INPUT_LEFT)) {
		if (m_stage <= 1) {
			m_stage = static_cast<int>(Constants["MAX_STAGE_NUM"]);
		}
		else {
			m_stage--;
		}
	}
	if (Input::getInstance().IsTrigger(INPUT_RIGHT)) {
		if (m_stage >= Constants["MAX_STAGE_NUM"]) {
			m_stage = 1;
		}
		else {
			m_stage++;
		}
	}
}

void SceneSelect::StageSelectHoldButton()
{
	// 左ボタン長押しで連続で選択ステージを切り替える
	if (Input::getInstance().IsHold(INPUT_LEFT)) {
		m_flameLeftButton++;

		// 一定フレーム長押ししたら連続でステージを切り替える
		if (m_flameLeftButton >= Constants["FLAME_BUTTON_HOLD"]) {
			if (m_flameLeftButton % static_cast<int>(Constants["FLAME_LHS_NUM_BUTTON"]) == 0) {
				if (m_stage <= 1) {
					m_stage = static_cast<int>(Constants["MAX_STAGE_NUM"]);
				}
				else {
					m_stage--;
				}
			}
		}
	}
	else {
		m_flameLeftButton = 0;
	}

	// 右ボタン長押しで連続で選択ステージを切り替える
	if (Input::getInstance().IsHold(INPUT_RIGHT)) {
		m_flameRightButton++;

		// 一定フレーム長押ししたら連続でステージを切り替える
		if (m_flameRightButton >= Constants["FLAME_BUTTON_HOLD"]) {
			if (m_flameRightButton % static_cast<int>(Constants["FLAME_LHS_NUM_BUTTON"]) == 0) {
				if (m_stage >= Constants["MAX_STAGE_NUM"]) {
					m_stage = 1;
				}
				else {
					m_stage++;
				}
			}
		}
	}
	else {
		m_flameRightButton = 0;
	}
}

void SceneSelect::StageSelectStick()
{
	// 左入力で選択切り替え
	if (Input::getInstance().GetStickThumbX(INPUT_LEFT_STICK) >= Input::getInstance().Constants["STICK_INVALID_VALUE"]) {
		m_flameLeftStick++;
		if (m_flameLeftStick % static_cast<int>(Constants["FLAME_LHS_NUM_STICK"]) == 0) {
			if (m_stage >= Constants["MAX_STAGE_NUM"]) {
				m_stage = 1;
			}
			else {
				m_stage++;
			}
		}
	}
	else {
		m_flameLeftStick = 10;
	}

	// 右入力で選択切り替え
	if (Input::getInstance().GetStickThumbX(INPUT_LEFT_STICK) <= -Input::getInstance().Constants["STICK_INVALID_VALUE"]) {
		m_flameRightStick++;
		if (m_flameRightStick % static_cast<int>(Constants["FLAME_LHS_NUM_STICK"]) == 0) {
			if (m_stage >= Constants["MAX_STAGE_NUM"]) {
				m_stage = 1;
			}
			else {
				m_stage++;
			}
		}
	}
	else {
		m_flameRightStick = 10;
	}
}
