#include "coins.h"
Coins::Coins(float x, float y, Texture* texture)
{
	this->frame = 0;
	this->texture = texture;

	this->preWidth = 0.f;
	this->preHeight = 0.f;
	this->width = 22.f;
	this->height = 23.f;
	this->delay = 0;
	this->x = x;
	this->y = y;
    this->initcoins();
	this->decay = 600;
}

Coins::~Coins()
{
    //dtor
}

void Coins::initcoins()
{
	this->currentFrame = IntRect(this->preWidth, this->preHeight, this->width, this->height);
	this->coin.setTexture(this->texture);
	this->coin.setTextureRect(this->currentFrame);
	this->coin.setRadius(40.f);
    this->coin.setPosition(this->x, this->y);
	this->coin.setScale(Vector2f(0.4f, 0.4f));
}

void Coins::updatecoins() {

	this->coin.setPosition(this->x, this->y);
	if(this->delay < 0) {

		this->delay = 10;

		this->frame++;
		this->frame %= 4;
	}
	this->delay --;
	this->decay --;

	if(this->decay < 300) {

		this->coin.setFillColor(Color(255, 255, 255, 255));
		if(this->decay % 40 < 20) this->coin.setFillColor(Color(255, 255, 255, 60));
	}
	this->currentFrame = IntRect(this->preWidth + (this->frame * this->width), this->preHeight, this->width, this->height);
	this->coin.setTextureRect(this->currentFrame);
}
 
void Coins::rendercoins(RenderTarget* target)
{
    target->draw(this->coin);
}