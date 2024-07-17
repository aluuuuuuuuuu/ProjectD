#include "SceneTest.h"
#include "DxLib.h"
#include "StaticFunction.h"
#include "Player.h"
#include "Singleton.h"
#include "EnemyManager.h"
#include "EnemyTest.h"
#include "UI.h"
#include "Direction.h"
#include "EffekseerForDXLib.h"

SceneTest::SceneTest()
{
	// ディレクションインスタンスの作成
	m_pDirection = make_shared<Direction>();

	// プレイヤーのインスタンスの作成
	m_pPlayer = make_shared<Player>(m_pDirection);

	// エネミーを追加する
	EnemyManager::getInstance().AddEnemy<EnemyTest>(Vec3{ 60,0,60 });
	EnemyManager::getInstance().AddEnemy<EnemyTest>(Vec3{ 60,0,30 });
	m_updateFunc = &SceneTest::NormalUpdate;
	m_drawFunc = &SceneTest::NormalDraw;
}

SceneTest::~SceneTest()
{
}

void SceneTest::Update()
{
	(this->*m_updateFunc)();
}

void SceneTest::Draw() const
{
	// グリッドの表示
	DrawGrid();

	(this->*m_drawFunc)();
}

void SceneTest::DrawGrid() const
{
	for (int x = -100; x <= 100; x += 10)
	{
		DrawLine3D(VGet(static_cast<float>(x), 0, -100), VGet(static_cast<float>(x), 0, 100), 0xffff00);
	}
	for (int z = -100; z <= 100; z += 10)
	{
		DrawLine3D(VGet(-100, 0, static_cast<float>(z)), VGet(100, 0, static_cast<float>(z)), 0xff0000);
	}

	// X+-,Z+-の方向が分かりやすいように表示を追加する
	VECTOR dispPos = ConvWorldPosToScreenPos(VGet(50, 0, 0));
	if (dispPos.z >= 0.0f && dispPos.z <= 1.0f)
	{
		DrawStringF(dispPos.x, dispPos.y, "X+", 0xffffff);
	}

	dispPos = ConvWorldPosToScreenPos(VGet(-50, 0, 0));
	if (dispPos.z >= 0.0f && dispPos.z <= 1.0f)
	{
		DrawStringF(dispPos.x, dispPos.y, "X-", 0xffffff);
	}

	dispPos = ConvWorldPosToScreenPos(VGet(0, 0, 50));
	if (dispPos.z >= 0.0f && dispPos.z <= 1.0f)
	{
		DrawStringF(dispPos.x, dispPos.y, "Z+", 0xffffff);
	}

	dispPos = ConvWorldPosToScreenPos(VGet(0, 0, -50));
	if (dispPos.z >= 0.0f && dispPos.z <= 1.0f)
	{
		DrawStringF(dispPos.x, dispPos.y, "Z-", 0xffffff);
	}
}

void SceneTest::NormalUpdate()
{
	// エネミーの更新
	EnemyManager::getInstance().Update();

	// プレイヤーの更新
	m_pPlayer->Update();

	// UIの更新
	UI::getInstance().Update();

	// シーケンス移行処理
	if (m_pDirection->IsPlaySequ()) {
		m_updateFunc = &SceneTest::SeqUpdate;
		m_drawFunc = &SceneTest::SeqDraw;
	}

}

void SceneTest::NormalDraw() const
{
	// エネミーの描画
	EnemyManager::getInstance().Draw();

	// プレイヤーの描画
	m_pPlayer->Draw();

	// UIの描画
	UI::getInstance().Draw();

	
}

void SceneTest::SeqUpdate()
{
	m_pPlayer->Update();
	m_pDirection->Update();
	UI::getInstance().Update();

	// シーケンス終了処理
	if (!m_pDirection->IsPlaySequ()) {
		m_updateFunc = &SceneTest::NormalUpdate;
		m_drawFunc = &SceneTest::NormalDraw;
	}
}

void SceneTest::SeqDraw() const
{
	// エネミーの描画
	EnemyManager::getInstance().Draw();

	// プレイヤーの描画
	m_pPlayer->Draw();

	// UIの描画
	UI::getInstance().Draw();

	// ディレクションの描画処理
	m_pDirection->Draw();
}
