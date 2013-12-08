#include <string>
#include <SDL.h>
#include "object.h"
#include "object_group.h"
#include "vector.h"
#include "image_functions.h"
#include "player.h"
#include "sound.h"
#include "level.h"
#include <vector>
#pragma once
class World
{
		char* background_file;
		player plyr;
		Camera cam;
		int gravity;
		SDL_Renderer* renderer;
		Sound music;
		std::string music_file;
		background bckrnd;
	public:
		object_group objects;
		World::World(){};
		World::World(int, char*, Camera, SDL_Renderer*, player*);
		
		void easyObject(spriteSheet sprites, std::string sequence, int frame, Vector2D pos, int damage);
		void easyObject(char* filename, Vector2D pos, int damage);
		void appObject(Object obj);
		void clearObjects();

		object_group getObjectGroup();

		void render();
		void update(bool, bool, bool, bool);
		void clean();
		void load_level(Level lvl);
		void setBackground(background);
		
		void loadMusic();
		void startMusic();
		void stopMusic();
};