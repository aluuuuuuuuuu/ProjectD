#include "Application.h"
#include "SceneManager.h"
#include "DxLib.h"
#include "Input.h"
#include "SceneTest.h"
#include <cassert>
#include "GraphicManager.h"

// ����������
bool Application::Init()
{
	// �O���t�@�C������萔���擾����
	assert(ConstantsFileLoad("data/constant/Application.csv", Constants) == 1);

	// �E�B���h�E���[�h�̐ݒ�
	ChangeWindowMode(true);

	// �E�B���h�E���̐ݒ�
	SetWindowText("ProjectD");

	// ��ʃT�C�Y�̐ݒ�
	SetGraphMode(static_cast<int>(Constants["SCREEN_WIDTH"]),
		static_cast<int>(Constants["SCREEN_HEIGHT"]),
		static_cast<int>(Constants["COLRO_BIT"]));

	// �𑜓x�̐ݒ�
	SetWindowSize(static_cast<int>(Constants["RESOLUTION_WIDTH"]),
		static_cast<int>(Constants["RESOLUTION_HEIGHT"]));

	// �w�ʂ̕`����s��Ȃ�
	SetUseBackCulling(true);

	// ���C�e�B���O���g�p����
	SetUseLighting(true);

	// �j�A���X�g�l�C�o�[�@�ŕ`�悷��
	SetDrawMode(DX_DRAWMODE_NEAREST);

	// Dxlib�̏�����
	if (DxLib_Init() == -1) return false;

	// �o�b�N�o�b�t�@�ɕ`�悷��
	SetDrawScreen(DX_SCREEN_BACK);

	// �J�[�\���̕\���ݒ�
	SetMouseDispFlag(true);

	// �摜�̃��[�h
	assert(GraphicManager::getInstance().LoadGraphics() == 1);

	return true;
}

// ���C������
void Application::Run()
{
	// �V�[���}�l�[�W���[�̃C���X�^���X���擾
	auto& manager = SceneManager::getInstance();

	// �����V�[����ݒ�
	manager.ChangeScene(std::make_shared <SceneTest>());

	// �C���v�b�g�̃C���X�^���X���擾
	auto& input = Input::getInstance();

	// �C���v�b�g�̏�������
	input.Init();

	// �Q�[�����[�v
	while (ProcessMessage() != -1)
	{
		// �t���[���̊J�n�������o���Ă���
		LONGLONG start = GetNowHiPerformanceCount();

		// Z�o�b�t�@���g�p���ď�������
		SetUseZBuffer3D(true);
		SetWriteZBuffer3D(true);

		// �`����s���O�ɉ�ʂ��N���A����
		ClearDrawScreen();

		/*�Q�[������*/

		// �X�V����
		input.Update();
		manager.SceneUpdate();

		manager.SceneDraw();

		// ��ʂ��؂�ւ��̂�҂�
		ScreenFlip();

		// manager�̃t���O�ŃQ�[�����I��������
		if (manager.GetGameEnd()) break;

		// esc�ŏI���i���j
		if (CheckHitKey(KEY_INPUT_ESCAPE)) {
			break;
		}

		// FPS60�ɌŒ肷��
		while (GetNowHiPerformanceCount() - start < 16667) {}
	}
}

// �I������
void Application::Terminate()
{
	DxLib_End();	// DxLib�̏I������
}
