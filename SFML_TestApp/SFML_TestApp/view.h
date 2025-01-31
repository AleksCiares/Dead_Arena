#pragma once
#include<SFML/Graphics.hpp>
using namespace sf;

View changeView(Vector2f position, View& view)
{
	if (position.x < 1000.0f) position.x = 1000.0f;
	if (position.x > 2600.0f) position.x = 2600.0f;
	if (position.y < 1000.0f) position.y = 1000.0f;
	if (position.y > 1500.0f)position.y = 1500.0f;

	view.setCenter(position);
	return view;
}
