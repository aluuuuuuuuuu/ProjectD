#pragma once
#include "SceneBase.h"
#include <memory>

class Player;
// テストシーン
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

    // プレイヤーのポインタ
    std::shared_ptr<Player> m_pPlayer;
};

