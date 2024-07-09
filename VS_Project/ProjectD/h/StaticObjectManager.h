#pragma once
#include <vector>
#include <memory>
#include "Singleton.h"

class StaticObject;

// 静的なオブジェクトを管理するマネージャー
class StaticObjectManager : public Singleton<StaticObjectManager>
{
	friend class Singleton<StaticObjectManager>;

public:

	void Init();
	void Update();
	void Draw() const;

private:

	// プライベートコンストラクタ
	StaticObjectManager() {};

	// 全てのスタティックオブジェクトを格納する
	std::vector<std::shared_ptr<StaticObject>> m_pObject;
	int model = 0;
	int texture = 0;
};

