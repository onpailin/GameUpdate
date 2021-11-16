#pragma once

#include<iostream>
#include<vector>
#include<ctime>
#include<sstream>
#include <tmxlite/Map.hpp>
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

	Texture texture;
	Sprite bg;
	Texture texture2;
	Sprite bg2;
	//State
	int game_state;

	//logic
	
	
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;
	int health;
	
	int points;
	
	vector<RectangleShape> enemies;
	Vector2i mousePosWindow;
	Vector2f mousePosView;

	sf::Font font;
	sf::Text guiText;

	RectangleShape enemy;
	void initVariables();
	void innitFonts();
	void innitText();
	void innitEnemy();
	void innitBg();
public:
	Game(RenderWindow* window);
	virtual ~Game();
	const bool running() const;
	const bool getEndGame() const;
	bool endGame;
	Player player;
	void spawnEnemy();
	void pollEvent();
	void updateMousePosition();
	
	void updateEnemies();
	void updateMap();
	void update();
	void collision();
	//void updateCollision();
	void updateText();
	void updateGui();
	void setPoint(int point);
	int getPoint();

	void renderText(RenderTarget& target);
	void renderEnemies(RenderTarget& target);
	void renderGui(RenderTarget& target);
	void render();
};
