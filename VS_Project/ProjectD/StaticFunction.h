#pragma once
#include <string>
#include <map>

using namespace std;

struct Function
{
	// ’è”‚ÌCSVƒtƒ@ƒCƒ‹‚ğmap‚É“ü—Í‚·‚éŠÖ”
	static int ConstantsFileLoad(const char* fileName,map<string, float>& constants);
};