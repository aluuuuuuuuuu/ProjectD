#pragma once
#include "SceneBase.h"
#include <memory>

class Player;
// �e�X�g�V�[��
class SceneTest :
    public SceneBase
{
public:
    SceneTest();
    virtual ~SceneTest();

    void Update();
    void Draw() const;

    void DrawGrid() const;
private:

    // �v���C���[�̃|�C���^
    std::shared_ptr<Player> m_pPlayer;
};

