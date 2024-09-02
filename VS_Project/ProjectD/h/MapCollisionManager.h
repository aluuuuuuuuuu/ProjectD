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

	// プレイヤーと静的オブジェクトの当たり判定をとって移動するベクトルを返す
	Vec3 PlayerCollision();

	// マップの当た判定のテスト表示
	void DrawColl();

	// 資格の描画
	void DrawBoxColl(Vec3 min, Vec3 max);

private:

	// 最近接点を求める関数
	Vec3 ClosestPointOnLineSegment(Vec3 A, Vec3 B, Vec3 Point);

	// 距離を計算する関数
	float DistanceSquared(Vec3 A, Vec3 B);

	// 当たっているかどうか判定する
	bool CheckCollisionCapsuleAABB(Vec3 min, Vec3 max, Vec3 center);

	// プレイヤーのカプセルの情報
	CapsuleData& m_playerCapsule;

	// 静的オブジェクトマネージャーの参照
	StaticObjectManager& m_staticObjectManager;
};

