#pragma once
#include "CameraBase.h"

#define SUBACTOR_MODE 0
#define MAINACTOR_MODE 1

class PlayerCamera :
	public CameraBase
{
public:
	PlayerCamera();
	virtual ~PlayerCamera();

	void Init(Vec3 pos);
	void Update(Vec3 pos);

	// �T�u�A�N�^�[���[�h�ƃ��C���A�N�^�[���[�h��ύX����
	void ChangeMode(int mode, Vec3 pos);

	// ���[�h�ؑ֒��ł��邩
	bool IsModeChange();
private:	

	// �֐��|�C���^
	using m_modeFunc_t = void (PlayerCamera::*)(Vec3 pos);
	m_modeFunc_t m_modeFunc = nullptr;

	// ���C���A�N�^�[���[�h
	void MainActorMode(Vec3 pos);

	// �T�u�A�N�^�[���[�h
	void SubActorMode(Vec3 pos);

	// �T�u�A�N�^�[���烁�C���A�N�^�[�ɕύX���鏈��
	void ChangeMainActorMode(Vec3 pos);

	// ��]
	Vec3 RotateMainActorMode(Vec3 pos);	// ���C���A�N�^�[���[�h�ł̉�]����
	Vec3 RotateSubActorMode(Vec3 pos);	// �T�u�A�N�^�[���[�h�ł̉�]����

	// �����̍��W����]������
	VECTOR MakeBasePos(VECTOR base);

	// ���C���A�N�^�[����T�u�ɕύX�����Ƃ��̍��W��ۑ�����
	Vec3 m_savePos;
	Vec3 m_saveTarget;
	Vec3 m_saveAngle;

	// ���C���ɕύX����Ƃ��̒P�ʃx�N�g��
	Vec3 m_unitPos;
	Vec3 m_unitTarget;
	Vec3 m_target;

	// ���[�h�ؑ֒��t���O
	bool m_changeFlag;
};

