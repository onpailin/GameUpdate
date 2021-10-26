#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

#include<iostream>

using namespace std;
using namespace sf;

class Player
{
private:
	Sprite sprite;
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

	bool moving;
	int standNum;
	int moveNum;
	bool turnLeft;

	void initVariables();
	void initSprite();
	void initAnimetion();
	void initPhysics();
public:
	Player();
	virtual ~Player();
	//Accessors
	const bool& getAnimSwitch();
	const sf::FloatRect getGlobalBounds() const;
	const sf::Vector2f gatPosition() const;
	//Modifiers
	void setPosition(const float x, const float y);

	//Function
	void updateInput(float deltaTime);
	void updateAnimation();
	void update(RenderTarget* target, float deltaTime);
	void render(RenderTarget* target);

	void updateMovement();
public:
	float jumpF = 400;
	float g = 9.8;
	float mass = 80;
	float a = 0;
};
