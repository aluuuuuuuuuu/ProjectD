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

	// 操作を変更したときの初期処理
	void ChangeInit();

	void Control();
private:
	
};