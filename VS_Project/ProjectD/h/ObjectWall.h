#pragma once
#include "StaticObjectBase.h"

class ObjectWall :
    public StaticObjectBase
{
public:
    ObjectWall();
    virtual ~ObjectWall();

    void Update();
    void Draw() const;
};

