#include "UI.h"
#include "DxLib.h"

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

void UI::SetEnemyInteractFlug(bool flug)
{
	m_enemyInteractFlug = flug;
}

void UI::DrawInteract() const
{
	if (m_enemyInteractFlug) {
		// �G�l�~�[�̏�Ƀ{�^����\������
		DrawString(ConvWorldPosToScreenPos(m_enemyInteractPos.VGet()).x, ConvWorldPosToScreenPos(m_enemyInteractPos.VGet()).y,"X",0xffffff);
	}
}
