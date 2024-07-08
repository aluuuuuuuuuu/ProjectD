#include "UI.h"
#include "DxLib.h"
#include "GraphicManager.h"

void UI::Update()
{
}

void UI::Draw() const
{
	// インタラクトボタンを表示
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

		// ワールド座標を画面座標に変換する
		Vec3 pos = ConvWorldPosToScreenPos(m_enemyInteractPos.VGet());

		// エネミーの上にボタンを表示する
		DrawRotaGraph(pos.intX(), pos.intY(), 1.0, 0, GraphicManager::getInstance().GetGraph("ButtonX"), true, false);
	}
}
