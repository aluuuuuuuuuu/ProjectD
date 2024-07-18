#include "SubActor.h"
#include "Input.h"
#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include <cassert>
#include <memory>
#include "EnemyManager.h"
#include "EnemyBase.h"
#include "Application.h"
#include "UI.h"

SubActor::SubActor():
	m_flame(0)
{
	// 外部ファイルから定数を取得する
	assert(ConstantsFileLoad("data/constant/SubActor.csv", Constants) == 1);

	// 歪みエフェクトをロード
	m_effectDistortionHandle = LoadEffekseerEffect("data/effect/test.efkefc", 120.0f);

	// 歪みエフェクトを発生させる
	m_effectDistortionHandle = PlayEffekseer2DEffect(m_effectDistortionHandle);
}

SubActor::~SubActor()
{
	DeleteEffekseerEffect(m_effectDistortionHandle);
}

void SubActor::Update()
{
	// 近くのエネミーを探してUIにデータを渡す
	auto enemy = FindEnemy();
	if (enemy == nullptr) {
		UI::getInstance().SetEnemyInteractFlag(false);
	}
	else {
		UI::getInstance().SetEnemyInteractFlag(true);
		UI::getInstance().SetEnemyInteractPos(enemy->Position);

		//　敵の座標をシーケンスに渡す
		m_enemyPos = enemy->Position;
	}

	// サインカーブを使用して常に上下にふわふわと動かす
	float move = 0.1f * sin(m_flame);
	m_flame += 0.01f;

	Position.y += move;

	SetPosPlayingEffekseer2DEffect(m_effectDistortionHandle, 960, 540, 0);
}

void SubActor::Draw() const
{
	// 歪みエフェクトを描画する
	DrawEffekseer2D_Draw(m_effectDistortionHandle);
}

Vec3 SubActor::GetEnemyPos()
{
	return m_enemyPos;
}

void SubActor::ChangeInit(Vec3 cameraPos, Vec3 mainActorPos)
{
	// メインアクター操作時のカメラの座標がそのままオズの初期座標になる
	Position = cameraPos;

	// メインアクターの座標を保存する
	m_mainActorPos = mainActorPos;
}

void SubActor::Control(Vec3 cameraRot)
{
	// インプットのインスタンスを取得
	auto& input = Input::getInstance();

	// 移動ベクトルの初期化
	m_moveVec = 0;

	// 平行移動
	if (input.GetStickVectorLength(INPUT_LEFT_STICK) > input.Constants["STICK_INVALID_VALUE"]) {

		// スティックの単位ベクトルに移動量をかけた値を代入
		m_moveVec = input.GetStickUnitVector(INPUT_LEFT_STICK) * Constants["HORIZONTAL_MOVE_SCALE"];

		// カメラの回転を得る
		Angle.y = cameraRot.y;

		// Y軸回転行列に変換
		MATRIX rotaMtx = MGetRotY(Angle.y);

		// 傾きの方向が逆なので反転させる
		Vec3 inclination = input.GetStickUnitVector(INPUT_LEFT_STICK) * -1;

		// スティックの傾きをカメラに合わせてY軸回転させる
		m_moveVec = VTransform(inclination.VGet(), rotaMtx);
	}

	// 垂直移動
	// RBで上昇
	if (input.IsHold(INPUT_RIGHT_SHOULDER)) {
		// 移動ベクトルのY値を加算する
		m_moveVec.y += Constants["VERTICAL_MOVE_SCALE"];
	}
	// RTで下降
	if (input.IsHold(INPUT_RIGHT_TRIGGER)) {
		// 移動ベクトルのY値を減算する
		m_moveVec.y += -Constants["VERTICAL_MOVE_SCALE"];
	}

	// 作成した移動ベクトルを単位化する
	m_moveVec.Normalize();

	// 現在の座標に移動ベクトルを足す
	Position += m_moveVec;

	// 移動した後移動可能範囲外に出ていたら位置を戻す
	float dist = (Position - m_mainActorPos).Length();
	if (dist >= Constants["MOVABLE_RANGE"]) {
		Position -= m_moveVec;
	}
}

std::shared_ptr<EnemyBase> SubActor::FindEnemy()
{
	std::list<std::shared_ptr<EnemyBase>> enemyList;

	// 範囲内の敵を配列におさめる
	for (std::shared_ptr<EnemyBase> enemy : EnemyManager::getInstance().GetEnemy()) {
		if ((enemy->Position - Position).Length() <= Constants["EFFECTIVE_RANGE"]) {
			enemyList.push_back(enemy);
		}
	}

	// 範囲内に敵がいなければnullを返す
	if (enemyList.size() == 0) {
		return nullptr;
	}

	// 範囲内の敵から画面外にいる敵を排除する
	for (auto it = enemyList.begin(); it != enemyList.end();) {
		VECTOR pos = ConvWorldPosToScreenPos((*it)->Position.VGet());
		if (pos.x < 0 || pos.x > Application::getInstance().Constants["SCREEN_WIDTH"] ||
			pos.y < 0 || pos.y > Application::getInstance().Constants["SCREEN_HEIGHT"]) {
			it = enemyList.erase(it);
		}
		else {
			it++;
		}
	}

	// 画面内に敵がいなければnullを返す
	if (enemyList.size() == 0) {
		return nullptr;
	}

	// サブアクターに最も近い敵を取り出す
	auto max = enemyList.front();
	for (std::shared_ptr<EnemyBase> enemy : EnemyManager::getInstance().GetEnemy()) {
		if ((max->Position - Position).Length() > (enemy->Position - Position).Length()) {
			max = enemy;
		}
	}

	return max;
}
