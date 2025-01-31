#include "text.h"

MyText::MyText(const char* pathToFonts, const char* string, const Color& color, float characterSize, const Text::Style& style)
{
	font_.loadFromFile(pathToFonts);
	text_.setFont(font_);
	text_.setFillColor(color);
	text_.setCharacterSize(characterSize);
	text_.setStyle(style);

	string_ = string;
}


const Text& MyText::update(const Vector2f& position, const int& value)
{
	std::ostringstream outString;
	outString << " ";
	outString << value;
	text_.setString(string_ + outString.str());
	text_.setPosition(position);
	
	return text_;
}