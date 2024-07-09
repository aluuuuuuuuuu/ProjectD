#include "Constant.h"
#include <fstream>
#include <sstream>

int Constant::ConstantsFileLoad(const char* fileName, std::map<std::string, float>& constants)
{
	// ファイルを開く
	std::ifstream file(fileName);

	// ファイルが開けなかったら-1を返す
	if (!file.is_open()) {
		return -1;
	}

	// 最後の行まで繰り返す
	std::string line;
	while (getline(file, line)) {

		// 行をとる
		std::stringstream stream(line);

		// 要素の内容を作成する
		std::string name;
		float value;

		// カンマで行を分割し定数名と値を格納する
		if (getline(stream, name, ',') && stream >> value) {
			constants[name] = value;
		}
	}

	// ファイルを閉じる
	file.close();

	// 終了したら1を返す
	return 1;
}
