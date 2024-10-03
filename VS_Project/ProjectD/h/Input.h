#pragma once
#include "Vec2.h"
#include "Vec3.h"
#include "Singleton.h"
#include "Constant.h"
#include <XInput.h>
#include "DkLib.h"

// �e�{�^���̒萔

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

// �p�b�h�̎��ʒ萔

#define INPUT_PAD_NUM1 0
#define INPUT_PAD_NUM2 1
#define INPUT_PAD_NUM3 2
#define INPUT_PAD_NUM4 3

//struct DK_XINPUT_STATE
//{
//	bool	Buttons[14];	// �{�^���P�U��( �Y���ɂ� DK_XINPUT_UP �����g�p����
//	unsigned char	LeftTrigger;	// ���g���K�[( 0�`255 )
//	unsigned char	RightTrigger;	// �E�g���K�[( 0�`255 )
//	short		ThumbLX;	// ���X�e�B�b�N�̉����l( -32768 �` 32767 )
//	short		ThumbLY;	// ���X�e�B�b�N�̏c���l( -32768 �` 32767 )
//	short		ThumbRX;	// �E�X�e�B�b�N�̉����l( -32768 �` 32767 )
//	short		ThumbRY;	// �E�X�e�B�b�N�̏c���l( -32768 �` 32767 )
//};

// �C���v�b�g����񋟂���V���O���g���N���X
class Input : 
	public Singleton<Input>,
	public Constant
{
	friend class Singleton<Input>;

public:

	void Init();

	// �X�V����
	void Update();

	// �������u�Ԃ��Ƃ�
	bool IsTrigger(int input) const;

	// �����Ă���Ԃ��Ƃ�
	bool IsHold(int input) const;

	// �������u�Ԃ��Ƃ�
	bool IsRelease(int input) const;

	// �X�e�B�b�N���͂̕����x�N�g����Ԃ�
	Vec3 GetStickVector(int input) const;

	// �X�e�B�b�N���͂̒P�ʕ����x�N�g����Ԃ�
	Vec3 GetStickUnitVector(int input) const;

	// �X�e�B�b�N���͂̒�����Ԃ�
	float GetStickVectorLength(int input) const;

	// �X�e�B�b�N���X����X�l��Ԃ�
	float GetStickThumbX(int input) const;

	// �X�e�B�b�N���X����Y�l��Ԃ�
	float GetStickThumbY(int input) const;

private:

	// �R���g���[���[�̏�Ԃ��擾����
	bool GetPadXInputState();

	// �v���C�x�[�g�R���X�g���N�^
	Input():m_padState(),m_lastPadState() {};

	DkLib::DK_XINPUT_STATE m_padState, m_lastPadState;
};

