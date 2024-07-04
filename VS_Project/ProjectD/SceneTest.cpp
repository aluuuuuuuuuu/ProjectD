#include "SceneTest.h"
#include "DxLib.h"
#include "StaticFunction.h"
#include "Player.h"

SceneTest::SceneTest()
{
}

SceneTest::~SceneTest()
{
}

void SceneTest::Update()
{
	m_pPlayer->Update();
}

void SceneTest::Draw() const
{
	m_pPlayer->Draw();
}
