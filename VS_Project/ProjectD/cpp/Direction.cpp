#include "Direction.h"
#include "DxLib.h"
#include "DirectionCamera.h"
#include "Input.h"
#include <cassert>
#include "EnemyBase.h"

Direction::Direction() :
	m_playFlag(false),
	m_faintFlag(false),
	m_flame(0)
{
	// 外部ファイルから定数を取得する
	assert(ConstantsFileLoad("data/constant/Direction.csv", Constants) == 1);

	m_updateFunc = &Direction::NullUpdate;
	m_drawFunc = &Direction::NullDraw;

	// ディレクションカメラの作成
	m_pCamera = std::make_shared<DirectionCamera>();
}

Direction::~Direction()
{
}

void Direction::Init()
{
}

void Direction::Update()
{
	(this->*m_updateFunc)();
}

void Direction::Draw()
{
	(this->*m_drawFunc)();
}

void Direction::PlayFaintSequ(Vec3 cameraPos)
{
	// 関数ポインタの設定
	m_updateFunc = &Direction::FaintUpdate;
	m_drawFunc = &Direction::FaintDraw;

	// カメラの座標を受け取る
	m_pCamera->Position = cameraPos;

	// 演出を行っているフラグを立てる
	m_playFlag = true;

	// 左右の玉の座標の設定
	m_left.pos = Vec3{ Constants["FAINT_LEFT_POS_X"],0.0f,Constants["FAINT_LEFT_POS_Z"] };
	m_right.pos = Vec3{ Constants["FAINT_RIGHT_POS_X"],0.0f,Constants["FAINT_RIGHT_POS_Z"] };

	// ターゲットの座標の設定
	m_target = Vec3{ Constants["FAINT_TARGET_POS_X"],0.0f,Constants["FAINT_TARGET_POS_Y"] };
}

void Direction::SetEnemyPtr(std::shared_ptr<EnemyBase> enemy)
{
	m_enemyPtr = enemy;
}

void Direction::StopSequence()
{
	m_updateFunc = &Direction::NullUpdate;
	m_drawFunc = &Direction::NullDraw;
	m_playFlag = false;
}

bool Direction::IsPlaySequ()
{
	return m_playFlag;
}

bool Direction::IsFaintEnemy()
{
	return m_faintFlag;
}

void Direction::NullUpdate()
{
}

void Direction::NullDraw() const
{
}

