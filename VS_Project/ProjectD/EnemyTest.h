#pragma once
#include "EnemyBase.h"
#include "CharactorBase.h"

class EnemyTest :
    public EnemyBase
{
public:
    EnemyTest(Vec3 pos);
    ~EnemyTest();

    void Update();
    void Draw() const;
private:

};

