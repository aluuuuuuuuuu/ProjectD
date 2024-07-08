#include "GraphicManager.h"
#include <fstream>
#include <sstream>
#include "DxLib.h"

int GraphicManager::LoadGraphics()
{
	// ファイルを開く
	std::ifstream file("data/GraphicCSV/Graphics.csv");

	// ファイルが開けなかったら-1を返す
	if (!file.is_open()) {
		return -1;
	}

	// 最後の行まで繰り返す
	std::string line;
	while (std::getline(file,line)){

		// 行をとる
		std::stringstream stream(line);

		// 要素の内容を作成する
		std::string name, path;

		// カンマで行を分割し画像名とパスを格納する
		if (std::getline(stream, name, ',') && stream >> path) {
			m_graphics[name] = LoadGraph(path.c_str());
		}
	}

	// 終了した場合1を返す
	return 1;
}

void GraphicManager::DeleteGraphics()
{
	for (auto& pair : m_graphics) {
		DeleteGraph(pair.second);
	}
}

int GraphicManager::GetGraph(std::string name)
{
	return m_graphics[name];
}
