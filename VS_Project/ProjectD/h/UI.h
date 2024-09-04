#pragma once
#include "Singleton.h"
#include "Vec3.h"
#include <memory>

class EnemyBase;
class UI :
    public Singleton<UI>
{
    friend class Singleton<UI>;

public:
    void Update();
    void Draw() const;

    void SetEnemyInteractPtr(std::shared_ptr<EnemyBase> enemy);
    void SetEnemyInteractFlag(bool flag);

    bool GetEnemyInteractFlag();
private:
    // �v���C�x�[�g�R���X�g���N�^
    UI() {};

    // �C���^���N�g�{�^����\������
    void DrawInteract() const;

    // �G�l�~�[�C���^���N�g��\������t���O
    bool m_enemyInteractFlag = false;

    // �G�l�~�[�C���^���N�g�̑ΏۃG�l�~�[�|�C���^
    std::shared_ptr<EnemyBase> m_enemyInteractPtr;
};

