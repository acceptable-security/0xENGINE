#pragma once
#include "SDL.h"
#include <vector>
#include "image_functions.h"
#include "object.h"

class object_group
{
		std::vector<Object> objectList;
	public:
		object_group(){};

		void append(Object*);
		void remove(Object);
		void empty();

		void render(Camera cam);
		void clean();

		bool isIn(Object);

		std::vector<Object> getList() { return objectList; };
};