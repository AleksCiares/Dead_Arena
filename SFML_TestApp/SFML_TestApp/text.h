#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<sstream>

using namespace sf;

class MyText
{
public:
	MyText(const char* pathToFonts, const char* string, const Color& color, float characterSize, const Text::Style& style);
	~MyText() = default;
	void setColor(const Color& color) { text_.setFillColor(color); }
	const Text& update(const Vector2f& position, const int& value);
	Text getText() { return text_; }

private:
	Font font_;
	Text text_;
	const char* string_;
};
