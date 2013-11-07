#include <SDL.h>
#include "world.h"
#include "object.h"
#include <string.h>
#include "image_functions.h"
#include "player.h"
#include <vector>

World::World(int grav, char* _background_file, Camera _cam, SDL_Renderer* _renderer, player* _plyr)
{
	plyr = *_plyr;
	renderer = _renderer;
	background_file = _background_file;
	bckrnd = new background(_background_file, _renderer);
	cam = _cam;
	gravity = grav;
}

object_group World::getObjectGroup()
{
	return objects;
}

void World::render()
{
	bckrnd->render();
	plyr.render(cam);
	objects.render(cam);
}

void World::update(bool up, bool down, bool left, bool right)
{
	plyr.update(up,down,left,right,objects.getList());
	cam.update(plyr);
}

void World::addObject(Object _obj)
{
	objects.append(&_obj);
}

void World::clearObjects()
{
	objects.empty();
}

void World::easyObject(spriteSheet sprites, std::string sequence, int frame, Vector2D pos, int damage)
{
	Object obj(sprites, frame, pos, renderer, damage, sequence);
	addObject(obj);
}

void World::easyObject(char* filename, Vector2D pos, int damage)
{
	Object obj(filename, pos, renderer, damage);
	addObject(obj);
}

void World::clean()
{
	bckrnd->clean();
	plyr.clean();
	objects.clean();
}

void World::setBackground(background* bkrnd)
{
	bckrnd = bkrnd;
}