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
	// 外部ファイルから定数を取得する
	assert(ConstantsFileLoad("data/constant/Collision.csv", Constants) == 1);
}

MapCollisionManager::~MapCollisionManager()
{

}

Vec3 MapCollisionManager::PlayerCollision()
{
	// プレイヤーとオブジェクトの当たり判定をとる
	for (std::shared_ptr<StaticObjectBase> obj : m_staticObjectManager.m_pStaticObject) {
		Vec3 pos = obj->Position;
		// オブジェクトの種類を特定する
		if (obj->m_code == WALL_CODE) {

			if (CheckCollisionCapsuleAABB(Vec3(pos.x - Constants["WALL_X"], pos.y, pos.z - Constants["WALL_Z"]),
				Vec3(pos.x + Constants["WALL_X"], pos.y + Constants["WALL_Y"], pos.z + Constants["WALL_Z"]),
				Vec3(pos.x, pos.y + Constants["WALL_Y / 2"], pos.z))) {
				printfDx("あったった");

			}
		}
		else if (obj->m_code == FLOOR_CODE) {

		}

	}
	return Vec3{ 0,0,0 };
}

Vec3 MapCollisionManager::ClosestPointOnLineSegment(Vec3 A, Vec3 B, Vec3 Point)
{
	// ABベクトル
	Vec3 AB = B - A;
	// 点からAまでのベクトル
	Vec3 AP = Point - A;
	// 点から線分上の最近接点までのパラメータt
	float t = AP.dot(AB) / AB.dot(AB);
	// tを0～1の範囲に制限（線分上に収まるように）
	t = (std::max)(0.0f, (std::min)(1.0f, t));
	// 最近接点の座標を計算
	return A + AB * t;
}

float MapCollisionManager::DistanceSquared(Vec3 A, Vec3 B)
{
	Vec3 diff = A - B;
	return diff.dot(diff);
}

bool MapCollisionManager::CheckCollisionCapsuleAABB(Vec3 min, Vec3 max, Vec3 center)
{

	// カプセルの線分に対するボックス中心の最近接点を求める
	Vec3 closestPoint = ClosestPointOnLineSegment(m_playerCapsule.PointA, m_playerCapsule.PointB, center);

	// 最近接点とボックスとの距離を計算する
	float distanceSquared = DistanceSquared(closestPoint, center);

	// 距離がカプセルの半径の2乗よりも小さいかどうかをチェック
	return distanceSquared <= (m_playerCapsule.Radius * m_playerCapsule.Radius);
}

void MapCollisionManager::DrawColl()
{
	for (std::shared_ptr<StaticObjectBase> obj : m_staticObjectManager.m_pStaticObject) {
		Vec3 pos = obj->Position;
		// オブジェクトの種類を特定する
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
	// 最小値からy軸
	DrawLine3D(min.VGet(), VECTOR{ min.x,max.y,min.z },0xff0000);

	// 最小値からx軸
	DrawLine3D(min.VGet(), VECTOR{ max.x,min.y,min.z }, 0xff0000);

	// 最小値からz軸
	DrawLine3D(min.VGet(), VECTOR{ min.x,min.y,max.z }, 0xff0000);

	// 最大値からy軸
	DrawLine3D(max.VGet(), VECTOR{ max.x,min.y,max.z }, 0xff0000);

	// 最大値からx軸
	DrawLine3D(max.VGet(), VECTOR{ min.x,max.y,max.z }, 0xff0000);

	// 最大値からz軸
	DrawLine3D(max.VGet(), VECTOR{ max.x,max.y,min.z }, 0xff0000);
}
