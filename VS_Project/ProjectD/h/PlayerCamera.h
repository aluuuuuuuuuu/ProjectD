#pragma once
#include "CameraBase.h"

#define SUBACTOR_MODE 0
#define MAINACTOR_MODE 1

class PlayerCamera :
	public CameraBase
{
public:
	PlayerCamera();
	virtual ~PlayerCamera();

	void Init(Vec3 pos);
	void Update(Vec3 pos);

	// サブアクターモードとメインアクターモードを変更する
	void ChangeMode(int mode);
private:	

	// 関数ポインタ
	using m_modeFunc_t = void (PlayerCamera::*)(Vec3 pos);
	m_modeFunc_t m_modeFunc = nullptr;

	// メインアクターモード
	void MainActorMode(Vec3 pos);

	// サブアクターモード
	void SubActorMode(Vec3 pos);

	// 回転
	Vec3 RotateMainActorMode(Vec3 pos);	// メインアクターモードでの回転処理
	Vec3 RotateSubActorMode(Vec3 pos);	// サブアクターモードでの回転処理

	// 引数の座標を回転させる
	VECTOR MakeBasePos(VECTOR base);

	// カメラの方向から発せられるライトのハンドル
	int m_lightHandle;
};

