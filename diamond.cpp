#include "diamond.h"
diamond::diamond(float x, float y, Texture* texture)
{
	this->frame = 0;
	this->texture = texture;

	this->preWidth = 0.f;
	this->preHeight = 0.f;
	this->width = 23.f;
	this->height = 21.f;
	this->delay = 0;
	this->x = x;
	this->y = y;
	this->initdiamond();
	this->decays = 600;
}
diamond::~diamond()
{
	//dtor
}
void diamond::initdiamond()
{
	this->currentFrame = IntRect(this->preWidth, this->preHeight, this->width, this->height);
	this->diamonds.setTexture(this->texture);
	this->diamonds.setTextureRect(this->currentFrame);
	this->diamonds.setRadius(40.f);
	this->diamonds.setPosition(this->x, this->y);
	this->diamonds.setScale(Vector2f(0.4f, 0.4f));
}

void diamond::updatediamond() {

	this->diamonds.setPosition(this->x, this->y);
	if (this->delay < 0) {

		this->delay = 10;

		this->frame++;
		this->frame %= 4;
	}
	this->delay--;
	this->decays--;

	if (this->decays < 300) {

		this->diamonds.setFillColor(Color(255, 255, 255, 255));
		if (this->decays % 40 < 20) this->diamonds.setFillColor(Color(255, 255, 255, 60));
	}
	this->currentFrame = IntRect(this->preWidth + (this->frame * this->width), this->preHeight, this->width, this->height);
	this->diamonds.setTextureRect(this->currentFrame);
}

void diamond::renderdiamond(RenderTarget* target)
{
	target->draw(this->diamonds);
}