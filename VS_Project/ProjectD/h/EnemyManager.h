#pragma once
#include <memory>
#include <list>
#include "Singleton.h"
#include "Vec3.h"

class EnemyBase;
// エネミー全体を管理するシングルトンクラス
class EnemyManager : public Singleton<EnemyManager>
{
	friend class Singleton<EnemyManager>;

public:
	void Init();
	void Update();
	void Draw() const;

	std::list<std::shared_ptr<EnemyBase>> GetEnemy();

	// 指定された種類の敵を配列に追加する
	void AddEnemy(Vec3 pos);
private:
	// プライベートコンストラクタ
	EnemyManager() {};

	// エネミーを格納するリスト配列
	std::list<std::shared_ptr<EnemyBase>> m_pEnemy;

	// エネミーのモデルハンドル
	int m_modelHandle;
};
