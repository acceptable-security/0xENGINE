#include <SDL.h>
#include "world.h"
#include "level.h"
#include "object.h"
#include <string.h>
#include "image_functions.h"
#include "player.h"
#include "template.h"
#include <vector>

World::World(int grav, char* _background_file, Camera _cam, SDL_Renderer* _renderer, player* _plyr)
{
	plyr = *_plyr;
	renderer = _renderer;
	background_file = _background_file;
	bckrnd = background(_background_file, _renderer);
	cam = _cam;
	gravity = grav;
}

object_group World::getObjectGroup()
{
	return objects;
}

void World::load_level(Level lvl)
{
	clearObjects();
	//printf("SIZE %d\n", objlist.size());
	for(int i = 0; i < lvl.objlist.size(); i++)
	{
		appObject(lvl.objlist[i]);
	}
	setBackground(lvl.back);
	//printf("\ndone done\n");
}


void World::render()
{
	//printf("SIZE %d\n", objects.objectList.size());
	bckrnd.render();

	plyr.render(cam);

	objects.render(cam);
}

void World::update(bool up, bool down, bool left, bool right)
{
	//printf("SIZE %d\n", objects.objectList.size());
	plyr.update(up,down,left,right,objects.getList());
	cam.update(plyr);
}

void World::appObject(Object _obj)
{
	//printf("WORLD-POS: %d %d\n", _obj.getPosition().xV, _obj.getPosition().yV);
	objects.append(_obj);
	printf("APP BOYS %d\n", _obj.sprites.num);
	//printf("SIZE %d\n", objects.objectList.size());
}

void World::clearObjects()
{
	objects.empty();
}

void World::easyObject(spriteSheet sprites, std::string sequence, int frame, Vector2D pos, int damage)
{
	Object obj(sprites, frame, pos, renderer, damage, sequence);
	appObject(obj);
}

void World::easyObject(char* filename, Vector2D pos, int damage)
{
	Object obj(filename, pos, renderer, damage);
	appObject(obj);
}

void World::clean()
{
	bckrnd.clean();
	plyr.clean();
	objects.clean();
}

void World::setBackground(background bkrnd)
{
	bckrnd = bkrnd;
}