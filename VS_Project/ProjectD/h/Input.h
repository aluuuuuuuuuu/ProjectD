#pragma once
#include "Vec2.h"
#include "Vec3.h"
#include "Singleton.h"
#include "Constant.h"
#include <Xinput.h>

// 各ボタンの定数

#define INPUT_A 0
#define INPUT_B 1
#define INPUT_X 2
#define INPUT_Y 3
#define INPUT_UP 4
#define INPUT_DOWN 5
#define INPUT_LEFT 6
#define INPUT_RIGHT 7
#define INPUT_START 8
#define INPUT_BACK 9
#define INPUT_LEFT_PUSH 10
#define INPUT_RIGHT_PUSH 11
#define INPUT_LEFT_SHOULDER 12
#define INPUT_RIGHT_SHOULDER 13
#define INPUT_LEFT_TRIGGER 14
#define INPUT_RIGHT_TRIGGER 15
#define INPUT_LEFT_STICK 16
#define INPUT_RIGHT_STICK 17

// パッドの識別定数

#define INPUT_PAD_NUM1 0
#define INPUT_PAD_NUM2 1
#define INPUT_PAD_NUM3 2
#define INPUT_PAD_NUM4 3

// XInputの入力状態を保存する構造体
struct XInputState
{
	XINPUT_STATE state;
	bool connected = false;
};

// インプット情報を提供するシングルトンクラス
class Input : 
	public Singleton<Input>,
	public Constant
{
	friend class Singleton<Input>;

public:

	void Init();

	// 更新処理
	void Update();

	// 押した瞬間をとる
	bool IsTrigger(int input) const;

	// 押している間をとる
	bool IsHold(int input) const;

	// 離した瞬間をとる
	bool IsRelease(int input) const;

	// スティック入力の方向ベクトルを返す
	Vec3 GetStickVector(int input) const;

	// スティック入力の単位方向ベクトルを返す
	Vec3 GetStickUnitVector(int input) const;

	// スティック入力の長さを返す
	float GetStickVectorLength(int input) const;

	// スティックを傾けたX値を返す
	float GetStickThumbX(int input) const;

	// スティックを傾けたY値を返す
	float GetStickThumbY(int input) const;
	
	// 生のXInputの構造体を返す
	XINPUT_STATE GetXInputState(int num) const;

private:

	// コントローラーの状態を取得する
	bool GetPadXInputState();

	// コントローラーの接続状態
	XInputState m_XInputState[XUSER_MAX_COUNT];

	// 今フレームのインプットステート
	XINPUT_STATE m_padState;

	// 前フレームのインプットステート
	XINPUT_STATE m_lastPadState;

	// プライベートコンストラクタ
	Input():m_padState(),m_lastPadState() {};
};

