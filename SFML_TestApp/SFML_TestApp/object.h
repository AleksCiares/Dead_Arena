#pragma once
#include"map.h"
#include<vector>

using namespace sf;


class Object
{
public:
	Object(Vector2f spritePos, Vector2f spriteSize, Vector2f spriteOrigin,const Map& map);
	virtual ~Object() = default;
	const Sprite& getSprite() { return sprite_; }
	Vector2f& setPosition() { return spritePosition_; }
	const bool isLive() { return vitalStatistics_.isLive; }
	float& health() { return vitalStatistics_.health; }
	virtual void update(const Vector2f& targetPos, const float& time) = 0;
	
protected:
	Texture    texture_;
	Sprite	   sprite_;
	Vector2f   spritePosition_;
	Vector2f   spriteSize_;
	Vector2f   spriteOrigin_;
	Vector2f   moving_;
	const Map& map_;
	float	   speed_ = 0;
	float	   currentFrame_;
	bool	   isMove_;
	float	   angleViewSprite_;
	enum MoveDirection
	{
		UP,
		RIGHT,
		DOWN,
		LEFT
	}moveDirection_;
	struct VitalStatistics
	{
		float health;
		bool  isLive;
	}vitalStatistics_;

	virtual void setMoveDirection() = 0;
	virtual void setViewDirection(const Vector2f& targetPos);
	virtual void collisionWithMap();
	virtual void move(const float& time);
	
	
};