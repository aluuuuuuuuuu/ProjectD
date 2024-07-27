#pragma once
#include "CharactorBase.h"
#include <memory>

class EnemyBase;
class SubActor :
	public CharactorBase
{
public:
	SubActor();
	~SubActor();

	void Update();
	void Draw() const;

	// �C���^���N�g����G�̍��W��Ԃ�
	Vec3 GetEnemyPos();

	// �����ύX�����Ƃ��̏�������
	void ChangeInit(Vec3 cameraPos, Vec3 mainActorPos);

	void Control(Vec3 cameraRot);
private:
	// �C���^���N�g����G��T���֐�
	std::shared_ptr<EnemyBase> FindEnemy();

	// ���C���A�N�^�[�̍��W
	Vec3 m_mainActorPos;
	
	// �C���^���N�g�ł���G�̍��W
	Vec3 m_enemyPos;

	// �T�C���J�[�u�p�̃t���[��
	float m_flame;

	// �V�F�[�_�[�n���h��
	int m_shaderHandle;

	// �V�F�[�_�[�p�̒萔�o�b�t�@
	int m_constBufferHandle;

	// �V�F�[�_�[�p�̃e�N�X�`��
	int m_textureHandlel;
};