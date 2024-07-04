#pragma once
#include <string>
#include <map>

using namespace std;

struct Function
{
	// 定数のCSVファイルをmapに入力する関数
	static int ConstantsFileLoad(const char* fileName,map<string, float>& constants);
};