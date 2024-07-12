#pragma once
#include "SceneBase.h"
#include <memory>

class Direction;
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

    // �֐��|�C���^
    using m_updateFunc_t = void (SceneTest::*)();
    using m_drawFunc_t = void (SceneTest::*)() const;
    m_updateFunc_t m_updateFunc = nullptr;
    m_drawFunc_t m_drawFunc = nullptr;

    // �ʏ�̏���
    void NormalUpdate();
    void NormalDraw() const;

    // �V�[�P���X���̏���
    void SeqUpdate();
    void SeqDraw() const;

    // �v���C���[�̃|�C���^
    std::shared_ptr<Player> m_pPlayer;

    // �f�B���N�V�����̂ۃC���^
    std::shared_ptr<Direction> m_pDirection;
};

