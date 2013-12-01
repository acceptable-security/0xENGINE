#include "SDL.h"
#include "object_group.h"
#include "image_functions.h"
#include "object.h"
#include <vector>

//int object_group::amount()
//{
//	return objectList.size();
//}

void object_group::render(Camera cam)
{
	//printf("Object_Group Size: %d\n", objectList.size());
	for(unsigned int i=0;i<objectList.size();i++)
	{
		objectList[i].render(cam);
	}
	//printf("All done!\n");
}

void object_group::empty()
{
	printf("EMPTYING\n");
	objectList.empty();
}

void object_group::clean()
{
	printf("CLEANING\n");
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
	printf("ADDING POS: (%d,%d)\n", obj.getCoordSet().getPosition().xV,obj.getCoordSet().getPosition().yV);
	objectList.push_back(obj);
	printf("SIZE NOW %d\n",objectList.size());

}

void object_group::remove(Object obj)
{
	printf("REMOVING OBJ\n");
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