#pragma once
#include "CharactorBase.h"
#include <memory>

class EnemyBase;
class SubActor :
	public CharactorBase
{
public:
	SubActor(std::list<std::shared_ptr<EnemyBase>> enemy);
	virtual ~SubActor();

	void Update();
	void Draw() const;

	// インタラクトする敵のポインタを返す
	std::shared_ptr<EnemyBase> GetEnemyPtr();

	// 操作を変更したときの初期処理
	void ChangeInit(Vec3 cameraPos, Vec3 mainActorPos);

	void Control(Vec3 cameraRot);
private:
	// インタラクトする敵を探す関数
	std::shared_ptr<EnemyBase> FindEnemy();

	// メインアクターの座標
	Vec3 m_mainActorPos;
	
	// インタラクトできる敵の座標
	std::shared_ptr<EnemyBase> m_enemyPtr;

	// サインカーブ用のフレーム
	float m_flame;

	std::list<std::shared_ptr<EnemyBase>>& m_enemyManager;
};