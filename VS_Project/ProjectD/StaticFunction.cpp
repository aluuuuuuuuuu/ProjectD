#include "StaticFunction.h"
#include <fstream>
#include <sstream>

// 定数のCSVファイルをmapに入力する関数
int Function::ConstantsFileLoad(const char* fileName, map<string, float>& constants)
{
	// ファイルを開く
	ifstream file(fileName);

	// ファイルが開けなかったら-1を返す
	if (!file.is_open()) {
		return -1;
	}

	// 最後の行まで繰り返す
	string line;
	while (getline(file, line)) {

		// 行をとる
		stringstream stream(line);

		// 要素の内容を作成する
		string name;
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
