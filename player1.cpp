#include "player1.h"



void Player::initVariables()
{
	this->movementSpeed = 5.f;
	this->preWidth = 33.f;
	this->preHeight = 32.f;
	this->width = 40.f;
	this->height = 55.f;
	this->moving = false;
	this->standNum = 2;
	this->moveNum = 1;
	this->turnLeft = false;
}

void Player::initSprite()
{
	if (!this->texture.loadFromFile("player.png"))
	{
		cout << "ERROR" << "\n";
	}
	this->currentFrame = IntRect(this->preWidth, this->preHeight, this->width, this->height);
	this->sprite.setTexture(this->texture);
	this->sprite.setTextureRect(this->currentFrame);
	this->sprite.scale(1.f, 1.f);
	this->sprite.setPosition(0.f, 0.f);
}

void Player::initAnimetion()
{
	this->aniTime.restart();
}

Player::Player()
{
	this->initVariables();
	this->initSprite();
	this->initAnimetion();
}

Player::~Player()
{
}

const sf::FloatRect Player::getGlobalBounds() const
{
	return this->sprite.getGlobalBounds();
}

const sf::Vector2f Player::gatPosition() const
{
	return this->sprite.getPosition();
}

void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Player::updateInput(float deltaTime)
{
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		this->sprite.move(-this->movementSpeed, 0.f);
		this->moving = true;
		this->turnLeft = true;
		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			this->sprite.move(0.f, -this->movementSpeed);
		}
		else if (Keyboard::isKeyPressed(Keyboard::S))
		{
			this->sprite.move(0.f, this->movementSpeed);
		}
	}
	else if (Keyboard::isKeyPressed(Keyboard::D))
	{
		this->sprite.move(this->movementSpeed, 0.f);
		this->moving = true;
		this->turnLeft = false;
		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			this->sprite.move(0.f, -this->movementSpeed);
		}
		else if (Keyboard::isKeyPressed(Keyboard::S))
		{
			this->sprite.move(0.f, this->movementSpeed);
		}
	}
	else if (Keyboard::isKeyPressed(Keyboard::W) && !jumping)
	{
		this->sprite.move(0.f, -this->movementSpeed);
		this->moving = true;
	}
	else if (Keyboard::isKeyPressed(Keyboard::S))
	{
		this->sprite.move(0.f, this->movementSpeed);
		this->moving = true;
	}
	else
	{
		this->moving = false;
	}
	if (Keyboard::isKeyPressed(Keyboard::Space) && !jumping)
	{
		this->jumping = true;
		this->a = jumpF / mass;
	}
	if (this->jumping)
	{
		a -= g * deltaTime;
		this->sprite.move(0, -a);
		if (this->sprite.getPosition().y > 525)
		{
			this->sprite.setPosition(this->sprite.getPosition().x, 525);
			this->jumping = false;
			a = 0;
		}
	}
}

void Player::updateAnimation()
{
	if (this->standNum >= 3)
	{
		this->standNum = 1;
	}
	if (this->moveNum >= 5)
	{
		this->moveNum = 1;
	}
	if (this->aniTime.getElapsedTime().asSeconds() >= 0.1f)
	{
		if (this->moving == false)
		{
			this->moveNum = 1;
			this->preHeight = 33.f;
			this->width = 39.f;
			switch (this->standNum)
			{
			case 1: this->preWidth = 82.f;
				break;
			case 2: this->preWidth = 33.f;
				break;
			default:
				break;
			}
			this->standNum++;
		}
		else if (this->moving == true)
		{
			this->standNum = 3;
			this->preHeight = 135.f;
			this->width = 38.f;
			switch (this->moveNum)
			{
			case 1: this->preWidth = 24.f;
				break;
			case 2: this->preWidth = 83.f;
				break;
			case 3: this->preWidth = 308.f;
				break;
			case 4: this->preWidth = 356.f;
				break;
			default:
				break;
			}
			this->moveNum++;
		}
		if (this->turnLeft == false)
		{
			this->currentFrame = IntRect(this->preWidth, this->preHeight, this->width, this->height);
		}
		else if (this->turnLeft == true)
		{
			this->currentFrame = IntRect(this->preWidth + this->width, this->preHeight, -this->width, this->height);
		}
		this->sprite.setTextureRect(this->currentFrame);
		this->aniTime.restart();
	}
}

void Player::update(RenderTarget* target, float deltaTime)
{
	this->updateInput(deltaTime);
	this->updateAnimation();
}

void Player::render(RenderTarget* target)
{
	target->draw(this->sprite);
}
