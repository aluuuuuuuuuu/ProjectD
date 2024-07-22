#include "SceneTitle.h"
#include "GraphicManager.h"
#include "DxLib.h"
#include "SceneManager.h"
#include "SceneSelect.h"

SceneTitle::SceneTitle() :
	m_flame(60)
{
	m_updateFunc = &SceneTitle::FadeInUpdate;
	m_drawFunc = &SceneTitle::FadeDraw;
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Update()
{
	(this->*m_updateFunc)();
}

void SceneTitle::Draw() const
{
	(this->*m_drawFunc)();
}

void SceneTitle::NormalUpdate()
{
	// ��������̃{�^���������ꂽ��t�F�[�h�A�E�g�����Ɉڍs����
	if (GetJoypadInputState(DX_INPUT_PAD1) != 0)
	{
		m_updateFunc = &SceneTitle::FadeOutUpdate;
		m_drawFunc = &SceneTitle::FadeDraw;
	}

	// �X�^�[�g�w����_�ł�����
	if (m_flame == 120) {
		m_flame++;
	}
	else if (m_flame == 1) {
		m_flame--;
	}
	else if (m_flame % 2 == 0) {
		m_flame += 2;
	}
	else{
		m_flame -= 2;
	}
}

void SceneTitle::NormalDraw() const
{
	DrawGraph(0, 0, GraphicManager::getInstance().GetGraph("TitleBack"), true);

	// �X�^�[�g�w����_�ł����Ȃ���`��
	int alpha = (int)(255 * ((float)m_flame / 120));
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawGraph(560, 900, GraphicManager::getInstance().GetGraph("PressAnyButton"), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SceneTitle::FadeInUpdate()
{
	m_flame--;
	if (m_flame <= 0) {
		m_updateFunc = &SceneTitle::NormalUpdate;
		m_drawFunc = &SceneTitle::NormalDraw;
	}
}

void SceneTitle::FadeOutUpdate()
{
	m_flame++;
	if (m_flame >= 120) {
		SceneManager::getInstance().ChangeScene(std::make_shared<SceneSelect>());
	}
}

void SceneTitle::FadeDraw() const
{
	NormalDraw();

	//�t�F�[�h�Ö�
	int alpha = (int)(255 * ((float)m_flame / 60));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 1980, 1080, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
