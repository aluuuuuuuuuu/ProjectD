#include "SceneTest.h"
#include "DxLib.h"
#include "StaticFunction.h"
#include "Player.h"
#include "Camera.h"
#include "Singleton.h"

SceneTest::SceneTest()
{
	m_pPlayer = make_shared<Player>();
	Camera::getInstance().Init(m_pPlayer->GetPos());
}

SceneTest::~SceneTest()
{
}

void SceneTest::Update()
{
	m_pPlayer->Update();

	Camera::getInstance().Update(m_pPlayer->GetPos());
}

void SceneTest::Draw() const
{
	DrawGrid();
	m_pPlayer->Draw();
}

void SceneTest::DrawGrid() const
{
	for (int x = -50; x <= 50; x += 10)
	{
		DrawLine3D(VGet(static_cast<float>(x), 0, -50), VGet(static_cast<float>(x), 0, 50), 0xffff00);
	}
	for (int z = -50; z <= 50; z += 10)
	{
		DrawLine3D(VGet(-50, 0, static_cast<float>(z)), VGet(50, 0, static_cast<float>(z)), 0xff0000);
	}

	// X+-,Z+-‚Ì•ûŒü‚ª•ª‚©‚è‚â‚·‚¢‚æ‚¤‚É•\Ž¦‚ð’Ç‰Á‚·‚é
	VECTOR dispPos = ConvWorldPosToScreenPos(VGet(50, 0, 0));
	if (dispPos.z >= 0.0f && dispPos.z <= 1.0f)
	{
		DrawStringF(dispPos.x, dispPos.y, "X+", 0xffffff);
	}

	dispPos = ConvWorldPosToScreenPos(VGet(-50, 0, 0));
	if (dispPos.z >= 0.0f && dispPos.z <= 1.0f)
	{
		DrawStringF(dispPos.x, dispPos.y, "X-", 0xffffff);
	}

	dispPos = ConvWorldPosToScreenPos(VGet(0, 0, 50));
	if (dispPos.z >= 0.0f && dispPos.z <= 1.0f)
	{
		DrawStringF(dispPos.x, dispPos.y, "Z+", 0xffffff);
	}

	dispPos = ConvWorldPosToScreenPos(VGet(0, 0, -50));
	if (dispPos.z >= 0.0f && dispPos.z <= 1.0f)
	{
		DrawStringF(dispPos.x, dispPos.y, "Z-", 0xffffff);
	}
}
