#pragma once
#include "SDL.h"
#include "template.h"
#include <map>
#include <vector>
#include <string>
class sequenceGroup
{
		std::map<std::string,spriteSheet> animList;
		std::string currAnim;
		std::vector<std::string> keyList;
	public:
		sequenceGroup() {}

		void insert(std::string, spriteSheet);
		void remove(std::string name);

		bool render(int x, int y, std::string name, bool, int);
		void rendertest(int x, int y, std::string name);
		void clean();
};