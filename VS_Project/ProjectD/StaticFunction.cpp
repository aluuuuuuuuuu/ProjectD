#include "StaticFunction.h"
#include <fstream>
#include <sstream>

// �萔��CSV�t�@�C����map�ɓ��͂���֐�
int Function::ConstantsFileLoad(const char* fileName, map<string, float>& constants)
{
	// �t�@�C�����J��
	ifstream file(fileName);

	// �t�@�C�����J���Ȃ�������-1��Ԃ�
	if (!file.is_open()) {
		return -1;
	}

	// �Ō�̍s�܂ŌJ��Ԃ�
	string line;
	while (getline(file, line)) {

		// �s���Ƃ�
		stringstream stream(line);

		// �v�f�̓��e���쐬����
		string name;
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
