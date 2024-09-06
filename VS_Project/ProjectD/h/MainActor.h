#pragma once
#include "CharactorBase.h"

class MainActor:
	public CharactorBase,
	public CapsuleCollision
{
public:
	MainActor();
	~MainActor();

	void Update();
	void Draw() const;

	void Control(Vec3 angle);
private:

	// �����Ă��Ȃ��Ƃ��͓����蔻��̃T�C�Y������������
	void MakeSmallerCollision();

	// �A�j���[�V�����ύX
	void AnimationControl();

	// �ړ���������ɉ�]����
	void RotateAngle(float cameraAngle);

};

