#pragma once
#include "Singleton.h"
#include <map>
#include <string>

class GraphicManager:
	public Singleton<GraphicManager>
{
	friend class Singleton<GraphicManager>;

public:

	// ���ׂẲ摜�����[�h����
	int LoadGraphics();

	// ���ׂẲ摜���f���[�g����
	void DeleteGraphics();

	// �摜��񋟂���
	int GetGraph(std::string name);

private:
	// �v���C�x�[�g�R���X�g���N�^
	GraphicManager() {};

	std::map<std::string, int> m_graphics;
};

