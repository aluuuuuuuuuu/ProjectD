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

SubActor::SubActor(std::list<std::shared_ptr<EnemyBase>>& enemy) :
	m_flame(0),
	m_enemy(enemy)
{
	// 外部ファイルから定数を取得する
	ReadCSV("data/constant/SubActor.csv");
}

SubActor::~SubActor()
{
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
		UI::getInstance().SetEnemyInteractPtr(enemy);

		//　敵のポインタをシーケンスに渡す
		m_enemyPtr = enemy;
	}

	// サインカーブを使用して常に上下にふわふわと動かす
	float move = 0.1f * sin(m_flame);
	m_flame += 0.01f;
	Position.y += move;
}

void SubActor::Draw() const
{
}

std::shared_ptr<EnemyBase> SubActor::GetEnemyPtr()
{
	return m_enemyPtr;
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
	if (input.GetStickVectorLength(INPUT_LEFT_STICK) > std::get<float>(input.GetConstant("STICK_INVALID_VALUE"))) {

		// スティックの単位ベクトルに移動量をかけた値を代入
		m_moveVec = input.GetStickUnitVector(INPUT_LEFT_STICK) * std::get<float>(Constants["HORIZONTAL_MOVE_SCALE"]);

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
	// Aで上昇
	if (input.IsHold(INPUT_A)) {
		// 移動ベクトルのY値を加算する
		m_moveVec.y += std::get<float>(Constants["VERTICAL_MOVE_SCALE"]);
	}
	// Bで下降
	if (input.IsHold(INPUT_B)) {
		// 移動ベクトルのY値を減算する
		m_moveVec.y += -std::get<float>(Constants["VERTICAL_MOVE_SCALE"]);
	}

	// 作成した移動ベクトルを単位化する
	m_moveVec.Normalize();

	// 現在の座標に移動ベクトルを足す
	Position += m_moveVec;

	// 移動した後移動可能範囲外に出ていたら位置を戻す
	float dist = (Position - m_mainActorPos).Length();
	if (dist >= std::get<float>(Constants["MOVABLE_RANGE"])) {
		Position -= m_moveVec;
	}
}

std::shared_ptr<EnemyBase> SubActor::FindEnemy()
{
	std::list<std::shared_ptr<EnemyBase>> enemyList;

	auto aaa = m_enemy.size();
	printfDx("%d\n", aaa);

	// 範囲内の敵を配列におさめる
	for (auto& enemy : m_enemy) {
		if ((enemy->Position - Position).Length() <= std::get<float>(Constants["EFFECTIVE_RANGE"])) {
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
		if (pos.x < 0 || pos.x > std::get<float>(Application::getInstance().GetConstant("SCREEN_WIDTH")) ||
			pos.y < 0 || pos.y > std::get<float>(Application::getInstance().GetConstant("SCREEN_HEIGHT"))) {
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
	auto &max = enemyList.front();
	for (auto& enemy : m_enemy) {
		if ((max->Position - Position).Length() > (enemy->Position - Position).Length()) {
			max = enemy;
		}
	}

	return max;
}