void Direction::FaintUpdate()
{
	// 敵を気絶させていたら何もしない
	if (m_faintFlag) {

		// 一定フレームたったら通常の処理に移行する
		if (m_flame >= Constants["END_FLAME"]) {
			m_playFlag = false;
			m_flame = 0;
		}
		else {
			m_flame++;
		}
	}
	else {
		// インプットのインスタンスを取得
		auto& input = Input::getInstance();

		// カメラのターゲットを敵の位置に固定する
		m_pCamera->Update(m_enemyPtr->Position.VGet());

		float moveScaleLeft = 1.0f;
		float moveScaleRight = 1.0f;

		// たまに近づくに連れ移動速度が遅くなっていく

		// 目標との距離を保存する
		m_left.length = (m_left.pos - m_target).Length();
		m_right.length = (m_right.pos - m_target).Length();

		// 左
		if (m_left.length <= Constants["TARGET_RANGE"]) {
			moveScaleLeft = static_cast<float>(1.0 - (1 - m_left.length / Constants["TARGET_RANGE"]));
		}
		// 右
		if (m_right.length <= Constants["TARGET_RANGE"]) {
			moveScaleRight = static_cast<float>(1.0 - (1 - m_right.length / Constants["TARGET_RANGE"]));
		}

		// 円がターゲットに近づくにつれ振動が大きくなる
		int vibe = 0;
		// 左
		if (m_left.length <= Constants["TARGET_RANGE"]) {
			vibe += static_cast<int>(500 * (1 - m_left.length / Constants["TARGET_RANGE"]));
		}
		// 右
		if (m_right.length <= Constants["TARGET_RANGE"]) {
			vibe += static_cast<int>(500 * (1 - m_right.length / Constants["TARGET_RANGE"]));
		}

		//左右のスティック入力で玉を動かす
		// 左
		if (input.GetStickVectorLength(INPUT_LEFT_STICK) > input.Constants["STICK_INVALID_VALUE"]) {

			// 移動ベクトルを作成
			m_left.moveVec = input.GetStickUnitVector(INPUT_LEFT_STICK);
			m_left.moveVec.z *= -1;

			// 座標を移動
			m_left.pos += m_left.moveVec * moveScaleLeft * Constants["MOVE_SCALE"];

			// コントローラーを振動させる
			StartJoypadVibration(DX_INPUT_PAD1, vibe, 10);
		}

		// スティックを離したら元の場所に戻る
		else {

			// ある程度近づいていたら移動を止める
			if ((m_left.pos - Vec3{ Constants["FAINT_LEFT_POS_X"],0.0f,Constants["FAINT_LEFT_POS_Z"] }).Length() <= Constants["MOVE_STOP_RANGE"]) {
				m_left.pos = Vec3{ Constants["FAINT_LEFT_POS_X"],0.0f,Constants["FAINT_LEFT_POS_Z"] };
			}
			else {
				m_left.moveVec = (Vec3{ Constants["FAINT_LEFT_POS_X"],0.0f,Constants["FAINT_LEFT_POS_Z"] } - m_left.pos).GetNormalized();
				m_left.pos += m_left.moveVec * Constants["RETURN_MOVE_SCALE"];
			}
		}
		// 右
		if (input.GetStickVectorLength(INPUT_RIGHT_STICK) > input.Constants["STICK_INVALID_VALUE"]) {

			// 移動ベクトルを作成
			m_right.moveVec = input.GetStickUnitVector(INPUT_RIGHT_STICK);
			m_right.moveVec.z *= -1;

			// 座標を移動
			m_right.pos += m_right.moveVec * moveScaleRight * Constants["MOVE_SCALE"];

			// コントローラーを振動させる
			StartJoypadVibration(DX_INPUT_PAD1, vibe, 10);
		}

		// スティックを離したら元の場所に戻る
		else {

			// ある程度近づいていたら移動を止める
			if ((m_right.pos - Vec3{ Constants["FAINT_RIGHT_POS_X"],0.0f,Constants["FAINT_RIGHT_POS_Z"] }).Length() <= Constants["MOVE_STOP_RANGE"]) {
				m_right.pos = Vec3{ Constants["FAINT_RIGHT_POS_X"],0.0f,Constants["FAINT_RIGHT_POS_Z"] };
			}
			else {
				m_right.moveVec = (Vec3{ Constants["FAINT_RIGHT_POS_X"],0.0f,Constants["FAINT_RIGHT_POS_Z"] } - m_right.pos).GetNormalized();
				m_right.pos += m_right.moveVec * Constants["RETURN_MOVE_SCALE"];
			}
		}

		// 目標にある程度近づいたら
		if (m_left.length <= Constants["ENEMY_FAINT_LENGTH"] && m_right.length <= Constants["ENEMY_FAINT_LENGTH"]) {
			// 敵をキルする処理を開始させる
			m_enemyPtr->SetStartDeadFlag();

			// 気絶させたフラグを立てる
			m_faintFlag = true;
		}
	}
	

}

void Direction::FaintDraw() const
{
	// 敵を気絶させていたら表示しない
	if (m_faintFlag) {

	}
	else {
		// 目標の玉を描画
		DrawCircle(m_target.intX(), m_target.intZ(), 30, 0xffff00, true);

		// 右の玉を描画
		DrawCircle(m_right.pos.intX(), m_right.pos.intZ(), static_cast<int>(Constants.at("CIRCLE_RADIUS")), 0x00ff00, true);

		// 左の玉を描画
		DrawCircle(m_left.pos.intX(), m_left.pos.intZ(), static_cast<int>(Constants.at("CIRCLE_RADIUS")), 0x00ff00, true);
	}
}
