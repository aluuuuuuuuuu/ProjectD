#include "Os.h"
#include "Camera.h"

Os::Os()
{
}

Os::~Os()
{
}

void Os::Update()
{
}

void Os::Draw() const
{
}

void Os::ChangeInit()
{
	// �u���[�^�X���쎞�̃J�����̍��W�����̂܂܃I�Y�̏������W�ɂȂ�
	Position = Camera::getInstance().Position;
}

void Os::Control()
{
}
