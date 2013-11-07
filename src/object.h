#ifndef OBJECT
#define OBJECT
#pragma once
class CoordSet;
#include "coordset.h"
#include "vector.h"
#include "SDL.h"
#include <string>
#include "image_functions.h"
#include "template.h"

SDL_Surface* load_background(std::string);

class background
{
	private:
		char* file;
		SDL_Texture* self;
		SDL_Renderer* renderer;
	public:
		background(){};
		background(char*, SDL_Renderer*);

		void render();
		void clean();
};
class Object
{
	private:
		bool coliding;
		std::string sequence;
		bool rendering;
		bool spriteSheeted;
		spriteSheet* sprites;
		int frame;
		SDL_Renderer* renderer;
		SDL_Texture* self;
		Vector2D position;
		CoordSet coords;
		int damage;

	public:
		//Initiation Functions
		Object(){};
		Object(char*, Vector2D, SDL_Renderer*, int);
		Object(spriteSheet, int, Vector2D, SDL_Renderer*, int, std::string);

		//Functions
		void update();
		void render(Camera);
		void clean();

		SDL_Texture* getSelf(){ return self; };
		Vector2D getPosition(){ return position; };
		CoordSet getCoordSet(){ return coords; };
		bool isColliding() { return coliding; };
		int getDamage() { return damage; };
};
#endif