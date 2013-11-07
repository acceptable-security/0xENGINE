#include <typeinfo>
#include <iostream>
#include <string>
#include "vector.h"
#include "SDL.h"
#include "coordset.h"
#include "object.h"

CoordSet::CoordSet()
{
	initialized = false;
}

CoordSet::CoordSet(Vector2D posn, SDL_Surface *surf)
{
	//std::cout << posn.xV << " " << posn.yV << std::endl;
	position = posn;
	//std::cout << position.xV << " " << position.yV << std::endl;
	surface = surf;

	w = surf->w;
	h = surf->h;

	setCoords();

	initialized = true;
}

CoordSet::CoordSet(Vector2D posn, int w, int h)
{
	position = posn;
	surface = NULL;

	this->w = w;
	this->h = h;

	setCoords();

	initialized = true;
}

void CoordSet::init(Vector2D posn, SDL_Surface *surf)
{
	if(initialized)
		return;

	//std::cout << posn.xV << " " << posn.yV << std::endl;
	position = posn;
	//std::cout << position.xV << " " << position.yV << std::endl;
	surface = surf;

	w = surf->w;
	h = surf->h;

	setCoords();

	initialized = true;
}

void CoordSet::init(Vector2D posn, int w, int h)
{
	if(initialized)
		return;

	//std::cout << posn.xV << " " << posn.yV << std::endl;
	position = posn;
	//std::cout << position.xV << " " << position.yV << std::endl;
	surface = NULL;

	this->w = w;
	this->h = h;

	setCoords();

	initialized = true;
}

void CoordSet::update()
{
	if(typeid(prnt).name() != "Object" || typeid(prnt).name() != "player" || !initialized)
		return;

	Vector2D oldpos = position;
	position = prnt->getPosition();
	Vector2D diff = position - oldpos;
	delete &oldpos;

	//Not simply calling setCoords to possibly squeeze out some resources.
	centre += diff;
	left += diff;
	right += diff;
	top += diff;
	bottom += diff;
	tleft = position;
	tright += diff;
	bleft += diff;
	bright += diff;
}

void CoordSet::setCoords()
{
	Vector2D posn = position;

	centre = (posn + Vector2D(w / 2, h / 2));
	left = (posn + Vector2D(0, h / 2));
	right = (posn + Vector2D(w, h / 2));
	top = (posn + Vector2D(w / 2, 0));
	bottom = (posn + Vector2D(w / 2, h));
	tleft = posn;
	tright = (posn + Vector2D(w, 0));
	bleft = (posn + Vector2D(0, h));
	bright = (posn + Vector2D(w, h));
}

void CoordSet::setCoordsFromPos(Vector2D posi, int from)
{
	switch(from)
	{
			case 0: //top
				position = posi - Vector2D(w / 2, 0);
				//printf("SHOULD BE %i %i\n", position.xV, position.yV);
				setCoords();
				break;
			case 1: //bottom
				position = posi - Vector2D(w / 2, h);
				setCoords();
				break;
			case 2: //left
				position = (posi - Vector2D(0, h/2));
				setCoords();
				break;
			case 3: //right
				position =  (posi - Vector2D(w, h/2));
				setCoords();
				break;
			default:
				break;
	}
}

void CoordSet::setPosition(Vector2D _pos) { position = _pos; setCoords(); }

Vector2D CoordSet::getPosition(){ return position; };
int CoordSet::getWidth(){ return w; };
int CoordSet::getHeight(){ return h; };
Vector2D CoordSet::getLeft(){ return left; };
void CoordSet::setLeft(Vector2D pos) { left = pos;	setCoords(); }
Vector2D CoordSet::getRight(){ return right; };
void CoordSet::setRight(Vector2D pos) { right = pos;	setCoords(); }
Vector2D CoordSet::getTop(){ return top; };
void CoordSet::setTop(Vector2D pos) { top = pos;	setCoords(); }
Vector2D CoordSet::getBottom(){ return bottom; };
void CoordSet::setBottom(Vector2D pos) { bottom = pos;	setCoords(); }
Vector2D CoordSet::getCentre(){ return centre; };
Vector2D CoordSet::getCenter(){ return centre; };
Vector2D CoordSet::getTopLeft(){ return tleft; };
Vector2D CoordSet::getTopRight(){ return tright; };
Vector2D CoordSet::getBottomLeft(){ return bleft; };
Vector2D CoordSet::getBottomRight(){ return bright; };
bool CoordSet::getInit(){ return initialized; };
void CoordSet::setParent(Object *par){ prnt = par; };