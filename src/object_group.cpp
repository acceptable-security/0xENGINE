#include "SDL.h"
#include "object_group.h"
#include "image_functions.h"
#include "object.h"
#include <vector>

void object_group::render(Camera cam)
{
	for(int i=0;i<objectList.size();i++)
	{
		objectList[i].render(cam);
	}
}

void object_group::empty()
{
	objectList.empty();
}

void object_group::clean()
{
	Object* obj;
	for(unsigned int i=0;i<objectList.size();i++)
	{
		obj = &objectList[i];
		obj->clean();
		objectList.erase(objectList.begin() + i);
	}
}

void object_group::append(Object obj)
{
	objectList.push_back(obj);
}

void object_group::remove(Object obj)
{
	if(isIn(obj) == false)
		return;
	int f = -1;
	for(unsigned int i = 0;i<objectList.size();i++)
	{
		if(&obj == &objectList[i])
		{
			f = i;
			break;
		}
	}
	if(f == -1) //should be impossible just in case..
		return;
	objectList.erase(objectList.begin() + f);
}

bool object_group::isIn(Object obj)
{
	for(unsigned int i=0;i<objectList.size();i++)
	{
		if(objectList[i].getSelf() == obj.getSelf())
			return true;
	}
	return false;
}