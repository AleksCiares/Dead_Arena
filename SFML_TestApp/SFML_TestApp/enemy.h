#pragma once
#include"object.h"


class Enemy : public Object
{
public:
	Enemy(Vector2f spritePos, Vector2f spriteSize, Vector2f spriteOrigin, const Map& map);
	~Enemy() = default;
	bool& setReadyToHit() { return readyToHit_; }
	void update(const Vector2f& targetPos, const float& time) override;

	
private:
	Texture movingTexture_[8];
	Texture hitTexture_[4];
	bool readyToHit_;
	float pauseBetweenHit_;
	float currentFrameHit_;

	void setMoveDirection() override;
};