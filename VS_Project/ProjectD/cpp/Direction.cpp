#include "Direction.h"
#include "DxLib.h"
#include "DirectionCamera.h"
#include "Input.h"
#include <cassert>

Direction::Direction() :
	m_playFlag(false)
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
	m_left.pos = Vec3{ Constants["FAINT_LEFT_POS_X"],Constants["FAINT_LEFT_POS_Y"],Constants["FAINT_LEFT_POS_Z"] };
	m_right.pos = Vec3{ Constants["FAINT_RIGHT_POS_X"],Constants["FAINT_RIGHT_POS_Y"],Constants["FAINT_RIGHT_POS_Z"] };

	m_right.moveScale = Constants["MOVE_SCALE"];
	m_left.moveScale = Constants["MOVE_SCALE"];

	m_target = Vec3{ Constants["FAINT_TARGET_POS_X"],0.0f,Constants["FAINT_TARGET_POS_Y"] };
}

void Direction::SetEnemyPos(Vec3 pos)
{
	m_enemyPos = pos;
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

void Direction::NullUpdate()
{
}

void Direction::NullDraw() const
{
}

void Direction::FaintUpdate()
{
	// インプットのインスタンスを取得
	auto& input = Input::getInstance();

	// カメラのターゲットを敵の位置に固定する
	m_pCamera->Update(m_enemyPos);

	// 左右のスティック入力で玉を動かす
	// 左
	if (input.GetStickVectorLength(INPUT_LEFT_STICK) > input.Constants["STICK_INVALID_VALUE"]) {
		m_left.moveVec = input.GetStickUnitVector(INPUT_LEFT_STICK) * m_left.moveScale;
		m_left.moveVec.z *= -1;
		m_left.pos += m_left.moveVec;

		// 玉と目標の距離が近くなるほど移動速度が下がっていく
		float len = (m_target - m_left.pos).Length();
		m_left.moveScale = ((len * len) / Constants["MOVE_SCALE"]) * 0.001f;
	}
	else {
		// 移動速度を初期化する
		m_left.moveScale = Constants["MOVE_SCALE"];

		// スティックを離したら元の位置に戻っていく
		// 元の位置に戻る単位ベクトルを作成する
		m_left.moveVec = Vec3{ Constants["FAINT_LEFT_POS_X"],Constants["FAINT_LEFT_POS_Y"] ,Constants["FAINT_LEFT_POS_Z"] } - m_left.pos;
		m_left.moveVec.Normalize();

		// 移動する
		m_left.pos += m_left.moveVec * m_left.moveScale;
	}
	// 右
	if (input.GetStickVectorLength(INPUT_RIGHT_STICK) > input.Constants["STICK_INVALID_VALUE"]) {
		m_right.moveVec = input.GetStickUnitVector(INPUT_RIGHT_STICK) * m_right.moveScale;
		m_right.moveVec.z *= -1;
		m_right.pos += m_right.moveVec;
	}
}

void Direction::FaintDraw() const
{
	DrawString(10, 10, "気絶させます", 0xff0000);

	// 目標の玉を描画
	DrawCircle(m_target.x, m_target.z, 30, 0xffff00, true);

	// 右の玉を描画
	DrawCircle(m_right.pos.x, m_right.pos.z, Constants.at("CIRCLE_RADIUS"), 0x00ff00, true);

	// 左の玉を描画
	DrawCircle(m_left.pos.x, m_left.pos.z, Constants.at("CIRCLE_RADIUS"), 0x00ff00, true);
}
