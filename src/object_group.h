#pragma once
#include "SDL.h"
#include <vector>
#include "image_functions.h"
#include "object.h"

class object_group
{
	public:
		std::vector<Object> objectList;
		object_group(){};

		void append(Object);
		void remove(Object);
		void empty();
		//int amount();

		void render(Camera cam);
		void clean();

		bool isIn(Object);

		std::vector<Object> getList() { return objectList; };
};