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
	// �O���t�@�C������萔���擾����
	assert(ConstantsFileLoad("data/constant/SceneSelect.csv", Constants) == 1);

	// �摜�̃��[�h
	m_waveGraphHandle = LoadGraph("data/image/string.png");
	m_stringGraphHandle = LoadGraph("data/image/SelectStage.png");

	// �w�i�F�̐ݒ�
	SetBackgroundColor(240, 240, 240);

	// �֐��|�C���^�̏�����
	m_updateFunc = &SceneSelect::FadeInUpdate;
	m_drawFunc = &SceneSelect::FadeDraw;
}

SceneSelect::~SceneSelect()
{
	// �摜�̃f���[�g
	DeleteGraph(m_waveGraphHandle);
	DeleteGraph(m_stringGraphHandle);
}

void SceneSelect::Update()
{
	// �X�V�̊֐��|�C���^�����s
	(this->*m_updateFunc)();
}

void SceneSelect::Draw() const
{
	// �`��̊֐��|�C���^�����s
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
	// �ʏ�̕`��������ɍs��
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
	StageSelectTriggerButton();

	// ���E�{�^���������őI���X�e�[�W��؂�ւ���
	StageSelectHoldButton();

	// �X�e�B�b�N�̍��E���͂őI���X�e�[�W��؂�ւ���
	StageSelectStick();
}

void SceneSelect::StageSelectTriggerButton()
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

void SceneSelect::StageSelectHoldButton()
{
	// ���{�^���������ŘA���őI���X�e�[�W��؂�ւ���
	if (Input::getInstance().IsHold(INPUT_LEFT)) {
		m_flameLeftButton++;

		// ���t���[��������������A���ŃX�e�[�W��؂�ւ���
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

	// �E�{�^���������ŘA���őI���X�e�[�W��؂�ւ���
	if (Input::getInstance().IsHold(INPUT_RIGHT)) {
		m_flameRightButton++;

		// ���t���[��������������A���ŃX�e�[�W��؂�ւ���
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
	// �����͂őI��؂�ւ�
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

	// �E���͂őI��؂�ւ�
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
