#pragma once
#include "SceneBase.h"

// �^�C�g���V�[��
class SceneTitle:
	public SceneBase
{
public:
	SceneTitle();
	virtual ~SceneTitle();

	void Update();

	void Draw() const;
private:

	// �֐��|�C���^
	using m_updateFunc_t = void (SceneTitle::*)();
	using m_drawFunc_t = void (SceneTitle::*)() const;
	m_updateFunc_t m_updateFunc = nullptr;
	m_drawFunc_t m_drawFunc = nullptr;

	// �ʏ�̏���
	void NormalUpdate();
	void NormalDraw() const;

	// �t�F�[�h����
	void FadeInUpdate();
	void FadeOutUpdate();
	void FadeDraw() const;

	// �t���[���J�E���^
	int m_flame;
};

