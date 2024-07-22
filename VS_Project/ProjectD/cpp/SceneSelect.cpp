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
	m_flameLeft(0),
	m_flameRight(0)
{
	// 外部ファイルから定数を取得する
	assert(ConstantsFileLoad("data/constant/SceneSelect.csv", Constants) == 1);

	m_effectHandle = LoadEffekseerEffect("data/effect/string.efkefc.efk", 1.0f);

	g = LoadGraph("data/image/名称未設定 1.png");

	// 背景色の設定
	SetBackgroundColor(240, 240, 240);

	// 関数ポインタの初期化
	m_updateFunc = &SceneSelect::FadeInUpdate;
	m_drawFunc = &SceneSelect::FadeDraw;
}

SceneSelect::~SceneSelect()
{
}

void SceneSelect::Update()
{
	(this->*m_updateFunc)();
}

void SceneSelect::Draw() const
{
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

	//DrawRotaGraph(0, 0, 1.0, 0.0, g, true);
	DrawGraph(0, 0, g, true);
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
	StageSelectTrigger();

	// 左右ボタン長押しで選択ステージを切り替える
	StageSelectHold();
}

void SceneSelect::StageSelectTrigger()
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

void SceneSelect::StageSelectHold()
{
	// 左右ボタン長押しで連続で選択ステージを切り替える
	if (Input::getInstance().IsHold(INPUT_LEFT)) {
		m_flameLeft++;

		// 一定フレーム長押ししたら連続でステージを切り替える
		if (m_flameLeft >= Constants["FLAME_BUTTON_HOLD"]) {
			if (m_flameLeft % static_cast<int>(Constants["FLAME_LHS_NUM"]) == 0) {
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
		m_flameLeft = 0;
	}

	// 左右ボタン長押しで連続で選択ステージを切り替える
	if (Input::getInstance().IsHold(INPUT_RIGHT)) {
		m_flameRight++;

		// 一定フレーム長押ししたら連続でステージを切り替える
		if (m_flameRight >= Constants["FLAME_BUTTON_HOLD"]) {
			if (m_flameRight % static_cast<int>(Constants["FLAME_LHS_NUM"]) == 0) {
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
		m_flameRight = 0;
	}
}
