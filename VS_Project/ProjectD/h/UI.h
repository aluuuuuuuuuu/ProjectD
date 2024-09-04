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
    // プライベートコンストラクタ
    UI() {};

    // インタラクトボタンを表示する
    void DrawInteract() const;

    // エネミーインタラクトを表示するフラグ
    bool m_enemyInteractFlag = false;

    // エネミーインタラクトの対象エネミーポインタ
    std::shared_ptr<EnemyBase> m_enemyInteractPtr;
};

