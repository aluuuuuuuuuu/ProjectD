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

	// �����ύX�����Ƃ��̏�������
	void ChangeInit();

	void Control();
private:
	
};