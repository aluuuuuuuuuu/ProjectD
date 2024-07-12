#include "Direction.h"
#include "DxLib.h"
#include "DirectionCamera.h"
#include "Input.h"
#include <cassert>

Direction::Direction() :
	m_playFlag(false)
{
	// �O���t�@�C������萔���擾����
	assert(ConstantsFileLoad("data/constant/Tama.csv", Constants) == 1);

	m_updateFunc = &Direction::NullUpdate;
	m_drawFunc = &Direction::NullDraw;

	// �f�B���N�V�����J�����̍쐬
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
	// �֐��|�C���^�̐ݒ�
	m_updateFunc = &Direction::FaintUpdate;
	m_drawFunc = &Direction::FaintDraw;

	// �J�����̍��W���󂯎��
	m_pCamera->Position = cameraPos;

	// ���o���s���Ă���t���O�𗧂Ă�
	m_playFlag = true;

	// ���E�̋ʂ̍��W�̐ݒ�
	m_left.pos = Vec3{ Constants["FAINT_LEFT_POS_X"],Constants["FAINT_LEFT_POS_Y"],Constants["FAINT_LEFT_POS_Z"] };
	m_right.pos = Vec3{ Constants["FAINT_RIGHT_POS_X"],Constants["FAINT_RIGHT_POS_Y"],Constants["FAINT_RIGHT_POS_Z"] };

	m_right.moveScale = Constants["MOVE_SCALE"];
	m_left.moveScale = Constants["MOVE_SCALE"];
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
	// �C���v�b�g�̃C���X�^���X���擾
	auto& input = Input::getInstance();

	// �J�����̃^�[�Q�b�g��G�̈ʒu�ɌŒ肷��
	m_pCamera->Update(m_enemyPos);

	// ���E�̃X�e�B�b�N���͂ŋʂ𓮂���
	// ��
	if (input.GetStickVectorLength(INPUT_LEFT_STICK) > input.Constants["STICK_INVALID_VALUE"]) {
		m_left.moveVec = input.GetStickUnitVector(INPUT_LEFT_STICK) * m_left.moveScale;
		m_left.moveVec.z *= -1;
		m_left.pos += m_left.moveVec;
	}
	// �E
	if (input.GetStickVectorLength(INPUT_RIGHT_STICK) > input.Constants["STICK_INVALID_VALUE"]) {
		m_right.moveVec = input.GetStickUnitVector(INPUT_RIGHT_STICK) * m_right.moveScale;
		m_right.moveVec.z *= -1;
		m_right.pos += m_right.moveVec;
	}
}

void Direction::FaintDraw() const
{
	DrawString(10, 10, "�C�₳���܂�", 0xff0000);

	// �ڕW�̋ʂ�`��
	DrawCircle(960, 700, 30, 0xffff00, true);

	// �E�̋ʂ�`��
	DrawCircle(m_right.pos.x, m_right.pos.z, Constants.at("CIRCLE_RADIUS"), 0x00ff00, true);

	// ���̋ʂ�`��
	DrawCircle(m_left.pos.x, m_left.pos.z, Constants.at("CIRCLE_RADIUS"), 0x00ff00, true);
}
