#pragma once
#include "EnemyBase.h"
#include "Components.h"
#include <memory>

class StaticObjectManager;
class Player;
class EnemyTest :
	public EnemyBase
{
public:
	EnemyTest(Vec3 pos, int modelhandle, std::shared_ptr<Player>& pl,std::shared_ptr<StaticObjectManager>& obj);
	virtual ~EnemyTest();

	void Update();
	void Draw() const;

private:

	// �v���C���[��F��������
	bool IsPlayerDetected();

	// �v���C���[�����̋������ɂ��邩
	bool IsPlayerInRange();

	// �v���C���[�����o���ɂ��邩
	bool IsPlayerInSight();

	// �v���C���[�Ƃ̊Ԃɏ�Q�������邩
	bool IsPlayerObstructed();

	// �v���C���[���G���قǂ̋����ɂ��邩
	bool IsPlayerWithinReach();

	// �v���C���[�̎Q��
	std::shared_ptr<Player>& m_pPlayer;

	// �X�^�e�B�b�N�I�u�W�F�N�g�}�l�[�W���[�̎Q��
	std::shared_ptr<StaticObjectManager>& m_pObject;


























	// �A�j���[�V����

	// �A�j���[�V������������
	void InitAnimation(int tag, float rate);

	// �A�j���[�V�����X�V����
	void UpdateAnimation();

	// �A�j���[�V�����ύX
	void ChangeAnimation(int tag, bool loop, float blendRate);

	// �A���ŃA�j����؂�ւ������ꍇ�̃A�j���[�V�����ύX
	void ChangeAnimationConnect(int tag1, int tag2, float rate1, float rate2);

	// �A�j���[�V�����I���t���O��Ԃ�
	bool GetEndAnimFlag();

	// ���s�̃A�j���[�V�����^�O��Ԃ�
	int GetAnimTag();






	// �A�j���[�V�����ϐ�
	// �f�t�H���g�̃u�����h���[�g
	float m_defaultRate = 0.0f;

	// �R�l�N�g��̃u�����h���[�g��ۑ�����
	float m_rate2 = 0.0f;

	// �u�����h���[�g
	float m_blendRateSave = 0.0f;

	// �Đ�����
	float m_flameCount = 0.0f;

	// ���t���[����
	float m_maxFlame = 0.0f;

	// �A�j���[�V�����C���f�b�N�X
	int m_attachIndex1 = 0;
	int m_attachIndex2 = 0;

	// �Đ����̃A�j���[�V����
	int m_playAnimation = 0;

	// �A���ōĐ�����A�j���[�V����
	std::vector<int> m_connectAnimation;

	// �A���ōĐ�����A�j���[�V�����̐i�s��
	int m_animationState = 0;

	// ���s�̃A�j���[�V�����^�O
	int m_runTag = 0;

	// ���[�v�Đ��t���O
	bool m_loopFlag = false;

	// �f�t�H���g�A�j���[�V�����^�O
	int m_defaultTag = 0;

	// �A�j���[�V�����R�l�N�g�t���O
	bool m_connectFlag = false;

	// �A�j���[�V�����u�����h���[�g
	float m_blendRate = 0.0f;

	// �A�j���[�V�����I���t���O
	bool m_endAnimFlag = true;


};

