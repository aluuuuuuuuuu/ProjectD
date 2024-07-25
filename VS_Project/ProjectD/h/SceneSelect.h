#pragma once
#include "SceneBase.h"
#include "Constant.h"

// ステージ選択シーン
class SceneSelect :
	public SceneBase,
	public Constant
{
public:
	SceneSelect();
	virtual ~SceneSelect();

	void Update();
	void Draw() const;
private:
	// 関数ポインタ
	using m_updateFunc_t = void (SceneSelect::*)();
	using m_drawFunc_t = void (SceneSelect::*)() const;
	m_updateFunc_t m_updateFunc = nullptr;
	m_drawFunc_t m_drawFunc = nullptr;

	// 通常の処理
	void NormalUpdate();
	void NormalDraw() const;

	// フェード処理
	void FadeInUpdate();
	void FadeOutUpdate();
	void FadeDraw() const;

	// 選択したステージに移行する
	void ChangeScene();

	// 選択ステージを切り替える
	void StageSelect();

	// 左右ボタンで選択ステージを切り替える
	void StageSelectTriggerButton();

	// 左右ボタン長押しで選択ステージを切り替える
	void StageSelectHoldButton();

	// スティックの左右操作で選択ステージを切り替える
	void StageSelectStick();

	// フレームカウンタ
	int m_flame;

	// ボタン長押し用のフレームカウンタ
	int m_flameLeftButton;
	int m_flameRightButton;

	// スティック用のフレームカウンタ
	int m_flameLeftStick;
	int m_flameRightStick;

	// 現在選択しているステージ
	int m_stage;

	// 波の画像ハンドル
	int m_waveGraphHandle;

	// 文字の画像ハンドル
	int m_stringGraphHandle;
};

