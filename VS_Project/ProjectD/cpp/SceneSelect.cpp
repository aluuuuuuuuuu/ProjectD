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
	// �O���t�@�C������萔���擾����
	assert(ConstantsFileLoad("data/constant/SceneSelect.csv", Constants) == 1);

	m_effectHandle = LoadEffekseerEffect("data/effect/string.efkefc.efk", 1.0f);

	g = LoadGraph("data/image/���̖��ݒ� 1.png");

	// �w�i�F�̐ݒ�
	SetBackgroundColor(240, 240, 240);

	// �֐��|�C���^�̏�����
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
	// A�{�^���������ꂽ��t�F�[�h�A�E�g�����Ɉڍs����
	if (Input::getInstance().IsTrigger(INPUT_A)) {
		m_updateFunc = &SceneSelect::FadeOutUpdate;
		m_drawFunc = &SceneSelect::FadeDraw;
	}

	// �I���X�e�[�W��؂�ւ���
	StageSelect();
}

void SceneSelect::NormalDraw() const
{
	// �e�X�g�ŃX�e�[�W����\��
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

	//�t�F�[�h�Ö�
	int alpha = (int)(255 * ((float)m_flame / 60));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 1980, 1080, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SceneSelect::ChangeScene()
{
	// �I�������X�e�[�W�Ɉڍs����
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
	// ���E�{�^���őI���X�e�[�W��؂�ւ���
	StageSelectTrigger();

	// ���E�{�^���������őI���X�e�[�W��؂�ւ���
	StageSelectHold();
}

void SceneSelect::StageSelectTrigger()
{
	// ���E�{�^���őI���X�e�[�W��؂�ւ���
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
	// ���E�{�^���������ŘA���őI���X�e�[�W��؂�ւ���
	if (Input::getInstance().IsHold(INPUT_LEFT)) {
		m_flameLeft++;

		// ���t���[��������������A���ŃX�e�[�W��؂�ւ���
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

	// ���E�{�^���������ŘA���őI���X�e�[�W��؂�ւ���
	if (Input::getInstance().IsHold(INPUT_RIGHT)) {
		m_flameRight++;

		// ���t���[��������������A���ŃX�e�[�W��؂�ւ���
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
