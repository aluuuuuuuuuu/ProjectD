#pragma once
#include <vector>
#include <memory>
#include "Vec3.h"

class StaticObjectBase;
class StaticObject;
class StaticObjectManager
{
public:
	StaticObjectManager();
	virtual ~StaticObjectManager();

	// �e�X�g�X�e�[�W�ł̏�������
	void InitTest();

	// �X�e�[�W�P�ł̏�������
	void InitStage1();

	void Draw(Vec3 plPos) const;

	std::vector<std::shared_ptr<StaticObjectBase>> m_pStaticObject;	// �v���P

private:

	// �ǃI�u�W�F�N�g�̃��f���n���h��
	int m_wallHandle;

	// ���I�u�W�F�N�g�̃��f���n���h��
	int m_floorHandle;
};

