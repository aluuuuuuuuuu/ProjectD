#pragma once
#include "Singleton.h"
#include <map>
#include <string>

class GraphicManager:
	public Singleton<GraphicManager>
{
	friend class Singleton<GraphicManager>;

public:

	// すべての画像をロードする
	int LoadGraphics();

	// すべての画像をデリートする
	void DeleteGraphics();

	// 画像を提供する
	int GetGraph(std::string name);

private:
	// プレイベートコンストラクタ
	GraphicManager() {};

	std::map<std::string, int> m_graphics;
};

