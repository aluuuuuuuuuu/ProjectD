#include "Application.h"
#include "SceneManager.h"
#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include "Input.h"
#include "SceneTest.h"
#include <cassert>
#include "GraphicManager.h"
#include "SceneTitle.h"
#include "SceneSelect.h"

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

	// ���C�g�̃J���[�𒲐�����
	SetLightDifColor(GetColorF(0.9f, 0.9f, 0.9f, 0.0f));

	// �j�A���X�g�l�C�o�[�@�ŕ`�悷��
	SetDrawMode(DX_DRAWMODE_NEAREST);

	// DirectX11���g�p����悤�ɂ���B(DirectX9���A�ꕔ�@�\�s��)
	// Effekseer���g�p����ɂ͕K���ݒ肷��B
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	// Dxlib�̏�����
	if (DxLib_Init() == -1) return false;

	// Effekseer������������B
	// �����ɂ͉�ʂɕ\������ő�p�[�e�B�N������ݒ肷��B
	if (Effekseer_Init(8000) == -1)
	{
		DxLib_End();
		return -1;
	}

	// �G�t�F�N�T�[�̘c�݂�����������
	Effekseer_InitDistortion(1.0f);

	// �t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h���B
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// DX���C�u�����̃f�o�C�X���X�g�������̃R�[���o�b�N��ݒ肷��B
	// �E�C���h�E�ƃt���X�N���[���̐؂�ւ�����������ꍇ�͕K�����s����B
	// �������ADirectX11���g�p����ꍇ�͎��s����K�v�͂Ȃ��B
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	// Effekseer��2D�`��̐ݒ������B
	Effekseer_Set2DSetting(1920, 1080);

	// �t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h���B
	// Effekseer���g�p����ꍇ�͕K���ݒ肷��B
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// �o�b�N�o�b�t�@�ɕ`�悷��
	SetDrawScreen(DX_SCREEN_BACK);

	// �w�i�F�̐ݒ�
	SetBackgroundColor(20, 20, 200);

	// �J�[�\���̕\���ݒ�
	SetMouseDispFlag(true);

	// Z�o�b�t�@��L���ɂ���B
	// Effekseer���g�p����ꍇ�A2D�Q�[���ł�Z�o�b�t�@���g�p����B
	SetUseZBuffer3D(TRUE);

	// Z�o�b�t�@�ւ̏������݂�L���ɂ���B
	// Effekseer���g�p����ꍇ�A2D�Q�[���ł�Z�o�b�t�@���g�p����B
	SetWriteZBuffer3D(TRUE);

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

		// DX���C�u�����̃J������Effekseer�̃J�����𓯊�����B
		Effekseer_Sync3DSetting();

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

	// �I���������s��
	Terminate();
}

// �I������
void Application::Terminate()
{
	// Effekseer���I������B
	Effkseer_End();

	DxLib_End();	// DxLib�̏I������
}
