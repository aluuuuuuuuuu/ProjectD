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
	// �O���t�@�C������萔���擾����
	ReadCSV("data/constant/SubActor.csv");
}

SubActor::~SubActor()
{
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
		UI::getInstance().SetEnemyInteractPtr(enemy);

		//�@�G�̃|�C���^���V�[�P���X�ɓn��
		m_enemyPtr = enemy;
	}

	// �T�C���J�[�u���g�p���ď�ɏ㉺�ɂӂ�ӂ�Ɠ�����
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
	if (input.GetStickVectorLength(INPUT_LEFT_STICK) > std::get<float>(input.GetConstant("STICK_INVALID_VALUE"))) {

		// �X�e�B�b�N�̒P�ʃx�N�g���Ɉړ��ʂ��������l����
		m_moveVec = input.GetStickUnitVector(INPUT_LEFT_STICK) * std::get<float>(Constants["HORIZONTAL_MOVE_SCALE"]);

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
	// A�ŏ㏸
	if (input.IsHold(INPUT_A)) {
		// �ړ��x�N�g����Y�l�����Z����
		m_moveVec.y += std::get<float>(Constants["VERTICAL_MOVE_SCALE"]);
	}
	// B�ŉ��~
	if (input.IsHold(INPUT_B)) {
		// �ړ��x�N�g����Y�l�����Z����
		m_moveVec.y += -std::get<float>(Constants["VERTICAL_MOVE_SCALE"]);
	}

	// �쐬�����ړ��x�N�g����P�ʉ�����
	m_moveVec.Normalize();

	// ���݂̍��W�Ɉړ��x�N�g���𑫂�
	Position += m_moveVec;

	// �ړ�������ړ��\�͈͊O�ɏo�Ă�����ʒu��߂�
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

	// �͈͓��̓G��z��ɂ����߂�
	for (auto& enemy : m_enemy) {
		if ((enemy->Position - Position).Length() <= std::get<float>(Constants["EFFECTIVE_RANGE"])) {
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
		if (pos.x < 0 || pos.x > std::get<float>(Application::getInstance().GetConstant("SCREEN_WIDTH")) ||
			pos.y < 0 || pos.y > std::get<float>(Application::getInstance().GetConstant("SCREEN_HEIGHT"))) {
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
	auto &max = enemyList.front();
	for (auto& enemy : m_enemy) {
		if ((max->Position - Position).Length() > (enemy->Position - Position).Length()) {
			max = enemy;
		}
	}

	return max;
}
