#include <iostream>
#include "vector.h"
#include "object.h"
#include "coordset.h"
//#include "SDL.h"

bool is_colliding(Object &objA, Object &objB)
{
	if(objA.getCoordSet().getBottomRight().xV < objB.getCoordSet().getTopLeft().xV)
		return false;
	if(objA.getCoordSet().getTopLeft().xV > objB.getCoordSet().getBottomRight().xV)
		return false;
	if(objA.getCoordSet().getBottomRight().yV < objB.getCoordSet().getTopLeft().yV)
		return false;
	if(objA.getCoordSet().getTopLeft().yV > objB.getCoordSet().getBottomRight().yV)
		return false;

	return true;
}

bool is_colliding(CoordSet &objA, CoordSet &objB)
{
	if(objA.getBottomRight().xV < objB.getTopLeft().xV)
		return false;
	if(objA.getTopLeft().xV > objB.getBottomRight().xV)
		return false;
	if(objA.getBottomRight().yV < objB.getTopLeft().yV)
		return false;
	if(objA.getTopLeft().yV > objB.getBottomRight().yV)
		return false;

	return true;
}