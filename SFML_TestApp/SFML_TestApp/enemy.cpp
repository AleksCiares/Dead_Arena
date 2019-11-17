#include "enemy.h"


Enemy::Enemy(Vector2f spritePos, Vector2f spriteSize, Vector2f spriteOrigin, const Map& map) :
	Object::Object(spritePos, spriteSize, spriteOrigin, map), readyToHit_(true), 
	pauseBetweenHit_(0.0f), currentFrameHit_(0.0f)
{
	Image image;
	image.loadFromFile("resource/enemy/move0.png");
	image.createMaskFromColor(Color(255, 255, 255));
	texture_.loadFromImage(image);
	sprite_.setTexture(texture_);

	sprite_.setPosition(spritePosition_);
	sprite_.setOrigin(spriteOrigin_);

	vitalStatistics_.health = 100.0f;
	vitalStatistics_.isLive = true;
	speed_ = 0.3f;

	for (int i = 0; i < 8; ++i) {
		image.loadFromFile("resource/enemy/move" + std::to_string(i) + ".png");
		image.createMaskFromColor(Color(255, 255, 255));
		movingTexture_[i].loadFromImage(image);
	}

	for (int i = 0; i < 4; ++i) {
		image.loadFromFile("resource/enemy/hit" + std::to_string(i) + ".png");
		image.createMaskFromColor(Color(255, 255, 255));
		hitTexture_[i].loadFromImage(image);
	}
}


void Enemy::setMoveDirection()
{
	if (-45.0f > angleViewSprite_ && angleViewSprite_ >= -135.0f) {
		moveDirection_ = MoveDirection::UP;
		moving_.x = 0;
		moving_.y = -speed_;
	}
	
	if (0.0f < angleViewSprite_ && angleViewSprite_ <= 45.0f || 0.0f >= angleViewSprite_ && angleViewSprite_ >= -45.0f) {
		moveDirection_ = MoveDirection::RIGHT;
		moving_.x = speed_;
		moving_.y = 0;
	}

	if (45.0f < angleViewSprite_ && angleViewSprite_ <= 135.0f) {
		moveDirection_ = MoveDirection::DOWN;
		moving_.x = 0;
		moving_.y = speed_;
	}

	if (-135.0f > angleViewSprite_ && angleViewSprite_ >= -180.0f || 135.0f < angleViewSprite_ && angleViewSprite_ < 180.0f) {
		moveDirection_ = MoveDirection::LEFT;
		moving_.x = -speed_;
		moving_.y = 0;
	}
}


void Enemy::update(const Vector2f& targetPos, const float& time)
{
	if (vitalStatistics_.health <= 0)
		vitalStatistics_.isLive = false;

	if (isMove_ == true) {
		currentFrame_ += time * 0.009f;

		if (currentFrame_ > 7)
			currentFrame_ -= 7;

		sprite_.setTexture(movingTexture_[(int)currentFrame_]);
	}

	if (readyToHit_ == false) {
		pauseBetweenHit_ += time * 0.005f;
		if (pauseBetweenHit_ > 12.0f) {
			readyToHit_ = true;
			pauseBetweenHit_ = 0.0f;
		}

		currentFrameHit_ += time * 0.002f;
		if (currentFrameHit_ > 3)
			currentFrameHit_ -= 3;

		sprite_.setTexture(hitTexture_[(int)currentFrameHit_]);
	}

	setViewDirection(targetPos);
	setMoveDirection();
	move(time);
}


