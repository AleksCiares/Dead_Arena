#include"player.h"

Player::Player(Vector2f spritePos, Vector2f spriteSize, Vector2f spriteOrigin, const Map& map) :
	Object::Object(spritePos, spriteSize, spriteOrigin, map), score_(0), ammo_(30), 
	isReloading_(false)
{
	Image image;

	image.loadFromFile("resource/sprites/handgun/reload/survivor-reload_handgun_0.png");
	image.createMaskFromColor(Color(255, 255, 255));
	texture_.loadFromImage(image);
	sprite_.setTexture(texture_);

	sprite_.setPosition(spritePosition_);
	sprite_.setOrigin(spriteOrigin_);

	vitalStatistics_.health = 100.0f;
	vitalStatistics_.isLive = true;
	speed_ = 0.6f;

	for (int i = 0; i < 15; ++i){
		image.loadFromFile("resource/sprites/handgun/reload/survivor-reload_handgun_" + std::to_string(i) + ".png");
		image.createMaskFromColor(Color(255, 255, 255));
		reloadTexture_[i].loadFromImage(image);
	}
}


void Player::setMoveDirection()
{
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		moveDirection_ = MoveDirection::RIGHT;
		moving_.x = speed_;
		moving_.y = 0;
	}

	if (Keyboard::isKeyPressed(Keyboard::A)) {
		moveDirection_ = MoveDirection::LEFT;
		moving_.x = -speed_;
		moving_.y = 0;
	}

	if (Keyboard::isKeyPressed(Keyboard::S)) {
		moveDirection_ = MoveDirection::DOWN;
		moving_.x = 0;
		moving_.y = speed_;
	}

	if (Keyboard::isKeyPressed(Keyboard::W)) {
		moveDirection_ = MoveDirection::UP;
		moving_.x = 0;
		moving_.y = -speed_;
	}
}


void Player::update(const Vector2f& targetPos, const float& time)
{
	if (vitalStatistics_.health <= 0)
		vitalStatistics_.isLive = false;
	
	if (isReloading_ == true) {

		currentFrame_ += time * 0.01f;
		if (currentFrame_ > 15) {
			currentFrame_ -= 15;
			ammo_ = 30;
			isReloading_ = false;
			sprite_.setTexture(texture_);
		}
		else
			sprite_.setTexture(reloadTexture_[(int)currentFrame_]);
	}

	setViewDirection(targetPos);
	setMoveDirection();
	move(time);
}
