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
	// �O���t�@�C������萔���擾����
	assert(ConstantsFileLoad("data/constant/SubActor.csv", Constants) == 1);

	// �c�݃G�t�F�N�g�����[�h
	m_effectDistortionHandle = LoadEffekseerEffect("data/effect/test.efkefc", 120.0f);

	// �c�݃G�t�F�N�g�𔭐�������
	m_effectDistortionHandle = PlayEffekseer2DEffect(m_effectDistortionHandle);
}

SubActor::~SubActor()
{
	DeleteEffekseerEffect(m_effectDistortionHandle);
}

void SubActor::Update()
{
	// �߂��̃G�l�~�[��T����UI�Ƀf�[�^��n��
	auto enemy = FindEnemy();
	if (enemy == nullptr) {
		UI::getInstance().SetEnemyInteractFlag(false);
	}
	else {
		UI::getInstance().SetEnemyInteractFlag(true);
		UI::getInstance().SetEnemyInteractPos(enemy->Position);

		//�@�G�̍��W���V�[�P���X�ɓn��
		m_enemyPos = enemy->Position;
	}

	// �T�C���J�[�u���g�p���ď�ɏ㉺�ɂӂ�ӂ�Ɠ�����
	float move = 0.1f * sin(m_flame);
	m_flame += 0.01f;

	Position.y += move;

	SetPosPlayingEffekseer2DEffect(m_effectDistortionHandle, 960, 540, 0);
}

void SubActor::Draw() const
{
	// �c�݃G�t�F�N�g��`�悷��
	DrawEffekseer2D_Draw(m_effectDistortionHandle);
}

Vec3 SubActor::GetEnemyPos()
{
	return m_enemyPos;
}

void SubActor::ChangeInit(Vec3 cameraPos, Vec3 mainActorPos)
{
	// ���C���A�N�^�[���쎞�̃J�����̍��W�����̂܂܃I�Y�̏������W�ɂȂ�
	Position = cameraPos;

	// ���C���A�N�^�[�̍��W��ۑ�����
	m_mainActorPos = mainActorPos;
}

void SubActor::Control(Vec3 cameraRot)
{
	// �C���v�b�g�̃C���X�^���X���擾
	auto& input = Input::getInstance();

	// �ړ��x�N�g���̏�����
	m_moveVec = 0;

	// ���s�ړ�
	if (input.GetStickVectorLength(INPUT_LEFT_STICK) > input.Constants["STICK_INVALID_VALUE"]) {

		// �X�e�B�b�N�̒P�ʃx�N�g���Ɉړ��ʂ��������l����
		m_moveVec = input.GetStickUnitVector(INPUT_LEFT_STICK) * Constants["HORIZONTAL_MOVE_SCALE"];

		// �J�����̉�]�𓾂�
		Angle.y = cameraRot.y;

		// Y����]�s��ɕϊ�
		MATRIX rotaMtx = MGetRotY(Angle.y);

		// �X���̕������t�Ȃ̂Ŕ��]������
		Vec3 inclination = input.GetStickUnitVector(INPUT_LEFT_STICK) * -1;

		// �X�e�B�b�N�̌X�����J�����ɍ��킹��Y����]������
		m_moveVec = VTransform(inclination.VGet(), rotaMtx);
	}

	// �����ړ�
	// RB�ŏ㏸
	if (input.IsHold(INPUT_RIGHT_SHOULDER)) {
		// �ړ��x�N�g����Y�l�����Z����
		m_moveVec.y += Constants["VERTICAL_MOVE_SCALE"];
	}
	// RT�ŉ��~
	if (input.IsHold(INPUT_RIGHT_TRIGGER)) {
		// �ړ��x�N�g����Y�l�����Z����
		m_moveVec.y += -Constants["VERTICAL_MOVE_SCALE"];
	}

	// �쐬�����ړ��x�N�g����P�ʉ�����
	m_moveVec.Normalize();

	// ���݂̍��W�Ɉړ��x�N�g���𑫂�
	Position += m_moveVec;

	// �ړ�������ړ��\�͈͊O�ɏo�Ă�����ʒu��߂�
	float dist = (Position - m_mainActorPos).Length();
	if (dist >= Constants["MOVABLE_RANGE"]) {
		Position -= m_moveVec;
	}
}

std::shared_ptr<EnemyBase> SubActor::FindEnemy()
{
	std::list<std::shared_ptr<EnemyBase>> enemyList;

	// �͈͓��̓G��z��ɂ����߂�
	for (std::shared_ptr<EnemyBase> enemy : EnemyManager::getInstance().GetEnemy()) {
		if ((enemy->Position - Position).Length() <= Constants["EFFECTIVE_RANGE"]) {
			enemyList.push_back(enemy);
		}
	}

	// �͈͓��ɓG�����Ȃ����null��Ԃ�
	if (enemyList.size() == 0) {
		return nullptr;
	}

	// �͈͓��̓G�����ʊO�ɂ���G��r������
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

	// ��ʓ��ɓG�����Ȃ����null��Ԃ�
	if (enemyList.size() == 0) {
		return nullptr;
	}

	// �T�u�A�N�^�[�ɍł��߂��G�����o��
	auto max = enemyList.front();
	for (std::shared_ptr<EnemyBase> enemy : EnemyManager::getInstance().GetEnemy()) {
		if ((max->Position - Position).Length() > (enemy->Position - Position).Length()) {
			max = enemy;
		}
	}

	return max;
}
