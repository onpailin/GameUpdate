#include "dispoint.h"
dispoint::dispoint(float x, float y, Texture* texture)
{
	this->frame = 0;
	this->texture = texture;

	this->preWidth = 0.f;
	this->preHeight = 0.f;
	this->width = 22.f;
	this->height = 25.f;
	this->delay = 0;
	this->x = x;
	this->y = y;
	this->initdispoint();
	this->decayss = 600;
}
dispoint::~dispoint()
{
	//dtor
}
void dispoint::initdispoint()
{
	this->currentFrame = IntRect(this->preWidth, this->preHeight, this->width, this->height);
	this->dispoints.setTexture(this->texture);
	this->dispoints.setTextureRect(this->currentFrame);
	this->dispoints.setRadius(40.f);
	this->dispoints.setPosition(this->x, this->y);
	this->dispoints.setScale(Vector2f(0.4f, 0.4f));
}

void dispoint::updatedispoint() {

	this->dispoints.setPosition(this->x, this->y);
	if (this->delay < 0) {

		this->delay = 10;

		this->frame++;
		this->frame %= 4;
	}
	this->delay--;
	this->decayss--;

	if (this->decayss < 300) {

		this->dispoints.setFillColor(Color(255, 255, 255, 255));
		if (this->decayss % 40 < 20) this->dispoints.setFillColor(Color(255, 255, 255, 60));
	}
	this->currentFrame = IntRect(this->preWidth + (this->frame * this->width), this->preHeight, this->width, this->height);
	this->dispoints.setTextureRect(this->currentFrame);
}

void dispoint::renderdispoint(RenderTarget* target)
{
	target->draw(this->dispoints);
}
