#include "UI.h"
#include "DxLib.h"
#include "GraphicManager.h"

void UI::Update()
{
}

void UI::Draw() const
{
	// �C���^���N�g�{�^����\��
	DrawInteract();
}

void UI::SetEnemyInteractPos(Vec3 pos)
{
	m_enemyInteractPos = pos;
}

void UI::SetEnemyInteractFlag(bool flug)
{
	m_enemyInteractFlag = flug;
}

bool UI::GetEnemyInteractFlag()
{
	return m_enemyInteractFlag;
}

void UI::DrawInteract() const
{
	if (m_enemyInteractFlag) {

		// ���[���h���W����ʍ��W�ɕϊ�����
		Vec3 pos = ConvWorldPosToScreenPos(m_enemyInteractPos.VGet());

		// �G�l�~�[�̏�Ƀ{�^����\������
		DrawRotaGraph(pos.intX(), pos.intY(), 1.0, 0, GraphicManager::getInstance().GetGraph("ButtonX"), true, false);
	}
}
