#pragma once
#include"object.h"


class Player : public Object
{
public:
	Player(Vector2f spritePos, Vector2f spriteSize, Vector2f spriteOrigin, const Map& map);
	~Player() = default;
	int& score() { return score_; }
	int& ammo() { return ammo_; }
	bool& isReloading() { return isReloading_; }
	void update(const Vector2f& targetPos, const float& time) override;
	
private:
	Texture reloadTexture_[15];
	int     score_;
	int     ammo_;
	bool    isReloading_ ;

	void setMoveDirection() override;
};