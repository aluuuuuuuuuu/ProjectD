#pragma once
#include "Components.h"
#include "Constant.h"
#include <vector>
#include <memory>

class StaticObjectManager;
class MapCollisionManager:
	public Constant
{
public:
	MapCollisionManager(CapsuleData& cap,StaticObjectManager& manager);
	virtual ~MapCollisionManager();

	// �v���C���[�ƐÓI�I�u�W�F�N�g�̓����蔻����Ƃ��Ĉړ�����x�N�g����Ԃ�
	Vec3 PlayerCollision();

	// �}�b�v�̓�������̃e�X�g�\��
	void DrawColl();

	// ���i�̕`��
	void DrawBoxColl(Vec3 min, Vec3 max);

private:

	// �ŋߐړ_�����߂�֐�
	Vec3 ClosestPointOnLineSegment(Vec3 A, Vec3 B, Vec3 Point);

	// �������v�Z����֐�
	float DistanceSquared(Vec3 A, Vec3 B);

	// �������Ă��邩�ǂ������肷��
	bool CheckCollisionCapsuleAABB(Vec3 min, Vec3 max, Vec3 center);

	// �v���C���[�̃J�v�Z���̏��
	CapsuleData& m_playerCapsule;

	// �ÓI�I�u�W�F�N�g�}�l�[�W���[�̎Q��
	StaticObjectManager& m_staticObjectManager;
};

