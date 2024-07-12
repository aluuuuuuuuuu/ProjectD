#pragma once
#include "CameraBase.h"

#define OS_MODE 0
#define BRUTUS_MODE 1

class PlayerCamera :
	public CameraBase
{
public:
	PlayerCamera();
	virtual ~PlayerCamera();

	void Init(Vec3 pos);
	void Update(Vec3 pos);

	// �T�u�A�N�^�[���[�h�ƃ��C���A�N�^�[���[�h��ύX����
	void ChangeMode(int mode);
private:	

	// �֐��|�C���^
	using m_modeFunc_t = void (PlayerCamera::*)(Vec3 pos);
	m_modeFunc_t m_modeFunc = nullptr;

	// ���C���A�N�^�[���[�h
	void MainActorMode(Vec3 pos);

	// �T�u�A�N�^�[���[�h
	void SubActorMode(Vec3 pos);

	// ��]
	Vec3 RotateMainActorMode(Vec3 pos);	// ���C���A�N�^�[���[�h�ł̉�]����
	Vec3 RotateSubActorMode(Vec3 pos);	// �T�u�A�N�^�[���[�h�ł̉�]����
};

