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
	void ChangeMode(int mode, Vec3 pos);

	// モード切替中であるか
	bool IsModeChange();
private:	

	// 関数ポインタ
	using m_modeFunc_t = void (PlayerCamera::*)(Vec3 pos);
	m_modeFunc_t m_modeFunc = nullptr;

	// メインアクターモード
	void MainActorMode(Vec3 pos);

	// サブアクターモード
	void SubActorMode(Vec3 pos);

	// サブアクターからメインアクターに変更する処理
	void ChangeMainActorMode(Vec3 pos);

	// 回転
	Vec3 RotateMainActorMode(Vec3 pos);	// メインアクターモードでの回転処理
	Vec3 RotateSubActorMode(Vec3 pos);	// サブアクターモードでの回転処理

	// 引数の座標を回転させる
	VECTOR MakeBasePos(VECTOR base);

	// メインアクターからサブに変更したときの座標を保存する
	Vec3 m_savePos;
	Vec3 m_saveTarget;
	Vec3 m_saveAngle;

	// メインに変更するときの単位ベクトル
	Vec3 m_unitPos;
	Vec3 m_unitTarget;
	Vec3 m_target;

	// モード切替中フラグ
	bool m_changeFlag;
};

