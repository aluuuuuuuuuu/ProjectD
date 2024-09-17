#pragma once

// パッド関係定数

// パッドID
#define DK_INPUT_PAD1				(0)
#define DK_INPUT_PAD2				(1)
#define DK_INPUT_PAD3				(2)
#define DK_INPUT_PAD4				(3)

// パッドボタンのビットマスク
#define DK_PAD_UP					(0x0001)
#define DK_PAD_DOWN					(0x0002)
#define DK_PAD_LEFT					(0x0004)
#define DK_PAD_RIGHT				(0x0008)
#define DK_PAD_START				(0x0010)
#define DK_PAD_BACK					(0x0020)
#define DK_PAD_LEFT_THUMB			(0x0040)
#define DK_PAD_RIGHT_THUMB			(0x0080)
#define DK_PAD_LEFT_SHOULDER		(0x0100)
#define DK_PAD_RIGHT_SHOULDER		(0x0200)
#define DK_PAD_A					(0x1000)
#define DK_PAD_B					(0x2000)
#define DK_PAD_X					(0x4000)
#define DK_PAD_Y					(0x8000)

// DK_XINPUT_STATE用の添え字
#define DK_XINPUT_UP				(0)
#define DK_XINPUT_DOWN				(1)
#define DK_XINPUT_LEFT				(2)
#define DK_XINPUT_RIGHT				(3)
#define DK_XINPUT_START				(4)
#define DK_XINPUT_BACK				(5)
#define DK_XINPUT_LEFT_THUMB		(6)	
#define DK_XINPUT_RIGHT_THUMB		(7)
#define DK_XINPUT_LEFT_SHOULDER		(8)
#define DK_XINPUT_RIGHT_SHOULDER	(9)	
#define DK_XINPUT_A					(10)
#define DK_XINPUTD_B				(11)
#define DK_XINPUT_X					(12)
#define DK_XINPUT_Y					(13)

// パッドのモーター番号
#define DK_PAD_MOTOR_LEFT			(1)
#define DK_PAD_MOTOR_RIGHT			(2)

// モータ速度の値
#define DK_PAD_MOTOR_VALUE			(6.5535)	

namespace DkLib 
{

	// 構造体

	// XINPUT_STATEの代わりの構造体
	struct DK_XINPUT_STATE
	{
		bool	Buttons[14];	// ボタン１６個( 添字には DK_XINPUT_UP 等を使用する
		unsigned char	LeftTrigger;	// 左トリガー( 0～255 )
		unsigned char	RightTrigger;	// 右トリガー( 0～255 )
		short		ThumbLX;	// 左スティックの横軸値( -32768 ～ 32767 )
		short		ThumbLY;	// 左スティックの縦軸値( -32768 ～ 32767 )
		short		ThumbRX;	// 右スティックの横軸値( -32768 ～ 32767 )
		short		ThumbRY;	// 右スティックの縦軸値( -32768 ～ 32767 )
	};
	

	// 関数

	// 入力系関数

	/// <summary>
	/// パッドが接続されている数を取得する
	/// </summary>
	/// <returns>接続されている数</returns>
	int GetJoypadNum();

	/// <summary>
	/// パッドの入力状態を取得する
	/// DK_PAD_UPなどのビットマスクとAND演算して結果が0でなければ押されている
	/// </summary>
	/// <param name="padNum">パッド番号</param>
	/// <returns>入力状態を表すビット</returns>
	int GetJoypadState(int padNum);

	/// <summary>
	/// XInputのパッド構造体をそのまま取得する
	/// </summary>
	/// <param name="padNum">パッド番号</param>
	/// <returns>XInputのパッド構造体</returns>
	DK_XINPUT_STATE GetPadXInputState(int padNum);

	/// <summary>
	/// パッドの振動を開始する
	/// </summary>
	/// <param name="padNum">振動させたいパッド番号</param>
	/// <param name="power">振動力(0~1000)</param>
	/// <param name="motorNum">左モータが右モータを指定する(DK_PAD_MOTOR_LEFT,DK_PAD_MOTOR_RIGHT)</param>
	/// <returns>0:成功　-1:エラー</returns>
	int StartPadVibration(int padNum, int power, int motorNum);

	/// <summary>
	/// パッドの振動を停止する
	/// </summary>
	/// <param name="padNum">振動させたいパッド番号</param>
	/// <param name="motorNum">左モータが右モータを指定する(DK_PAD_MOTOR_LEFT,DK_PAD_MOTOR_RIGHT)</param>
	/// <returns>0:成功　-1:エラー</returns>
	int StopPadVibration(int padNum, int motorNum);
}