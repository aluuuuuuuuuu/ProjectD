#include "Application.h"
#include "SceneManager.h"
#include "DxLib.h"
#include "Input.h"
#include "SceneTest.h"
#include <cassert>
#include "GraphicManager.h"

// 初期化処理
bool Application::Init()
{
	// 外部ファイルから定数を取得する
	assert(ConstantsFileLoad("data/constant/Application.csv", Constants) == 1);

	// ウィンドウモードの設定
	ChangeWindowMode(true);

	// ウィンドウ名の設定
	SetWindowText("ProjectD");

	// 画面サイズの設定
	SetGraphMode(static_cast<int>(Constants["SCREEN_WIDTH"]),
		static_cast<int>(Constants["SCREEN_HEIGHT"]),
		static_cast<int>(Constants["COLRO_BIT"]));

	// 解像度の設定
	SetWindowSize(static_cast<int>(Constants["RESOLUTION_WIDTH"]),
		static_cast<int>(Constants["RESOLUTION_HEIGHT"]));

	// 背面の描画を行わない
	SetUseBackCulling(true);

	// ライティングを使用する
	SetUseLighting(true);

	// ニアレストネイバー法で描画する
	SetDrawMode(DX_DRAWMODE_NEAREST);

	// Dxlibの初期化
	if (DxLib_Init() == -1) return false;

	// バックバッファに描画する
	SetDrawScreen(DX_SCREEN_BACK);

	// カーソルの表示設定
	SetMouseDispFlag(true);

	// 画像のロード
	assert(GraphicManager::getInstance().LoadGraphics() == 1);

	return true;
}

// メイン処理
void Application::Run()
{
	// シーンマネージャーのインスタンスを取得
	auto& manager = SceneManager::getInstance();

	// 初期シーンを設定
	manager.ChangeScene(std::make_shared <SceneTest>());

	// インプットのインスタンスを取得
	auto& input = Input::getInstance();

	// インプットの初期処理
	input.Init();

	// ゲームループ
	while (ProcessMessage() != -1)
	{
		// フレームの開始時刻を覚えておく
		LONGLONG start = GetNowHiPerformanceCount();

		// Zバッファを使用して書き込む
		SetUseZBuffer3D(true);
		SetWriteZBuffer3D(true);

		// 描画を行う前に画面をクリアする
		ClearDrawScreen();

		/*ゲーム処理*/

		// 更新処理
		input.Update();
		manager.SceneUpdate();

		manager.SceneDraw();

		// 画面が切り替わるのを待つ
		ScreenFlip();

		// managerのフラグでゲームを終了させる
		if (manager.GetGameEnd()) break;

		// escで終了（仮）
		if (CheckHitKey(KEY_INPUT_ESCAPE)) {
			break;
		}

		// FPS60に固定する
		while (GetNowHiPerformanceCount() - start < 16667) {}
	}
}

// 終了処理
void Application::Terminate()
{
	DxLib_End();	// DxLibの終了処理
}
