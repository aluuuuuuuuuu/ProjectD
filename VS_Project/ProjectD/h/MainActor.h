#pragma once
#include "CharactorBase.h"

class MainActor:
	public CharactorBase
{
public:
	MainActor();
	~MainActor();

	void Update();
	void Draw() const;

	void Control(Vec3 angle);
private:

	// �A�j���[�V�����ύX
	void AnimationControl();

	// �ړ���������ɉ�]����
	void RotateAngle(float cameraAngle);

};

