#include "object.h"
#include "vector.h"
#include "SDL.h"
#include <string>
#include "image_functions.h"
#include "template.h"
#include "coordset.h"
#include <iostream>

using namespace std;

background::background(char* filename, SDL_Renderer* rendr)
{
	file = filename;
	renderer = rendr;
	self = load_image(filename, renderer);
}

background::background(std::string filename, SDL_Renderer* rendr)
{
	file = (char *)filename.c_str();
	renderer = rendr;
	self = load_image((char *)filename.c_str(), renderer);
}

void background::render()
{
	apply_background(self, renderer);
}

void background::clean()
{
	SDL_DestroyTexture(self);
}

Object::Object(char* filename, Vector2D pos, SDL_Renderer* rendererErs, int damage)
{
	damage = 0;
	position.xV = pos.xV;
	position.yV = pos.yV;
	renderer = rendererErs;
	self = load_image(filename, renderer);
	int w, h = NULL;
	SDL_QueryTexture(self, NULL, NULL, &w, &h);
	coords.init(pos, w, h);
	coords.setParent(this);
	spriteSheeted = false;
}
Object::Object(spriteSheet _sprites, int frames, Vector2D pos, SDL_Renderer* rendererErs, int damage, std::string _sequence)
{
	sequence = _sequence;
	damage = 0;
	position.xV = pos.xV;
	position.yV = pos.yV;
	renderer = rendererErs;
	self = _sprites.getImage();
	spriteSheeted = true;
	frame = frames;
	sprites = _sprites;
	int w, h = NULL;
	SDL_QueryTexture(self, NULL, NULL, &w, &h);
	coords.init(pos, w, h);
	coords.setParent(this);
}

void Object::render(Camera cam){
	if(!spriteSheeted)
	{
		apply_texture(position.xValue(),position.yValue(), self, renderer, cam, NULL);
	}
	else
	{
		sprites.render(position.xV, position.yV, frame, sequence, cam);
	}
}

void Object::update(){
	coords.update();
}

void Object::clean()
{
	SDL_DestroyTexture(self);
}