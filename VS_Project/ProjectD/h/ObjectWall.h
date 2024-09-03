#pragma once
#include "StaticObjectBase.h"

class ObjectWall :
    public StaticObjectBase
{
public:
    ObjectWall(int modelHandle,Vec3 pos,bool angle);
    virtual ~ObjectWall();

    void Draw() const;
};

