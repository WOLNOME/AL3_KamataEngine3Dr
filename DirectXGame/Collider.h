#pragma once
#include "Vector3.h"
#include <cstdint>
class Collider {

public:
	virtual ~Collider() = default;
	float GetRadius() { return radius_; }
	virtual void SetRadius(float& radius) { radius_ = radius; }
	virtual void OnCollision();
	virtual Vector3 GetWorldPosition() = 0;
	uint32_t GetCollisionAttribute() { return collisionAttribute_; }
	void SetCollisionAttribute(const uint32_t collisionAttribute) { collisionAttribute_ = collisionAttribute; }
	uint32_t GetCollisionMask() { return CollisionMask_; }
	void SetCollisionMask(const uint32_t collisionMask) { CollisionMask_ = collisionMask; }

private:
	float radius_ = 1.5f;
	uint32_t collisionAttribute_ = 0xffffffff;
	uint32_t CollisionMask_ = 0xffffffff;
};