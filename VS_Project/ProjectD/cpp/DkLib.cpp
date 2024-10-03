#include "DkLib.h"
#include <Xinput.h>
#include <Windows.h>
#include <winerror.h>

using namespace DkLib;

int DkLib::GetJoypadNum()
{
	// パッドが接続されている数を保存する
	int num = 0;

	DWORD dwResult;
	for (int i = 0; i < XUSER_MAX_COUNT; i++)
	{
		XINPUT_STATE st;
		ZeroMemory(&st, sizeof(XINPUT_STATE));

		// XInputの状態を受け取る
		dwResult = XInputGetState(i, &st);

		if (dwResult == ERROR_SUCCESS)
		{
			// 接続されている数一つ増やす
			num++;
		}
	}

	return num;
}

int DkLib::GetJoypadState(int padNum)
{
	// 入力状態を保存する構造体
	XINPUT_STATE st;
	ZeroMemory(&st, sizeof(XINPUT_STATE));

	// 入力状態を取得
	XInputGetState(padNum, &st);

	return st.Gamepad.wButtons;
}

DK_XINPUT_STATE DkLib::GetPadXInputState(int padNum)
{
	// 最終的に返す構造体
	DK_XINPUT_STATE st;
	ZeroMemory(&st, sizeof(DK_XINPUT_STATE));

	// XInputの構造体
	XINPUT_STATE stX;
	ZeroMemory(&stX, sizeof(XINPUT_STATE));

	// XInputの状態を取得する
	XInputGetState(padNum, &stX);

	// ボタンの状態を格納する
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

	// トリガー情報を格納する
	st.LeftTrigger = stX.Gamepad.bLeftTrigger;
	st.RightTrigger = stX.Gamepad.bRightTrigger;

	// スティックの傾き値を格納する
	st.ThumbLX = stX.Gamepad.sThumbLX;
	st.ThumbLY = stX.Gamepad.sThumbLY;
	st.ThumbRX = stX.Gamepad.sThumbRX;
	st.ThumbRY = stX.Gamepad.sThumbRY;

	return st;
}

int DkLib::StartPadVibration(int padNum, int power, int motorNum)
{
	// 振動情報を持つ構造体
	XINPUT_VIBRATION st;
	ZeroMemory(&st, sizeof(XINPUT_VIBRATION));

	// モータ速度
	float speed = power* DK_PAD_MOTOR_VALUE;

	// 振動情報を入力
	if (motorNum == DK_PAD_MOTOR_LEFT) {
		// 左モータに速度を入力する
		st.wLeftMotorSpeed = speed;
	}
	else if (motorNum == DK_PAD_MOTOR_RIGHT) {
		// 右モータに速度を入力する
		st.wRightMotorSpeed = speed;
	}
	else {
		// 上以外だとエラー
		return -1;
	}
	
	// パッドの状態を更新
	if (XInputSetState(padNum, &st) != ERROR_SUCCESS) return -1;

	return 0;
}

int DkLib::StopPadVibration(int padNum, int motorNum)
{
	// 振動情報を持つ構造体
	XINPUT_VIBRATION st;
	ZeroMemory(&st, sizeof(XINPUT_VIBRATION));

	// 振動情報を入力
	if (motorNum == DK_PAD_MOTOR_LEFT) {
		// 左モータに速度を入力する
		st.wLeftMotorSpeed = 0;
	}
	else if (motorNum == DK_PAD_MOTOR_RIGHT) {
		// 右モータに速度を入力する
		st.wRightMotorSpeed = 0;
	}
	else {
		// 上以外だとエラー
		return -1;
	}

	// パッドの状態を更新
	if (XInputSetState(padNum, &st) != ERROR_SUCCESS) return -1;

	return 0;
}
