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

	void Init();
	void Update(Vec3 pos);

private:
	Camera() {};

	// ��]
	void Rotate(Vec3 pos);

	// �����O�̍��W
	Vec3 m_beforePos;
};

