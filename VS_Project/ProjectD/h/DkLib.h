#pragma once

// �p�b�h�֌W�萔

// �p�b�hID
#define DK_INPUT_PAD1				(0)
#define DK_INPUT_PAD2				(1)
#define DK_INPUT_PAD3				(2)
#define DK_INPUT_PAD4				(3)

// �p�b�h�{�^���̃r�b�g�}�X�N
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

// DK_XINPUT_STATE�p�̓Y����
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

// �p�b�h�̃��[�^�[�ԍ�
#define DK_PAD_MOTOR_LEFT			(1)
#define DK_PAD_MOTOR_RIGHT			(2)

// ���[�^���x�̒l
#define DK_PAD_MOTOR_VALUE			(6.5535)	

namespace DkLib 
{

	// �\����

	// XINPUT_STATE�̑���̍\����
	struct DK_XINPUT_STATE
	{
		bool	Buttons[14];	// �{�^���P�U��( �Y���ɂ� DK_XINPUT_UP �����g�p����
		unsigned char	LeftTrigger;	// ���g���K�[( 0�`255 )
		unsigned char	RightTrigger;	// �E�g���K�[( 0�`255 )
		short		ThumbLX;	// ���X�e�B�b�N�̉����l( -32768 �` 32767 )
		short		ThumbLY;	// ���X�e�B�b�N�̏c���l( -32768 �` 32767 )
		short		ThumbRX;	// �E�X�e�B�b�N�̉����l( -32768 �` 32767 )
		short		ThumbRY;	// �E�X�e�B�b�N�̏c���l( -32768 �` 32767 )
	};
	

	// �֐�

	// ���͌n�֐�

	/// <summary>
	/// �p�b�h���ڑ�����Ă��鐔���擾����
	/// </summary>
	/// <returns>�ڑ�����Ă��鐔</returns>
	int GetJoypadNum();

	/// <summary>
	/// �p�b�h�̓��͏�Ԃ��擾����
	/// DK_PAD_UP�Ȃǂ̃r�b�g�}�X�N��AND���Z���Č��ʂ�0�łȂ���Ή�����Ă���
	/// </summary>
	/// <param name="padNum">�p�b�h�ԍ�</param>
	/// <returns>���͏�Ԃ�\���r�b�g</returns>
	int GetJoypadState(int padNum);

	/// <summary>
	/// XInput�̃p�b�h�\���̂����̂܂܎擾����
	/// </summary>
	/// <param name="padNum">�p�b�h�ԍ�</param>
	/// <returns>XInput�̃p�b�h�\����</returns>
	DK_XINPUT_STATE GetPadXInputState(int padNum);

	/// <summary>
	/// �p�b�h�̐U�����J�n����
	/// </summary>
	/// <param name="padNum">�U�����������p�b�h�ԍ�</param>
	/// <param name="power">�U����(0~1000)</param>
	/// <param name="motorNum">�����[�^���E���[�^���w�肷��(DK_PAD_MOTOR_LEFT,DK_PAD_MOTOR_RIGHT)</param>
	/// <returns>0:�����@-1:�G���[</returns>
	int StartPadVibration(int padNum, int power, int motorNum);

	/// <summary>
	/// �p�b�h�̐U�����~����
	/// </summary>
	/// <param name="padNum">�U�����������p�b�h�ԍ�</param>
	/// <param name="motorNum">�����[�^���E���[�^���w�肷��(DK_PAD_MOTOR_LEFT,DK_PAD_MOTOR_RIGHT)</param>
	/// <returns>0:�����@-1:�G���[</returns>
	int StopPadVibration(int padNum, int motorNum);
}