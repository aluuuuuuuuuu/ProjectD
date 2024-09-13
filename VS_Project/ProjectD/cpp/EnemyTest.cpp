#include "EnemyTest.h"
#include "DxLib.h"
#include <cassert>
#include "StaticObjectManager.h"
#include "Player.h"

EnemyTest::EnemyTest(Vec3 pos, int modelhandle, std::shared_ptr<Player>& pl, std::shared_ptr<StaticObjectManager>& obj) :
	m_pPlayer(pl),
	m_pObject(obj)
{
	int a = 0;
	// 外部ファイルから定数を取得する
	ReadCSV("data/constant/Enemy.csv");

	// 初期位置の設定
	Position = pos;

	// 拡大の設定
	Scale = Vec3{ 0.2f,0.2f,0.2f };

	// ３Dモデル初期処理
	InitModel(modelhandle);
	// アニメーションの初期処理
	InitAnimation(0, 0.15f);
	//InitAnimation(ModelHandle, 0, 0.15f);
	/*index = MV1AttachAnim(ModelHandle, Constants["ANIM_IDLE"]);
	m_maxFlameA = MV1GetAttachAnimTotalTime(ModelHandle, index);*/
	//ChangeAnimation(2, true, 0.0f);
}

EnemyTest::~EnemyTest()
{
}

void EnemyTest::Update()
{
	//Angle.y += 0.1;
	UpdateAnimation();
	UpdateModel(GetTransformInstance());


	// プレイヤーが視覚に入るか触れるくらい近くにいる場合認識する
	if (IsPlayerDetected() || IsPlayerWithinReach()) {

	}


	// ラジアン角を正規化する
	Angle.y = fmodf(Angle.y, static_cast<float>(DX_TWO_PI));
	if (Angle.y < 0.0f) Angle.y += static_cast<float>(DX_TWO_PI);
}

void EnemyTest::Draw() const
{
	DrawModel();
}

bool EnemyTest::IsPlayerDetected()
{
	// プレイヤーが一定の距離内にいるか
	if (IsPlayerInRange()) {

		// プレイヤーが視覚内にいるか
		if (IsPlayerInSight()) {

			// プレイヤーとの間に障害物があるか
			if (IsPlayerObstructed()) {

				// 認識できる
				return true;
			}
		}
	}

	// 認識できない
	return false;
}

bool EnemyTest::IsPlayerInRange()
{
	// プレイヤーと自身の距離が一定以内であるか
	return((Position - m_pPlayer->GetPos()).Length() <= std::get<float>(Constants["PLAYER_RANGE"]));
}

bool EnemyTest::IsPlayerInSight()
{
	// 正面を向いた正規ベクトル
	Vec3 normalVector;
	normalVector.x = std::cos(Angle.y);
	normalVector.z = std::sin(Angle.y);

	//// 自身からプレイヤーへの正規ベクトル
	//Vec3 playerVector = (Position - m_pPlayer->GetPos()).GetNormalized();
	//if(std::cos(Constants["SIGHT_RANGE"]) )
	return false;

}

bool EnemyTest::IsPlayerObstructed()
{
	return false;
}

bool EnemyTest::IsPlayerWithinReach()
{
	int a = 0;
	return ((Position - m_pPlayer->GetPos()).Length() <= std::get<float>(Constants["PLAYER_WITHIN_RANGE"]));
}

void EnemyTest::InitAnimation(int tag, float rate)
{
	m_defaultRate = rate;

	m_defaultTag = tag;

	m_loopFlag = true;

	m_endAnimFlag = false;

	m_attachIndex1 = MV1AttachAnim(ModelHandle, tag);

	m_attachIndex2 = MV1AttachAnim(ModelHandle, tag);

	// アニメーションの総フレーム数を保存
	m_maxFlame = MV1GetAttachAnimTotalTime(ModelHandle, m_attachIndex1);

	// 再生中のアニメーションのタグを保存する
	m_playAnimation = tag;
}

void EnemyTest::UpdateAnimation()
{
	// 前のフレームでアニメーションが終了していたらデフォルトに戻す
	if (m_endAnimFlag) {
		ChangeAnimation(m_defaultTag, true, m_defaultRate);
	}

	// 再生時間を進める
	m_flameCount += 0.5f;

	// ブレンドレートを加算していく
	if (m_blendRate >= 1.0f) {
		MV1SetAttachAnimBlendRate(ModelHandle, m_attachIndex1, 1.0f);
	}
	else {
		m_blendRate += m_blendRateSave;

		MV1SetAttachAnimBlendRate(ModelHandle, m_attachIndex2, 1.0f - m_blendRate);

		MV1SetAttachAnimBlendRate(ModelHandle, m_attachIndex1, m_blendRate);
	}

	// 再生時間がアニメーションの総再生時間に達したとき
	if (m_flameCount >= m_maxFlame) {

		// コネクトフラグがtrueだったら次のアニメーションをスタートさせる
		if (m_connectFlag) {
			m_animationState++;
			ChangeAnimation(m_connectAnimation[m_animationState], true, m_rate2);
			m_connectAnimation.clear();
			m_animationState = 0;
		}
		// ループフラグがtrueだったらループさせる
		else if (m_loopFlag) {
			m_flameCount = 0.0f;
		}
		// 完全に終了したらフラグを立てる
		else {
			m_endAnimFlag = true;
		}
	}
	//printfDx("%f", m_flameCount);

	// アニメーション更新
	MV1SetAttachAnimTime(ModelHandle, m_attachIndex1, m_flameCount);
}

// アニメーション変更
void EnemyTest::ChangeAnimation(int tag, bool loop, float blendRate)
{
	// 再生するアニメーションを変更する
	if (tag != m_playAnimation) {
		// 現行のアニメーションをデタッチする
		MV1DetachAnim(ModelHandle, m_attachIndex2);

		// ループフラグを保存
		m_loopFlag = loop;

		// ブレンドレートを変更
		m_blendRateSave = blendRate;

		// 再生時間を最初に戻す
		m_flameCount = 0.0f;

		// 行っていたアニメーションを保存
		m_attachIndex2 = m_attachIndex1;

		// アニメーションを変更
		m_attachIndex1 = MV1AttachAnim(ModelHandle, tag);

		// アニメーションのフレーム数を保存
		m_maxFlame = MV1GetAttachAnimTotalTime(ModelHandle, m_attachIndex1);

		// 再生中のアニメーションのタグを保存する
		m_playAnimation = tag;

		// アニメーション終了フラグをfalseに
		m_endAnimFlag = false;

		// ブレンドレートを初期化する
		m_blendRate = 0.0f;

		// コネクトフラグを下げる
		m_connectFlag = false;
	}
}

// アニメーションを連続させたいときの変更関数
void EnemyTest::ChangeAnimationConnect(int tag1, int tag2, float rate1, float rate2)
{
	m_endAnimFlag = false;
	m_connectAnimation.push_back(tag1);
	m_connectAnimation.push_back(tag2);
	ChangeAnimation(m_connectAnimation[m_animationState], false, rate1);
	m_connectFlag = true;
}

bool EnemyTest::GetEndAnimFlag()
{
	return m_endAnimFlag;
}

int EnemyTest::GetAnimTag()
{
	return m_playAnimation;
}
