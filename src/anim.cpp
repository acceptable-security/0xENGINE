/*
#include "anim.h"
#include <string>
#include "template.h"
#include <map>

bool sequenceGroup::render(int x, int y, std::string name, bool loop, int change)
{
	return animList[name].renderNext(x, y, loop, change);
	//animList[name].renderTest(x,y);
	//return true;
}
void sequenceGroup::rendertest(int x, int y, std::string name)
{
	animList[name].renderTest(x,y);
}

void sequenceGroup::insert(std::string name, spriteSheet sprites)
{
	if(animList.count(name) == 0) 
	{
		keyList.push_back(name);
		animList[name] = sprites;
	}
}

void sequenceGroup::remove(std::string name)
{
	if(animList.count(name) == 1)
	{
		animList.erase(name);
	}
}

void sequenceGroup::clean()
{
	for(int i = 0; i <keyList.size();i++)
	{
		animList[keyList[i]].clean();
	}
}
*/