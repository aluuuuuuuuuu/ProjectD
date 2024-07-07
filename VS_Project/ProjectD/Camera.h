#pragma once
#include "Components.h"
#include "Singleton.h"
#include "Constant.h"

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
	void ChangeMode(bool osFlug);

private:
	Camera() {};

	// �֐��|�C���^
	using m_modeFunc_t = void (Camera::*)(Vec3 pos);
	m_modeFunc_t m_modeFunc = nullptr;

	// �u���[�^�X���[�h
	void BrutusMode(Vec3 pos);

	// �I�Y���[�h
	void OsMode(Vec3 pos);

	// ��]
	void RotateBrutus(Vec3 pos);	// �u���[�^�X���[�h�ł̉�]����
	Vec3 RotateOs(Vec3 pos);	// �I�Y���[�h�ł̉�]����
};

