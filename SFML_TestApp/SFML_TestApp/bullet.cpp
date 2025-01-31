#include "bullet.h"


Bullet::Bullet( Vector2f spritePos, Vector2f mousePos, Vector2f spriteOrigin, const Map& map) :
	mousePosition_(mousePos), map_(map)
{
	Image image;
	image.loadFromFile("resource/bullet_0.png");

	image.createMaskFromColor(Color(255, 255, 255));
	texture_.loadFromImage(image);
	sprite_.setTexture(texture_);

	sprite_.setPosition(spritePos);
	sprite_.setOrigin(spriteOrigin);

	setViewDirection();
}


void Bullet::setViewDirection()
{
	float dX = mousePosition_.x - sprite_.getPosition().x;	
	float dY = mousePosition_.y - sprite_.getPosition().y;
	float distance = sqrt(pow(dX, 2) + pow(dY, 2));

	angleViewSprite_ = (atan2(dY, dX)) / 3.14159265f * 180;	
	moving_.x = dX / distance * 25.0f;
	moving_.y = dY / distance * 25.0f;

	sprite_.setRotation(angleViewSprite_);
}


void Bullet::collisionWithMap()
{
	//for (int i = (spritePosition_.y - spriteOrigin_.y) / 100;
	//	i < (spritePosition_.y + (spriteSize_.y - spriteOrigin_.y)) / 100; i++)
	//	for (int j = (spritePosition_.x - spriteOrigin_.x) / 100;
	//		j < (spritePosition_.x + (spriteSize_.x - spriteOrigin_.x)) / 100; j++)
	//		if (map_.getTileMap()[i][j] == '0' || map_.getTileMap()[i][j] == 'm') {
	//			/*if (moveDirection == MoveDirection::DOWN)
	//				spritePosition_.y = i * 100 - (spriteSize_.y - spriteOrigin_.y);

	//			if (moveDirection == MoveDirection::UP)
	//				spritePosition_.y = i * 100 + (100 + spriteOrigin_.y);

	//			if (moveDirection == MoveDirection::RIGHT)
	//				spritePosition_.x = j * 100 - (spriteSize_.x - spriteOrigin_.x);

	//			if (moveDirection == MoveDirection::LEFT)
	//				spritePosition_.x = j * 100 + (100 + spriteOrigin_.x);*/
	//			
	//			isLive_ = false;
	//		}

}


void Bullet::update()
{
	collisionWithMap();
	sprite_.move(moving_);
}




