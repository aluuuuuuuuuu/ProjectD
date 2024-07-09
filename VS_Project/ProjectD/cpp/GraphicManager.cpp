#include "GraphicManager.h"
#include <fstream>
#include <sstream>
#include "DxLib.h"

int GraphicManager::LoadGraphics()
{
	// �t�@�C�����J��
	std::ifstream file("data/GraphicCSV/Graphics.csv");

	// �t�@�C�����J���Ȃ�������-1��Ԃ�
	if (!file.is_open()) {
		return -1;
	}

	// �Ō�̍s�܂ŌJ��Ԃ�
	std::string line;
	while (std::getline(file,line)){

		// �s���Ƃ�
		std::stringstream stream(line);

		// �v�f�̓��e���쐬����
		std::string name, path;

		// �J���}�ōs�𕪊����摜���ƃp�X���i�[����
		if (std::getline(stream, name, ',') && stream >> path) {
			m_graphics[name] = LoadGraph(path.c_str());
		}
	}

	// �I�������ꍇ1��Ԃ�
	return 1;
}

void GraphicManager::DeleteGraphics()
{
	for (auto& pair : m_graphics) {
		DeleteGraph(pair.second);
	}
}

int GraphicManager::GetGraph(std::string name)
{
	return m_graphics[name];
}
