#include "Sprite.h"


void Sprite::Draw()
{
	transform();
	setRenderState();
	draw();
}

Sprite::Sprite()
{
	this->display = true;
}

Sprite::~Sprite()
{
}

void Sprite::update()
{
	this->transform();
}

bool Sprite::getDisplay()
{
	return this->display;
}

void Sprite::enable()
{
	this->display = true;
}

void Sprite::disable()
{
	this->display = false;
}