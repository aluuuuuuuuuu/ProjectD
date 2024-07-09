#pragma once
#include "CharactorBase.h"
#include <memory>

class EnemyBase;
class Os :
	public CharactorBase
{
public:
	Os();
	~Os();

	void Update();
	void Draw() const;

	// 操作を変更したときの初期処理
	void ChangeInit(Vec3 pos);

	void Control();
private:
	// インタラクトする敵を探す関数
	std::shared_ptr<EnemyBase> FindEnemy();

	// ブルータスの座標
	Vec3 m_brutusPos;
};