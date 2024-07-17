#include "SceneTest.h"
#include "DxLib.h"
#include "StaticFunction.h"
#include "Player.h"
#include "Singleton.h"
#include "EnemyManager.h"
#include "EnemyTest.h"
#include "UI.h"
#include "Direction.h"
#include "EffekseerForDXLib.h"

SceneTest::SceneTest()
{
	// �f�B���N�V�����C���X�^���X�̍쐬
	m_pDirection = make_shared<Direction>();

	// �v���C���[�̃C���X�^���X�̍쐬
	m_pPlayer = make_shared<Player>(m_pDirection);

	// �G�l�~�[��ǉ�����
	EnemyManager::getInstance().AddEnemy<EnemyTest>(Vec3{ 60,0,60 });
	EnemyManager::getInstance().AddEnemy<EnemyTest>(Vec3{ 60,0,30 });
	m_updateFunc = &SceneTest::NormalUpdate;
	m_drawFunc = &SceneTest::NormalDraw;
}

SceneTest::~SceneTest()
{
}

void SceneTest::Update()
{
	(this->*m_updateFunc)();
}

void SceneTest::Draw() const
{
	// �O���b�h�̕\��
	DrawGrid();

	(this->*m_drawFunc)();
}

void SceneTest::DrawGrid() const
{
	for (int x = -100; x <= 100; x += 10)
	{
		DrawLine3D(VGet(static_cast<float>(x), 0, -100), VGet(static_cast<float>(x), 0, 100), 0xffff00);
	}
	for (int z = -100; z <= 100; z += 10)
	{
		DrawLine3D(VGet(-100, 0, static_cast<float>(z)), VGet(100, 0, static_cast<float>(z)), 0xff0000);
	}

	// X+-,Z+-�̕�����������₷���悤�ɕ\����ǉ�����
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

void SceneTest::NormalUpdate()
{
	// �G�l�~�[�̍X�V
	EnemyManager::getInstance().Update();

	// �v���C���[�̍X�V
	m_pPlayer->Update();

	// UI�̍X�V
	UI::getInstance().Update();

	// �V�[�P���X�ڍs����
	if (m_pDirection->IsPlaySequ()) {
		m_updateFunc = &SceneTest::SeqUpdate;
		m_drawFunc = &SceneTest::SeqDraw;
	}

}

void SceneTest::NormalDraw() const
{
	// �G�l�~�[�̕`��
	EnemyManager::getInstance().Draw();

	// �v���C���[�̕`��
	m_pPlayer->Draw();

	// UI�̕`��
	UI::getInstance().Draw();

	
}

void SceneTest::SeqUpdate()
{
	m_pPlayer->Update();
	m_pDirection->Update();
	UI::getInstance().Update();

	// �V�[�P���X�I������
	if (!m_pDirection->IsPlaySequ()) {
		m_updateFunc = &SceneTest::NormalUpdate;
		m_drawFunc = &SceneTest::NormalDraw;
	}
}

void SceneTest::SeqDraw() const
{
	// �G�l�~�[�̕`��
	EnemyManager::getInstance().Draw();

	// �v���C���[�̕`��
	m_pPlayer->Draw();

	// UI�̕`��
	UI::getInstance().Draw();

	// �f�B���N�V�����̕`�揈��
	m_pDirection->Draw();
}
