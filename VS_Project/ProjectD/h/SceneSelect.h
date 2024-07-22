#pragma once
#include "SceneBase.h"
#include "Constant.h"

// �X�e�[�W�I���V�[��
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
	// �֐��|�C���^
	using m_updateFunc_t = void (SceneSelect::*)();
	using m_drawFunc_t = void (SceneSelect::*)() const;
	m_updateFunc_t m_updateFunc = nullptr;
	m_drawFunc_t m_drawFunc = nullptr;

	// �ʏ�̏���
	void NormalUpdate();
	void NormalDraw() const;

	// �t�F�[�h����
	void FadeInUpdate();
	void FadeOutUpdate();
	void FadeDraw() const;

	// �I�������X�e�[�W�Ɉڍs����
	void ChangeScene();

	// �I���X�e�[�W��؂�ւ���
	void StageSelect();

	// ���E�{�^���őI���X�e�[�W��؂�ւ���
	void StageSelectTrigger();

	// ���E�{�^���������őI���X�e�[�W��؂�ւ���
	void StageSelectHold();

	// �t���[���J�E���^
	int m_flame;

	// �{�^���������p�̃t���[���J�E���^
	int m_flameLeft;
	int m_flameRight;

	// ���ݑI�����Ă���X�e�[�W
	int m_stage;

	// �^�񒆂̔g�G�t�F�N�g
	int m_effectHandle;
	int a;

	int g;
};

