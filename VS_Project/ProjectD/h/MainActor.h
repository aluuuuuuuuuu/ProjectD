#pragma once
#include "CharactorBase.h"

class MainActor:
	public CharactorBase,
	private Model,
	private Animation
{
public:
	MainActor();
	~MainActor();

	void Update();
	void Draw() const;

	void Control(Vec3 angle);
private:

	// �A�j���[�V�����ύX
	void ChangeAnimation();

	// �ړ���������ɉ�]����
	void RotateAngle(float cameraAngle);

};

