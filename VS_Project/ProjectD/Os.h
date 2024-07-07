#pragma once
#include "CharactorBase.h"

class Os :
	public CharactorBase
{
public:
	Os();
	~Os();

	void Update();
	void Draw() const;

	// ‘€ì‚ğ•ÏX‚µ‚½‚Æ‚«‚Ì‰Šúˆ—
	void ChangeInit();

	void Control();
private:
	
};