#include "EnemyTest.h"
#include "DxLib.h"
#include <cassert>

EnemyTest::EnemyTest(Vec3 pos, int modelhandle)
{
	// 外部ファイルから定数を取得する
	assert(ConstantsFileLoad("data/constant/Enemy.csv", Constants) == 1);

	// 初期位置の設定
	Position = pos;

	// 拡大の設定
	Scale = Vec3{ 0.2f,0.2f,0.2f };

	// ３Dモデル初期処理
	InitModel(modelhandle);
	// アニメーションの初期処理
	//InitAnimation(ModelHandle, Constants["ANIM_IDLE"], 0.15f);
	InitAnimation(ModelHandle, 1, 0.15f);
	/*index = MV1AttachAnim(ModelHandle, 2);
	m_maxFlame = MV1GetAttachAnimTotalTime(ModelHandle, index);*/

}

EnemyTest::~EnemyTest()
{
}

void EnemyTest::Update()
{
	//ChangeAnimation(ModelHandle, Constants["ANIM_IDLE"], true, 0.0f);
	UpdateAnimation(ModelHandle);
	/*m_flame += 0.5f;
	MV1SetAttachAnimTime(ModelHandle, index, m_flame);*/
	UpdateModel(GetTransformInstance());
}

void EnemyTest::Draw() const
{
	DrawModel();
}
