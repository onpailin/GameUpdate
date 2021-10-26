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
	//physic
	Vector2f velocity;
	float velocityMax;
	float velocityMin;
	float acceletion;
	float drag;
	float gravity;
	float velocityMaxY;

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
	void resetVeloccityY();

	//Function
	void updateInput(float deltaTime);
	void updateAnimation();
	void update(RenderTarget* target,float deltaTime);
	void render(RenderTarget* target);

	void resetVelocityX();
	void resetVelocityY();
	

	void updateMovement();
public:
	float jumpF = 400;
	float g = 9.8;
	float mass = 50;
	float speed = 0;
	float a = 0;

};

