#pragma once

class StaticObject;
class StaticObjectManager
{
public:
	StaticObjectManager();
	virtual ~StaticObjectManager();

	void Update();
	void Draw() const;
};

