#pragma once
#include "EnemyBase.h"
#include "Components.h"

class EnemyTest :
    public EnemyBase
{
public:
    EnemyTest(Vec3 pos,int modelhandle);
    virtual ~EnemyTest();

    void Update();
    void Draw() const;

private:

    // �e�X�g�p�ϐ�
    int index;
    float m_maxFlameA;
    float m_flameA = 0.0f;


};

