#pragma once
#include <vector>
#include <memory>
#include "Singleton.h"

class StaticObject;

// �ÓI�ȃI�u�W�F�N�g���Ǘ�����}�l�[�W���[
class StaticObjectManager : public Singleton<StaticObjectManager>
{
	friend class Singleton<StaticObjectManager>;

public:

	void Init();
	void Update();
	void Draw() const;

private:

	// �v���C�x�[�g�R���X�g���N�^
	StaticObjectManager() {};

	// �S�ẴX�^�e�B�b�N�I�u�W�F�N�g���i�[����
	std::vector<std::shared_ptr<StaticObject>> m_pObject;
	int model = 0;
	int texture = 0;
};

