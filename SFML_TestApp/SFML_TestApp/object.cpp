#include"object.h"

Object::Object(Vector2f spritePos, Vector2f spriteSize, Vector2f spriteOrigin,const Map& map) :
	spritePosition_(spritePos), spriteSize_(spriteSize), spriteOrigin_(spriteOrigin), map_(map),
	isMove_(true), currentFrame_(0.0f), angleViewSprite_(0.0f)
{}

void Object::setViewDirection(const Vector2f& targetPos)
{
	float dX = targetPos.x - sprite_.getPosition().x;	// ¬ектор , колинеарный пр€мой, который пересекает спрайт и курсор
	float dY = targetPos.y - sprite_.getPosition().y;	// он же, координата y.
	angleViewSprite_ = (atan2(dY, dX)) / 3.14159265f * 180;	// ѕолучаем угол в радианах и переводим его в градусы.

	sprite_.setRotation(angleViewSprite_);
}


void Object::collisionWithMap()
{
	for (int i = (spritePosition_.y - spriteOrigin_.y) / 60;
		i < (spritePosition_.y + (spriteSize_.y - spriteOrigin_.y)) / 60; i++)
		for (int j = (spritePosition_.x - spriteOrigin_.x) / 60;
			j < (spritePosition_.x + (spriteSize_.x - spriteOrigin_.x)) / 60; j++)
			if (map_.getTileMap()[i][j] == '0') {
				if (moveDirection_ == MoveDirection::DOWN)
					spritePosition_.y = i * 60 - (spriteSize_.y - spriteOrigin_.y);

				if (moveDirection_ == MoveDirection::UP)
					spritePosition_.y = i * 60 + (60 + spriteOrigin_.y);

				if (moveDirection_ == MoveDirection::RIGHT)
					spritePosition_.x = j * 60 - (spriteSize_.x - spriteOrigin_.x);

				if (moveDirection_ == MoveDirection::LEFT)
					spritePosition_.x = j * 60 + (60 + spriteOrigin_.x);

				isMove_ = false;
			}
}


void Object::move(const float& time)
{
	isMove_ = true;
	spritePosition_.x += moving_.x * time;
	spritePosition_.y += moving_.y * time;
	moving_.x = 0;
	moving_.y = 0;
	collisionWithMap();

	sprite_.setPosition(spritePosition_);
}