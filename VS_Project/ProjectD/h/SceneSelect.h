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
	void StageSelectTrigger();

	// 左右ボタン長押しで選択ステージを切り替える
	void StageSelectHold();

	// フレームカウンタ
	int m_flame;

	// ボタン長押し用のフレームカウンタ
	int m_flameLeft;
	int m_flameRight;

	// 現在選択しているステージ
	int m_stage;

	// 真ん中の波エフェクト
	int m_effectHandle;
	int a;

	int g;
};

