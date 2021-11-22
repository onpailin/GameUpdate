#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include<tmxlite/Map.hpp>
#include<tmxlite/Layer.hpp>
#include<tmxlite/TileLayer.hpp>
#include<tmxlite/ObjectGroup.hpp>
#include"Coins.h"
#include"diamond.h"
#include"dispoint.h"

#include <vector>
#include<iostream>

using namespace std;
using namespace sf;

struct Level
{
	unsigned int level_width;
	unsigned int level_height;
	unsigned int tile_width;
	unsigned int tile_height;
};


class Player
{
private:
	
	Texture texture;
	IntRect currentFrame;
	Clock aniTime;

	float gravity;

	bool jumping = false;

	float movementSpeed;
	float width;
	float height;
	float preWidth;
	float preHeight;
	
	Texture coin_texture;
	Texture diamond_texture;
	Texture dispoint_texture;
	int coins_delay;
	int diamond_delay;
	int dispoint_delay;
	void spawnCoins(RenderTarget* target);
	void spawndiamond(RenderTarget* target);
	void spawndispoint(RenderTarget* target);
	
	bool moving;
	int standNum;
	int moveNum;
	bool turnLeft;
	//Physics
	Vector2f velocity;
	float velocityMax;
	float velocityMin;
	float accleration;
	float drag;
	float velocityMaxY;

	tmx::Map map;
	unsigned int level_width;
	unsigned int level_height;
	unsigned int tile_width;
	unsigned int tile_height;
	vector<Level> solid;

	void initVariables();
	void initSprite();
	void initAnimetion();
	void initPhysics();

	vector<vector<int>> tiles;
	vector<RectangleShape> walls;
public:

	Sprite sprite;

	Player();
	virtual ~Player();
	//Accessors
	const bool& getAnimSwitch();
	const sf::FloatRect getGlobalBounds() const;
	const sf::Vector2f getPosition() const;
	//Modifiers
	void setPosition(const float x, const float y);

	//Function
	void updateInput(float deltaTime);
	void updateAnimation();
	void updateCollision();
	void update(RenderTarget* target, float deltaTime);
	void updateMaps();
	void render(RenderTarget* target);
	void updatePhysics();
	void resetVelocityX();
	void resetVelocityY();
	void loadmap();
	vector <Coins> coins;
	vector <diamond> diamonds;
	vector <dispoint> dispoints;
	void setTile();
	void setWall();
	void drawWall(RenderTarget* target);

	void updateMovement();
};
