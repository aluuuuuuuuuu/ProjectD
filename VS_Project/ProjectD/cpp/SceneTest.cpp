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
#include "StaticObjectManager.h"
#include "MapCollisionManager.h"

SceneTest::SceneTest()
{
	// �G�l�~�[�}�l�[�W���[�̍쐬
	m_pEnemyManager = make_shared<EnemyManager>();

	// �f�B���N�V�����C���X�^���X�̍쐬
	m_pDirection = make_shared<Direction>();

	// �v���C���[�̃C���X�^���X�̍쐬
	m_pPlayer = make_shared<Player>(m_pDirection,m_pEnemyManager->GetEnemy());

	// �X�^�e�B�b�N�I�u�W�F�N�g�}�l�[�W���[�̃C���X�^���X�̍쐬
	m_pStaticObject = make_shared<StaticObjectManager>();

	// �X�^�e�B�b�N�I�u�W�F�N�g�}�l�[�W���[�̏�������
	m_pStaticObject->InitTest();

	// �R���W�����}�l�[�W���[�̍쐬
	m_pCollisionManager = make_shared<MapCollisionManager>(m_pPlayer->GetCupsule(),*m_pStaticObject);

	// �G�l�~�[��ǉ�����
	m_pEnemyManager->AddEnemy(Vec3{ 60,0,60 }, m_pPlayer, m_pStaticObject);

	m_pEnemyManager->AddEnemy(Vec3{ 60,0,30 }, m_pPlayer, m_pStaticObject);
	m_updateFunc = &SceneTest::NormalUpdate;
	m_drawFunc = &SceneTest::NormalDraw;
}

SceneTest::~SceneTest()
{
}

void SceneTest::Update()
{
	(this->*m_updateFunc)();

	// �G�t�F�N�g�̍X�V����
	UpdateEffekseer2D();
}

void SceneTest::Draw() const
{
	// �O���b�h�̕\��
	//DrawGrid();

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
	m_pEnemyManager->Update();

	// �v���C���[�̍X�V
	m_pPlayer->Update();

	m_pPlayer->CollisionMove(m_pCollisionManager->PlayerCollision());
	m_pCollisionManager->DrawColl();

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
	// �X�^�e�B�b�N�I�u�W�F�N�g�̕`��
	m_pStaticObject->Draw(m_pPlayer->GetPos());

	// �G�l�~�[�̕`��
	m_pEnemyManager->Draw();

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

		// �C��t���O�������Ă�����v���C���[�����C���A�N�^�[�ɕύX����
		if (m_pDirection->IsFaintEnemy()) {
			m_pPlayer->ChangeMode();
		}

		// �ʏ�̏����Ɉڍs����
		m_updateFunc = &SceneTest::NormalUpdate;
		m_drawFunc = &SceneTest::NormalDraw;
	}
}

void SceneTest::SeqDraw() const
{
	// �X�^�e�B�b�N�I�u�W�F�N�g�̕`��
	m_pStaticObject->Draw(m_pPlayer->GetPos());

	// �G�l�~�[�̕`��
	m_pEnemyManager->Draw();

	// �v���C���[�̕`��
	m_pPlayer->Draw();

	// UI�̕`��
	UI::getInstance().Draw();

	// �f�B���N�V�����̕`�揈��
	m_pDirection->Draw();
}
