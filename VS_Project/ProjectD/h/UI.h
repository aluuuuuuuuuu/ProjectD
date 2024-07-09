#pragma once
#include "Singleton.h"
#include "Vec3.h"

class UI :
    public Singleton<UI>
{
    friend class Singleton<UI>;

public:
    void Update();
    void Draw() const;

    void SetEnemyInteractPos(Vec3 pos);
    void SetEnemyInteractFlag(bool flag);

    bool GetEnemyInteractFlag();
private:
    // �v���C�x�[�g�R���X�g���N�^
    UI() {};

    // �C���^���N�g�{�^����\������
    void DrawInteract() const;

    // �G�l�~�[�C���^���N�g��\������t���O
    bool m_enemyInteractFlag = false;

    // �G�l�~�[�C���^���N�g��\��������W
    Vec3 m_enemyInteractPos;
};

