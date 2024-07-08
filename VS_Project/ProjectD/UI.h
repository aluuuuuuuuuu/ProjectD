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
    void SetEnemyInteractFlug(bool flug);
private:
    // �v���C�x�[�g�R���X�g���N�^
    UI() {};

    // �C���^���N�g�{�^����\������
    void DrawInteract() const;

    // �G�l�~�[�C���^���N�g��\������t���O
    bool m_enemyInteractFlug = false;

    // �G�l�~�[�C���^���N�g��\��������W
    Vec3 m_enemyInteractPos;
};

