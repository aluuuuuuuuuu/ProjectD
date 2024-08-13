#include "EnemyTest.h"
#include "DxLib.h"
#include <cassert>

EnemyTest::EnemyTest(Vec3 pos, int modelhandle)
{
	// �O���t�@�C������萔���擾����
	assert(ConstantsFileLoad("data/constant/Enemy.csv", Constants) == 1);

	// �����ʒu�̐ݒ�
	Position = pos;

	// �g��̐ݒ�
	Scale = Vec3{ 0.2f,0.2f,0.2f };

	// �RD���f����������
	InitModel(modelhandle);
	// �A�j���[�V�����̏�������
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
