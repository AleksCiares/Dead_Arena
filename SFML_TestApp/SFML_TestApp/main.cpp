#pragma once
#include<vector>
#include<stdlib.h>

#include"SFML/Graphics.hpp"
#include"SFML/Window.hpp"
#include"SFML/Audio.hpp"

#include"map.h"
#include"view.h"
#include"player.h"
#include"enemy.h"4
#include"bullet.h"
#include"text.h"

using namespace sf;


struct MySprite
{
	Sprite sprite;
	Texture texture;
};

Bullet* bulletsFactory(Vector2f spritePos, Vector2f mousePos, Vector2f spriteOrigin, const Map& map)
{
	return new Bullet(spritePos, mousePos, spriteOrigin, map);
}

Enemy* enemyFactory(Vector2f spritePos, Vector2f spriteSize, Vector2f spriteOrigin,
	const Map& map)
{
	return new Enemy(spritePos, spriteSize, spriteOrigin, map);
}

float getRandomPos(const float& randomPos, const float& min, const float& max)
{
	return randomPos < min || randomPos > max ? getRandomPos(rand() % 10000, min, max) : randomPos;
}

MySprite* createSprite(const char* pathToImage, const Vector2f& position, const Color& colorMask)
{
	Image image;
	MySprite* object = new MySprite;

	image.loadFromFile(pathToImage);
	image.createMaskFromColor(colorMask);
	object->texture.loadFromImage(image);
	object->sprite.setTexture(object->texture);
	object->sprite.setPosition(position);

	return object;
}

void startGame(RenderWindow& window, Clock& clock, Event& event)
{
	View view;
	Map map(42, 60);
	MyText healthInfo("resource/font.ttf", "HEALTH", Color::Green, 60.0f, Text::Style::Bold);
	MyText ammoInfo("resource/font.ttf", "AMMO", Color::White, 60.0f, Text::Style::Bold);
	MyText scoreInfo("resource/font.ttf", "SCORE", Color::White, 70.0f, Text::Style::Bold);
	Player hero(Vector2f(1000.0f, 1000.0f), Vector2f(212.0f, 160.0f), Vector2f(80.0f, 80.0f), map);
	std::vector<Enemy* > enemies;
	std::vector<Bullet*> bullets;

	view.zoom(2);
	while (window.isOpen()) {
		Vector2f mousePosition = window.mapPixelToCoords(Mouse::getPosition(window));
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;

		//////////////////обработка событий с окном//////////////
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				return;
			}

			if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left &&
				hero.ammo() > 0 && hero.isReloading() == false) {
				bullets.push_back(bulletsFactory(hero.getSprite().getPosition(),
					mousePosition, Vector2f(10.0f, 3.0f), map));
				hero.ammo() -= 1;
			}
			
			if (event.key.code == Keyboard::R && hero.ammo() < 30)
				hero.isReloading() = true;
		}
		/////////////////////////////////////////////////////

		if (hero.isLive() == true) {
			hero.update(mousePosition, time);

			if (hero.health() < 20.0f)
				healthInfo.setColor(Color::Red);

			if (hero.ammo() == 0)
				ammoInfo.setColor(Color::Red);
			else
				ammoInfo.setColor(Color::Green);
		}
		else {
			MyText info("resource/font.ttf", "\t\tYOU DIE!!!\nYour score: ", Color::Red, 140.0f, Text::Style::Italic);

			while (window.isOpen()) {
				while (window.pollEvent(event)) {
					if (event.type == Event::Closed)
						return;
				}

				window.draw(info.update(window.getView().getCenter() + Vector2f(-550, -250), hero.score()));
				window.display();
			}
		}

		if (enemies.size() < 7)
			enemies.push_back(new Enemy(Vector2f(getRandomPos(rand() % 10000, 400.0f, 2700.0f), getRandomPos(rand() % 10000, 400.0f, 900.0f)),
				Vector2f(120.0f, 170.0f), Vector2f(70.0f, 80.0f), map));

		for (int i = 0; i < enemies.size();i++) {
			enemies[i]->update(hero.setPosition(), time);

			if (enemies[i]->getSprite().getGlobalBounds().intersects(hero.getSprite().getGlobalBounds()) && enemies[i]->setReadyToHit() == true) {
				hero.health() -= 2.0f;
				enemies[i]->setReadyToHit() = false;
			}

			if (!bullets.empty())
				for (int j = 0; j < bullets.size();j++) {
					if (enemies[i]->getSprite().getGlobalBounds().intersects(bullets[j]->getSprite().getGlobalBounds())) {
						enemies[i]->health() -= 20;
						bullets[j]->isLive() = false;
						delete bullets[j];
						bullets.erase(bullets.begin() + j);
					}
				}

			if (enemies[i]->isLive() == false) {
				delete enemies[i];
				enemies.erase(enemies.begin() + i);
				hero.score() += 10;
			}
		}

		if (!bullets.empty())
			for (int i = 0; i < bullets.size();i++)
				bullets[i]->update();


		changeView(hero.setPosition(), view);
		window.setView(view);
		window.clear(Color(136, 0, 0));
		map.createMap(window);

		for (int i = 0; i < bullets.size(); i++) {
			window.draw(bullets[i]->getSprite());
		}
		window.draw(hero.getSprite());
		for (int i = 0; i < enemies.size(); i++) {
			window.draw(enemies[i]->getSprite());
		}
		window.draw(healthInfo.update(view.getCenter() + Vector2f(-850.0f, 850.0f), hero.health()));
		window.draw(ammoInfo.update(view.getCenter() + Vector2f(500.0f, 850.0f), hero.ammo()));
		window.draw(scoreInfo.update(view.getCenter() + Vector2f(-850.0f, -850.0f), hero.score()));

		window.display();
	}
}


int main()
{	
	RenderWindow window(VideoMode(900, 900), "Dead Arena");
	Clock clock;
	View view;
	Event event;
	MySprite* background = createSprite("resource/background.jpg", Vector2f(), Color::Black);
	MySprite* newgameImage = createSprite("resource/newgame.png", Vector2f(310.0f, 450.0f), Color::White);
	MySprite* exitImage = createSprite("resource/exit.png", Vector2f(400.0f, 550.0f), Color::White);

	while (window.isOpen()) {

		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
		}

		Vector2f mousePosition = window.mapPixelToCoords(Mouse::getPosition(window));

		if (newgameImage->sprite.getGlobalBounds().contains(mousePosition)) {
			newgameImage->sprite.setColor(Color::Red);
			if (event.key.code == Mouse::Left) {
				startGame(window, clock, event);
				window.setView(view);
			}
		}
		else
			newgameImage->sprite.setColor(Color::White);

		if (exitImage->sprite.getGlobalBounds().contains(mousePosition)) {
			exitImage->sprite.setColor(Color::Red);
			if (event.key.code == Mouse::Left)
				window.close();
		}
		else
			exitImage->sprite.setColor(Color::White);

		window.clear();
		window.draw(background->sprite);
		window.draw(newgameImage->sprite);
		window.draw(exitImage->sprite);
		window.display();
	}

	delete background;
	delete newgameImage;
	delete exitImage;

	return 0;
}


