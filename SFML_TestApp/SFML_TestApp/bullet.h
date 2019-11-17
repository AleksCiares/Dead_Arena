#pragma once
#include"map.h"

class Bullet 
{
public:
	Bullet(Vector2f spritePos, Vector2f mousePos, Vector2f spriteOrigin, const Map& map);
	~Bullet() = default;
	const Sprite& getSprite() { return sprite_; }
	bool& isLive() { return isLive_; }
	void update();

private:
	Texture    texture_;
	Sprite	   sprite_;
	Vector2f   mousePosition_;
	const Map& map_;
	bool	   isLive_;
	float	   angleViewSprite_;
	Vector2f   moving_;

	void setViewDirection();
	void collisionWithMap();
};

