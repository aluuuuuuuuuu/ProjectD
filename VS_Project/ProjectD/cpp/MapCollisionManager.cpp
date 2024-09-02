#include "MapCollisionManager.h"
#include "StaticObjectManager.h"
#include "StaticObjectBase.h"
#include "DxLib.h"
#include <cassert>
#include <cmath>
#include <algorithm>

MapCollisionManager::MapCollisionManager(CapsuleData& cap, StaticObjectManager& manager):
	m_playerCapsule(cap),
	m_staticObjectManager(manager)
{
	// �O���t�@�C������萔���擾����
	assert(ConstantsFileLoad("data/constant/Collision.csv", Constants) == 1);
}

MapCollisionManager::~MapCollisionManager()
{

}

Vec3 MapCollisionManager::PlayerCollision()
{
	// �v���C���[�ƃI�u�W�F�N�g�̓����蔻����Ƃ�
	for (std::shared_ptr<StaticObjectBase> obj : m_staticObjectManager.m_pStaticObject) {
		Vec3 pos = obj->Position;
		// �I�u�W�F�N�g�̎�ނ���肷��
		if (obj->m_code == WALL_CODE) {

			if (CheckCollisionCapsuleAABB(Vec3(pos.x - Constants["WALL_X"], pos.y, pos.z - Constants["WALL_Z"]),
				Vec3(pos.x + Constants["WALL_X"], pos.y + Constants["WALL_Y"], pos.z + Constants["WALL_Z"]),
				Vec3(pos.x, pos.y + Constants["WALL_Y / 2"], pos.z))) {
				printfDx("����������");

			}
		}
		else if (obj->m_code == FLOOR_CODE) {

		}

	}
	return Vec3{ 0,0,0 };
}

Vec3 MapCollisionManager::ClosestPointOnLineSegment(Vec3 A, Vec3 B, Vec3 Point)
{
	// AB�x�N�g��
	Vec3 AB = B - A;
	// �_����A�܂ł̃x�N�g��
	Vec3 AP = Point - A;
	// �_���������̍ŋߐړ_�܂ł̃p�����[�^t
	float t = AP.dot(AB) / AB.dot(AB);
	// t��0�`1�͈̔͂ɐ����i������Ɏ��܂�悤�Ɂj
	t = (std::max)(0.0f, (std::min)(1.0f, t));
	// �ŋߐړ_�̍��W���v�Z
	return A + AB * t;
}

float MapCollisionManager::DistanceSquared(Vec3 A, Vec3 B)
{
	Vec3 diff = A - B;
	return diff.dot(diff);
}

bool MapCollisionManager::CheckCollisionCapsuleAABB(Vec3 min, Vec3 max, Vec3 center)
{

	// �J�v�Z���̐����ɑ΂���{�b�N�X���S�̍ŋߐړ_�����߂�
	Vec3 closestPoint = ClosestPointOnLineSegment(m_playerCapsule.PointA, m_playerCapsule.PointB, center);

	// �ŋߐړ_�ƃ{�b�N�X�Ƃ̋������v�Z����
	float distanceSquared = DistanceSquared(closestPoint, center);

	// �������J�v�Z���̔��a��2��������������ǂ������`�F�b�N
	return distanceSquared <= (m_playerCapsule.Radius * m_playerCapsule.Radius);
}

void MapCollisionManager::DrawColl()
{
	for (std::shared_ptr<StaticObjectBase> obj : m_staticObjectManager.m_pStaticObject) {
		Vec3 pos = obj->Position;
		// �I�u�W�F�N�g�̎�ނ���肷��
		if (obj->m_code == WALL_CODE) {
			DrawBoxColl(Vec3(pos.x - Constants["WALL_X"], pos.y, pos.z - Constants["WALL_Z"]), 
						Vec3(pos.x + Constants["WALL_X"], pos.y + Constants["WALL_Y"], pos.z + Constants["WALL_Z"]));
		}
		else if (obj->m_code == FLOOR_CODE) {

		}

	}
}

void MapCollisionManager::DrawBoxColl(Vec3 min, Vec3 max)
{
	// �ŏ��l����y��
	DrawLine3D(min.VGet(), VECTOR{ min.x,max.y,min.z },0xff0000);

	// �ŏ��l����x��
	DrawLine3D(min.VGet(), VECTOR{ max.x,min.y,min.z }, 0xff0000);

	// �ŏ��l����z��
	DrawLine3D(min.VGet(), VECTOR{ min.x,min.y,max.z }, 0xff0000);

	// �ő�l����y��
	DrawLine3D(max.VGet(), VECTOR{ max.x,min.y,max.z }, 0xff0000);

	// �ő�l����x��
	DrawLine3D(max.VGet(), VECTOR{ min.x,max.y,max.z }, 0xff0000);

	// �ő�l����z��
	DrawLine3D(max.VGet(), VECTOR{ max.x,max.y,min.z }, 0xff0000);
}
