#pragma once
#include "SceneBase.h"
class SceneTest :
    public SceneBase
{
public:
    SceneTest();
    virtual ~SceneTest();

    void Update();
    void Draw() const;
};

