#pragma once
#include <string>
#include <map>

using namespace std;

struct Function
{
	// �萔��CSV�t�@�C����map�ɓ��͂���֐�
	static int ConstantsFileLoad(const char* fileName,map<string, float>& constants);
};