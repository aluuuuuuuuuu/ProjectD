#include "Application.h"
#include "SceneManager.h"
#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include "Input.h"
#include "SceneTest.h"
#include <cassert>
#include "GraphicManager.h"
#include "SceneTitle.h"
#include "SceneSelect.h"

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

	// ライトのカラーを調整する
	SetLightDifColor(GetColorF(0.9f, 0.9f, 0.9f, 0.0f));

	// ニアレストネイバー法で描画する
	SetDrawMode(DX_DRAWMODE_NEAREST);

	// DirectX11を使用するようにする。(DirectX9も可、一部機能不可)
	// Effekseerを使用するには必ず設定する。
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	// Dxlibの初期化
	if (DxLib_Init() == -1) return false;

	// Effekseerを初期化する。
	// 引数には画面に表示する最大パーティクル数を設定する。
	if (Effekseer_Init(8000) == -1)
	{
		DxLib_End();
		return -1;
	}

	// エフェクサーの歪みを初期化する
	Effekseer_InitDistortion(1.0f);

	// フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// DXライブラリのデバイスロストした時のコールバックを設定する。
	// ウインドウとフルスクリーンの切り替えが発生する場合は必ず実行する。
	// ただし、DirectX11を使用する場合は実行する必要はない。
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	// Effekseerに2D描画の設定をする。
	Effekseer_Set2DSetting(1920, 1080);

	// フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
	// Effekseerを使用する場合は必ず設定する。
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// バックバッファに描画する
	SetDrawScreen(DX_SCREEN_BACK);

	// 背景色の設定
	SetBackgroundColor(20, 20, 200);

	// カーソルの表示設定
	SetMouseDispFlag(true);

	// Zバッファを有効にする。
	// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
	SetUseZBuffer3D(TRUE);

	// Zバッファへの書き込みを有効にする。
	// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
	SetWriteZBuffer3D(TRUE);

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

		// DXライブラリのカメラとEffekseerのカメラを同期する。
		Effekseer_Sync3DSetting();

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

	// 終了処理を行う
	Terminate();
}

// 終了処理
void Application::Terminate()
{
	// Effekseerを終了する。
	Effkseer_End();

	DxLib_End();	// DxLibの終了処理
}
