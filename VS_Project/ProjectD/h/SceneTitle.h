#pragma once
#include "SceneBase.h"

// タイトルシーン
class SceneTitle:
	public SceneBase
{
public:
	SceneTitle();
	virtual ~SceneTitle();

	void Update();

	void Draw() const;
private:

	// 関数ポインタ
	using m_updateFunc_t = void (SceneTitle::*)();
	using m_drawFunc_t = void (SceneTitle::*)() const;
	m_updateFunc_t m_updateFunc = nullptr;
	m_drawFunc_t m_drawFunc = nullptr;

	// 通常の処理
	void NormalUpdate();
	void NormalDraw() const;

	// フェード処理
	void FadeInUpdate();
	void FadeOutUpdate();
	void FadeDraw() const;

	// フレームカウンタ
	int m_flame;
};

