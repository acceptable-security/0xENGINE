#pragma once
#include "SDL.h"
#include "object.h"
#include <string>
#include <vector>
#include "vector.h"
#include "template.h"
#include "coordset.h"
#include "image_functions.h"

class player
{
		//Vector2D position;
		Vector2D velocity;
		spriteSheet* sequences;
		std::string currAnimName;
		int frameTime;
		bool shouldFlip;
		bool hasFlipped;
		int jump;
		int speed;
		bool onGround;
		int width, height;
		CoordSet cords;
		std::string prev_state;
		float cameraX, cameraY;
		
	public:
		player(){};
		player(Vector2D startpos, spriteSheet* animations, int frT, int jump, int speed, int width, int height);

		void render(Camera cam);
		void rendertest(Camera cam);

		void update(bool, bool, bool, bool, std::vector<Object>);
		void phys_update(std::vector<bool>, std::vector<Object>);
		void do_collisions(int, int, std::vector<Object>);
		void anim_update();
		
		void clean();

		Vector2D getPosition() { return cords.getPosition(); };
		CoordSet getCoordSet() { return cords; };

};