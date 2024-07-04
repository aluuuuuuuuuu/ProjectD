#include "DxLib.h"
#include "Application.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	auto& application = Application::getInstance();

	if (!application.Init()) return-1;

	application.Run();

	return 0;
}