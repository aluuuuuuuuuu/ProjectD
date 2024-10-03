#pragma once
#include "Vec2.h"
#include "Vec3.h"
#include "Singleton.h"
#include "Constant.h"
#include <XInput.h>
#include "DkLib.h"

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

//struct DK_XINPUT_STATE
//{
//	bool	Buttons[14];	// ボタン１６個( 添字には DK_XINPUT_UP 等を使用する
//	unsigned char	LeftTrigger;	// 左トリガー( 0～255 )
//	unsigned char	RightTrigger;	// 右トリガー( 0～255 )
//	short		ThumbLX;	// 左スティックの横軸値( -32768 ～ 32767 )
//	short		ThumbLY;	// 左スティックの縦軸値( -32768 ～ 32767 )
//	short		ThumbRX;	// 右スティックの横軸値( -32768 ～ 32767 )
//	short		ThumbRY;	// 右スティックの縦軸値( -32768 ～ 32767 )
//};

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

private:

	// コントローラーの状態を取得する
	bool GetPadXInputState();

	// プライベートコンストラクタ
	Input():m_padState(),m_lastPadState() {};

	DkLib::DK_XINPUT_STATE m_padState, m_lastPadState;
};

