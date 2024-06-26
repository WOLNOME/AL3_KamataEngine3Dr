#include "EnemyBullet.h"
#include "Function.h"
#include "TextureManager.h"
#include <cassert>

void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	// NULLポインタチェック
	assert(model);

	model_ = model;
	// テクスチャ読み込み
	textureHandle_ = TextureManager::Load("red.png");
	// 速度初期化
	velocity_ = velocity;

	worldTransform_.Initialize();
	// 引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;
	// Z方向に伸びた形状
	worldTransform_.scale_.x = 0.5f;
	worldTransform_.scale_.y = 0.5f;
	worldTransform_.scale_.z = 3.0f;
	// y軸周りの角度(θy)
	worldTransform_.rotation_.y = std::atan2(velocity_.x, velocity_.z);
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(-worldTransform_.rotation_.y);
	Vector3 velocityZ = Transform(velocity_, rotateYMatrix);
	// x軸周りの角度(θx)
	worldTransform_.rotation_.x = std::atan2(-velocityZ.y, velocityZ.z);
}

void EnemyBullet::Update() {
	// ワールドトランスフォームの更新
	worldTransform_.UpdateMatrix();

	// 速度加算
	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);

	// 時間経過でデス
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
}

void EnemyBullet::Draw(const ViewProjection& viewProjection) {
	// モデルの描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void EnemyBullet::OnCollision() { isDead_ = true; }

Vector3 EnemyBullet::GetWorldPosition() {
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}
