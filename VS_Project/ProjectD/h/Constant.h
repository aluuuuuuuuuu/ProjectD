#pragma once
#include <map>
#include <string>
#include <variant>

// 変数型
enum MyDataType { _INT, _FLOAT, _BOOL, _STRING };

// 定数管理クラス
class Constant
{
	// 定数を格納するための型
	using ConstantVariant = std::variant<int, float, bool, std::string>;

public:

	// 定数mapを得る
	std::map<std::string, ConstantVariant> GetConstants();
	
	// 定数を取得する
	std::variant<int, float, bool, std::string> GetConstant(const std::string& name);

	// 定数を格納するmap配列
	std::map<std::string, ConstantVariant> Constants;
protected:

	// CSVから定数を読み込む
	void ReadCSV(const std::string& filename);

	
private:
	

	// 引数の文字列から変数型を推測する
	MyDataType GetDataType(const std::string& type);

};
