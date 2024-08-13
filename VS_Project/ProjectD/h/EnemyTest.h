#pragma once
#include "EnemyBase.h"
#include "CharactorBase.h"

class EnemyTest :
    public EnemyBase
{
public:
    EnemyTest(Vec3 pos,int modelhandle);
    virtual ~EnemyTest();

    void Update();
    void Draw() const;
private:

    int index;
    float m_maxFlame;
    float m_flame = 0.0f;
};

