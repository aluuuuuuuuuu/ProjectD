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
#include "StaticObjectManager.h"
#include "MapCollisionManager.h"

SceneTest::SceneTest()
{
	// エネミーマネージャーの作成
	m_pEnemyManager = make_shared<EnemyManager>();

	// ディレクションインスタンスの作成
	m_pDirection = make_shared<Direction>();

	// プレイヤーのインスタンスの作成
	m_pPlayer = make_shared<Player>(m_pDirection,m_pEnemyManager->GetEnemy());

	// スタティックオブジェクトマネージャーのインスタンスの作成
	m_pStaticObject = make_shared<StaticObjectManager>();

	// スタティックオブジェクトマネージャーの初期処理
	m_pStaticObject->InitTest();

	// コリジョンマネージャーの作成
	m_pCollisionManager = make_shared<MapCollisionManager>(m_pPlayer->GetCupsule(),*m_pStaticObject);

	// エネミーを追加する
	m_pEnemyManager->AddEnemy(Vec3{ 60,0,60 }, m_pPlayer, m_pStaticObject);

	m_pEnemyManager->AddEnemy(Vec3{ 60,0,30 }, m_pPlayer, m_pStaticObject);
	m_updateFunc = &SceneTest::NormalUpdate;
	m_drawFunc = &SceneTest::NormalDraw;
}

SceneTest::~SceneTest()
{
}

void SceneTest::Update()
{
	(this->*m_updateFunc)();

	// エフェクトの更新処理
	UpdateEffekseer2D();
}

void SceneTest::Draw() const
{
	// グリッドの表示
	//DrawGrid();

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
	m_pEnemyManager->Update();

	// プレイヤーの更新
	m_pPlayer->Update();

	m_pPlayer->CollisionMove(m_pCollisionManager->PlayerCollision());
	m_pCollisionManager->DrawColl();

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
	// スタティックオブジェクトの描画
	m_pStaticObject->Draw(m_pPlayer->GetPos());

	// エネミーの描画
	m_pEnemyManager->Draw();

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

		// 気絶フラグが立っていたらプレイヤーをメインアクターに変更する
		if (m_pDirection->IsFaintEnemy()) {
			m_pPlayer->ChangeMode();
		}

		// 通常の処理に移行する
		m_updateFunc = &SceneTest::NormalUpdate;
		m_drawFunc = &SceneTest::NormalDraw;
	}
}

void SceneTest::SeqDraw() const
{
	// スタティックオブジェクトの描画
	m_pStaticObject->Draw(m_pPlayer->GetPos());

	// エネミーの描画
	m_pEnemyManager->Draw();

	// プレイヤーの描画
	m_pPlayer->Draw();

	// UIの描画
	UI::getInstance().Draw();

	// ディレクションの描画処理
	m_pDirection->Draw();
}
