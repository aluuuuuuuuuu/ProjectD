#pragma once
#include "Components.h"
#include "Singleton.h"
#include "Constant.h"

#define OS_MODE 0
#define BRUTUS_MODE 1
#define SEQUENCE_MODE 2

// �J�����N���X
class Camera :
	public Transform,
	public Constant,
	public Singleton<Camera>
{
	friend class Singleton<Camera>;

public:
	~Camera();

	void Init(Vec3 pos);
	void Update(Vec3 pos);

	// �I�Y���[�h�ƃu���[�^�X���[�h��ύX����
	void ChangeMode(int mode);

private:
	Camera() {};

	// �֐��|�C���^
	using m_modeFunc_t = void (Camera::*)(Vec3 pos);
	m_modeFunc_t m_modeFunc = nullptr;

	// �u���[�^�X���[�h
	void BrutusMode(Vec3 pos);

	// �I�Y���[�h
	void OsMode(Vec3 pos);

	// �V�[�P���X���[�h
	void SequMode(Vec3 pos);

	// ��]
	void RotateBrutus(Vec3 pos);	// �u���[�^�X���[�h�ł̉�]����
	Vec3 RotateOs(Vec3 pos);	// �I�Y���[�h�ł̉�]����
};

