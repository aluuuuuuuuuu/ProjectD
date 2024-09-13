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
	// �O���t�@�C������萔���擾����
	ReadCSV("data/constant/Enemy.csv");

	// �����ʒu�̐ݒ�
	Position = pos;

	// �g��̐ݒ�
	Scale = Vec3{ 0.2f,0.2f,0.2f };

	// �RD���f����������
	InitModel(modelhandle);
	// �A�j���[�V�����̏�������
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


	// �v���C���[�����o�ɓ��邩�G��邭�炢�߂��ɂ���ꍇ�F������
	if (IsPlayerDetected() || IsPlayerWithinReach()) {

	}


	// ���W�A���p�𐳋K������
	Angle.y = fmodf(Angle.y, static_cast<float>(DX_TWO_PI));
	if (Angle.y < 0.0f) Angle.y += static_cast<float>(DX_TWO_PI);
}

void EnemyTest::Draw() const
{
	DrawModel();
}

bool EnemyTest::IsPlayerDetected()
{
	// �v���C���[�����̋������ɂ��邩
	if (IsPlayerInRange()) {

		// �v���C���[�����o���ɂ��邩
		if (IsPlayerInSight()) {

			// �v���C���[�Ƃ̊Ԃɏ�Q�������邩
			if (IsPlayerObstructed()) {

				// �F���ł���
				return true;
			}
		}
	}

	// �F���ł��Ȃ�
	return false;
}

bool EnemyTest::IsPlayerInRange()
{
	// �v���C���[�Ǝ��g�̋��������ȓ��ł��邩
	return((Position - m_pPlayer->GetPos()).Length() <= std::get<float>(Constants["PLAYER_RANGE"]));
}

bool EnemyTest::IsPlayerInSight()
{
	// ���ʂ����������K�x�N�g��
	Vec3 normalVector;
	normalVector.x = std::cos(Angle.y);
	normalVector.z = std::sin(Angle.y);

	//// ���g����v���C���[�ւ̐��K�x�N�g��
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

	// �A�j���[�V�����̑��t���[������ۑ�
	m_maxFlame = MV1GetAttachAnimTotalTime(ModelHandle, m_attachIndex1);

	// �Đ����̃A�j���[�V�����̃^�O��ۑ�����
	m_playAnimation = tag;
}

void EnemyTest::UpdateAnimation()
{
	// �O�̃t���[���ŃA�j���[�V�������I�����Ă�����f�t�H���g�ɖ߂�
	if (m_endAnimFlag) {
		ChangeAnimation(m_defaultTag, true, m_defaultRate);
	}

	// �Đ����Ԃ�i�߂�
	m_flameCount += 0.5f;

	// �u�����h���[�g�����Z���Ă���
	if (m_blendRate >= 1.0f) {
		MV1SetAttachAnimBlendRate(ModelHandle, m_attachIndex1, 1.0f);
	}
	else {
		m_blendRate += m_blendRateSave;

		MV1SetAttachAnimBlendRate(ModelHandle, m_attachIndex2, 1.0f - m_blendRate);

		MV1SetAttachAnimBlendRate(ModelHandle, m_attachIndex1, m_blendRate);
	}

	// �Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB�����Ƃ�
	if (m_flameCount >= m_maxFlame) {

		// �R�l�N�g�t���O��true�������玟�̃A�j���[�V�������X�^�[�g������
		if (m_connectFlag) {
			m_animationState++;
			ChangeAnimation(m_connectAnimation[m_animationState], true, m_rate2);
			m_connectAnimation.clear();
			m_animationState = 0;
		}
		// ���[�v�t���O��true�������烋�[�v������
		else if (m_loopFlag) {
			m_flameCount = 0.0f;
		}
		// ���S�ɏI��������t���O�𗧂Ă�
		else {
			m_endAnimFlag = true;
		}
	}
	//printfDx("%f", m_flameCount);

	// �A�j���[�V�����X�V
	MV1SetAttachAnimTime(ModelHandle, m_attachIndex1, m_flameCount);
}

// �A�j���[�V�����ύX
void EnemyTest::ChangeAnimation(int tag, bool loop, float blendRate)
{
	// �Đ�����A�j���[�V������ύX����
	if (tag != m_playAnimation) {
		// ���s�̃A�j���[�V�������f�^�b�`����
		MV1DetachAnim(ModelHandle, m_attachIndex2);

		// ���[�v�t���O��ۑ�
		m_loopFlag = loop;

		// �u�����h���[�g��ύX
		m_blendRateSave = blendRate;

		// �Đ����Ԃ��ŏ��ɖ߂�
		m_flameCount = 0.0f;

		// �s���Ă����A�j���[�V������ۑ�
		m_attachIndex2 = m_attachIndex1;

		// �A�j���[�V������ύX
		m_attachIndex1 = MV1AttachAnim(ModelHandle, tag);

		// �A�j���[�V�����̃t���[������ۑ�
		m_maxFlame = MV1GetAttachAnimTotalTime(ModelHandle, m_attachIndex1);

		// �Đ����̃A�j���[�V�����̃^�O��ۑ�����
		m_playAnimation = tag;

		// �A�j���[�V�����I���t���O��false��
		m_endAnimFlag = false;

		// �u�����h���[�g������������
		m_blendRate = 0.0f;

		// �R�l�N�g�t���O��������
		m_connectFlag = false;
	}
}

// �A�j���[�V������A�����������Ƃ��̕ύX�֐�
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
