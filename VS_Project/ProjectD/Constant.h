#pragma once
#include <map>
#include <string>

class Constant
{
public:

	// ファイルから定数をロードする
	int ConstantsFileLoad(const char* fileName, std::map<std::string, float>& constants);

	// 定数マップ
	std::map < std::string, float > Constants;
};
