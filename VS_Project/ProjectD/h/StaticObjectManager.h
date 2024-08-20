#pragma once
#include <vector>
#include <memory>
#include "Vec3.h"

class StaticObjectBase;
class StaticObject;
class StaticObjectManager
{
public:
	StaticObjectManager();
	virtual ~StaticObjectManager();

	// テストステージでの初期処理
	void InitTest();

	// ステージ１での初期処理
	void InitStage1();

	void Draw(Vec3 plPos) const;
private:
	std::vector<std::shared_ptr<StaticObjectBase>> m_pStaticObject;

	// 壁オブジェクトのモデルハンドル
	int m_wallHandle;
};

