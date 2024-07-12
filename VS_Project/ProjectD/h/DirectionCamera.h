#pragma once
#include "CameraBase.h"

class DirectionCamera:
	public CameraBase
{
public:
	DirectionCamera();
	virtual ~DirectionCamera();

	void Init();
	virtual void Update(Vec3 pos);
private:
};

