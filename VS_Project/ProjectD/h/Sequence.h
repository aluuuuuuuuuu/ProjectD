#pragma once
#include "Singleton.h"

class Sequence :
	public Singleton<Sequence>
{
	friend class Singleton<Sequence>;

public:
	void Init();
	void Update();
	void Draw();

	// �C��V�[�P���X��ݒ肷��
	void PlayFaintSequ();

	// �V�[�P���X���Đ����ł��邩
	bool IsPlaySequ();

private:
	// �v���C�x�[�g�R���X�g���N�^
	Sequence() {};

	// �֐��|�C���^
	using m_updateFunc_t = void (Sequence::*)();
	using m_drawFunc_t = void (Sequence::*)() const;
	m_updateFunc_t m_updateFunc = nullptr;
	m_drawFunc_t m_drawFunc = nullptr;

	// null
	void NullUpdate();
	void NullDraw() const;

	// �C��V�[�P���X����
	void FaintUpdate();
	void FaintDraw() const;

	// �V�[�P���X���Đ�����t���O
	bool m_playFlag = false;
};

