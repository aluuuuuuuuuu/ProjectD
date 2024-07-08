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
    // プライベートコンストラクタ
    UI() {};

    // インタラクトボタンを表示する
    void DrawInteract() const;

    // エネミーインタラクトを表示するフラグ
    bool m_enemyInteractFlug = false;

    // エネミーインタラクトを表示する座標
    Vec3 m_enemyInteractPos;
};

