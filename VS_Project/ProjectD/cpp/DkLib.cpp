#include "DkLib.h"
#include <Xinput.h>
#include <Windows.h>
#include <winerror.h>

using namespace DkLib;

int DkLib::GetJoypadNum()
{
	// �p�b�h���ڑ�����Ă��鐔��ۑ�����
	int num = 0;

	DWORD dwResult;
	for (int i = 0; i < XUSER_MAX_COUNT; i++)
	{
		XINPUT_STATE st;
		ZeroMemory(&st, sizeof(XINPUT_STATE));

		// XInput�̏�Ԃ��󂯎��
		dwResult = XInputGetState(i, &st);

		if (dwResult == ERROR_SUCCESS)
		{
			// �ڑ�����Ă��鐔����₷
			num++;
		}
	}

	return num;
}

int DkLib::GetJoypadState(int padNum)
{
	// ���͏�Ԃ�ۑ�����\����
	XINPUT_STATE st;
	ZeroMemory(&st, sizeof(XINPUT_STATE));

	// ���͏�Ԃ��擾
	XInputGetState(padNum, &st);

	return st.Gamepad.wButtons;
}

DK_XINPUT_STATE DkLib::GetPadXInputState(int padNum)
{
	// �ŏI�I�ɕԂ��\����
	DK_XINPUT_STATE st;
	ZeroMemory(&st, sizeof(DK_XINPUT_STATE));

	// XInput�̍\����
	XINPUT_STATE stX;
	ZeroMemory(&stX, sizeof(XINPUT_STATE));

	// XInput�̏�Ԃ��擾����
	XInputGetState(padNum, &stX);

	// �{�^���̏�Ԃ��i�[����
	st.Buttons[DK_PAD_UP] = (DK_PAD_UP & stX.Gamepad.wButtons) != 0;
	st.Buttons[DK_PAD_DOWN] = (DK_PAD_DOWN & stX.Gamepad.wButtons) != 0;
	st.Buttons[DK_PAD_LEFT] = (DK_PAD_LEFT & stX.Gamepad.wButtons) != 0;
	st.Buttons[DK_PAD_RIGHT] = (DK_PAD_RIGHT & stX.Gamepad.wButtons) != 0;
	st.Buttons[DK_PAD_START] = (DK_PAD_START & stX.Gamepad.wButtons) != 0;
	st.Buttons[DK_PAD_BACK] = (DK_PAD_BACK & stX.Gamepad.wButtons) != 0;
	st.Buttons[DK_PAD_LEFT_THUMB] = (DK_PAD_LEFT_THUMB & stX.Gamepad.wButtons) != 0;
	st.Buttons[DK_PAD_RIGHT_THUMB] = (DK_PAD_RIGHT_THUMB & stX.Gamepad.wButtons) != 0;
	st.Buttons[DK_PAD_LEFT_SHOULDER] = (DK_PAD_LEFT_SHOULDER & stX.Gamepad.wButtons) != 0;
	st.Buttons[DK_PAD_RIGHT_SHOULDER] = (DK_PAD_RIGHT_SHOULDER & stX.Gamepad.wButtons) != 0;
	st.Buttons[DK_PAD_A] = (DK_PAD_A & stX.Gamepad.wButtons) != 0;
	st.Buttons[DK_PAD_B] = (DK_PAD_B & stX.Gamepad.wButtons) != 0;
	st.Buttons[DK_PAD_X] = (DK_PAD_X & stX.Gamepad.wButtons) != 0;
	st.Buttons[DK_PAD_Y] = (DK_PAD_Y & stX.Gamepad.wButtons) != 0;

	// �g���K�[�����i�[����
	st.LeftTrigger = stX.Gamepad.bLeftTrigger;
	st.RightTrigger = stX.Gamepad.bRightTrigger;

	// �X�e�B�b�N�̌X���l���i�[����
	st.ThumbLX = stX.Gamepad.sThumbLX;
	st.ThumbLY = stX.Gamepad.sThumbLY;
	st.ThumbRX = stX.Gamepad.sThumbRX;
	st.ThumbRY = stX.Gamepad.sThumbRY;

	return st;
}

int DkLib::StartPadVibration(int padNum, int power, int motorNum)
{
	// �U���������\����
	XINPUT_VIBRATION st;
	ZeroMemory(&st, sizeof(XINPUT_VIBRATION));

	// ���[�^���x
	float speed = power* DK_PAD_MOTOR_VALUE;

	// �U���������
	if (motorNum == DK_PAD_MOTOR_LEFT) {
		// �����[�^�ɑ��x����͂���
		st.wLeftMotorSpeed = speed;
	}
	else if (motorNum == DK_PAD_MOTOR_RIGHT) {
		// �E���[�^�ɑ��x����͂���
		st.wRightMotorSpeed = speed;
	}
	else {
		// ��ȊO���ƃG���[
		return -1;
	}
	
	// �p�b�h�̏�Ԃ��X�V
	if (XInputSetState(padNum, &st) != ERROR_SUCCESS) return -1;

	return 0;
}

int DkLib::StopPadVibration(int padNum, int motorNum)
{
	// �U���������\����
	XINPUT_VIBRATION st;
	ZeroMemory(&st, sizeof(XINPUT_VIBRATION));

	// �U���������
	if (motorNum == DK_PAD_MOTOR_LEFT) {
		// �����[�^�ɑ��x����͂���
		st.wLeftMotorSpeed = 0;
	}
	else if (motorNum == DK_PAD_MOTOR_RIGHT) {
		// �E���[�^�ɑ��x����͂���
		st.wRightMotorSpeed = 0;
	}
	else {
		// ��ȊO���ƃG���[
		return -1;
	}

	// �p�b�h�̏�Ԃ��X�V
	if (XInputSetState(padNum, &st) != ERROR_SUCCESS) return -1;

	return 0;
}
