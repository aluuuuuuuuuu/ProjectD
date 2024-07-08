#include "Constant.h"
#include <fstream>
#include <sstream>

int Constant::ConstantsFileLoad(const char* fileName, std::map<std::string, float>& constants)
{
	// �t�@�C�����J��
	std::ifstream file(fileName);

	// �t�@�C�����J���Ȃ�������-1��Ԃ�
	if (!file.is_open()) {
		return -1;
	}

	// �Ō�̍s�܂ŌJ��Ԃ�
	std::string line;
	while (getline(file, line)) {

		// �s���Ƃ�
		std::stringstream stream(line);

		// �v�f�̓��e���쐬����
		std::string name;
		float value;

		// �J���}�ōs�𕪊����萔���ƒl���i�[����
		if (getline(stream, name, ',') && stream >> value) {
			constants[name] = value;
		}
	}

	// �t�@�C�������
	file.close();

	// �I��������1��Ԃ�
	return 1;
}
