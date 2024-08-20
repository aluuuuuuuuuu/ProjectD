#pragma once
#include "StaticObjectBase.h"

class ObjectWall :
    public StaticObjectBase
{
public:
    ObjectWall(int modelHandle);
    virtual ~ObjectWall();

    void Draw() const;
};

