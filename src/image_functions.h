#pragma once
#include <SDL.h>
#include <SDL_image.h>
//#include "player.h"

class player;


class Camera
{

public:
	SDL_Rect* state;
	Camera::Camera();
	Camera::Camera(int width, int height);
	void update(player target_player);
	SDL_Rect apply(SDL_Rect target_rect);
	Camera operator = (const Camera);
};

SDL_Texture* load_image(char* filename, SDL_Renderer* renderer);

void apply_texture(int x, int y, SDL_Texture* source, SDL_Renderer* destination, Camera cam, SDL_Rect* sS = NULL);

void apply_background(SDL_Texture* source, SDL_Renderer* destination);
