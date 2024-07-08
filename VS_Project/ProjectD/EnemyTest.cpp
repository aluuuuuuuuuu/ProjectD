#include "EnemyTest.h"
#include "DxLib.h"

EnemyTest::EnemyTest(Vec3 pos)
{
	Position = pos;
}

EnemyTest::~EnemyTest()
{
}

void EnemyTest::Update()
{
}

void EnemyTest::Draw() const
{
	DrawSphere3D(Position.VGet(), 8, 16, 0xff0000, 0xff0000, true);
}
