#pragma once

#include<iostream>
#include<vector>
#include<ctime>
#include<sstream>

#include "player1.h"

using namespace std;
using namespace sf;

class Game
{
private:
	RenderWindow* window;
	VideoMode videomode;
	Event ev;
	float deltaTime;
	Clock clock;

	//logic
	bool endGame;
	unsigned points;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;
	int health;

	Player player;

	vector<RectangleShape> enemies;
	Vector2i mousePosWindow;
	Vector2f mousePosView;

	Font font;

	Text uiText;

	RectangleShape enemy;
	void initVariables();
	void innitWindow();
	void innitFonts();
	void innitText();
	void innitEnemy();
public:
	Game();
	virtual ~Game();
	const bool running() const;
	const bool getEndGame() const;

	void spawnEnemy();
	void pollEvent();
	void updateCollision();
	void updateMousePosition();
	void updateText();
	void updateEnemies();
	void updateMap();
	void update();
	
	void collision(); 
	{
		if (this->player->getPosition().y + this->player->getGlobalBounds().height + 30 > this->window->getSize().y)
		{
		}
	}

	void renderText(RenderTarget& target);
	void renderEnemies(RenderTarget& target);
	void render();
};