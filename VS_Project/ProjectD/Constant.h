#pragma once
#include <map>
#include <string>

class Constant
{
public:

	// �t�@�C������萔�����[�h����
	int ConstantsFileLoad(const char* fileName, std::map<std::string, float>& constants);

	// �萔�}�b�v
	std::map < std::string, float > Constants;
};
