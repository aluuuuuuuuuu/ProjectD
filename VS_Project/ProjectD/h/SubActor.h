#pragma once
#include "CharactorBase.h"
#include <memory>

class EnemyBase;
class SubActor :
	public CharactorBase
{
public:
	SubActor();
	~SubActor();

	void Update();
	void Draw() const;

	// インタラクトする敵の座標を返す
	Vec3 GetEnemyPos();

	// 操作を変更したときの初期処理
	void ChangeInit(Vec3 cameraPos, Vec3 mainActorPos);

	void Control(Vec3 cameraRot);
private:
	// インタラクトする敵を探す関数
	std::shared_ptr<EnemyBase> FindEnemy();

	// メインアクターの座標
	Vec3 m_mainActorPos;
	
	// インタラクトできる敵の座標
	Vec3 m_enemyPos;

	// サインカーブ用のフレーム
	float m_flame;

	// シェーダーハンドル
	int m_shaderHandle;

	// シェーダー用の定数バッファ
	int m_constBufferHandle;

	// シェーダー用のテクスチャ
	int m_textureHandlel;
};