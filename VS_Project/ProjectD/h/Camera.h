#pragma once
#include "Components.h"
#include "Singleton.h"
#include "Constant.h"

#define OS_MODE 0
#define BRUTUS_MODE 1
#define SEQUENCE_MODE 2

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
	void ChangeMode(int mode);

private:
	Camera() {};

	// 関数ポインタ
	using m_modeFunc_t = void (Camera::*)(Vec3 pos);
	m_modeFunc_t m_modeFunc = nullptr;

	// ブルータスモード
	void BrutusMode(Vec3 pos);

	// オズモード
	void OsMode(Vec3 pos);

	// シーケンスモード
	void SequMode(Vec3 pos);

	// 回転
	void RotateBrutus(Vec3 pos);	// ブルータスモードでの回転処理
	Vec3 RotateOs(Vec3 pos);	// オズモードでの回転処理
};

