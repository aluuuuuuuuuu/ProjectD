#pragma once
#include "Components.h"
#include "Singleton.h"
#include "Constant.h"

// カメラクラス
class Camera :
	public Transform,
	public Constant,
	public Singleton<Camera>
{
	friend class Singleton<Camera>;

public:
	~Camera();

	void Init(Vec3 pos);
	void Update(Vec3 pos);

	// オズモードとブルータスモードを変更する
	void ChangeMode(bool osFlug);

private:
	Camera() {};

	// 関数ポインタ
	using m_modeFunc_t = void (Camera::*)(Vec3 pos);
	m_modeFunc_t m_modeFunc = nullptr;

	// ブルータスモード
	void BrutusMode(Vec3 pos);

	// オズモード
	void OsMode(Vec3 pos);

	// 回転
	void RotateBrutus(Vec3 pos);	// ブルータスモードでの回転処理
	Vec3 RotateOs(Vec3 pos);	// オズモードでの回転処理
};

