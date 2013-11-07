#include "template.h"
#include "image_functions.h"
#include "SDL.h"
#include <string>
#include <iostream>

spriteSheet::spriteSheet(char* filename, SDL_Renderer* rendr)
{
	renderer = rendr;
	image = load_image(filename,renderer);
	number=0;
	currNum = 0;
	interChange=0;
}
void spriteSheet::newSequence(std::string name, int changeTime)
{
	std::vector<SDL_Rect> image;
	animList[name] = image;
	changeList[name] = changeTime;
	//memcpy(&animList[name], &image, sizeof(image));
	numList[name] = 0;
	keyList.push_back(name);
}
void spriteSheet::addCoords(int x, int y, int w, int h, std::string sequence)
{
	int num = numList[sequence];
	SDL_Rect imga;
	animList[sequence].push_back(imga);
	//std::vector<SDL_Rect> image = animList[sequence];
	//SDL_Rect img = image.at(num);

	animList[sequence][num].x = x;
	animList[sequence][num].y = y;
	animList[sequence][num].w = w;
	animList[sequence][num].h = h;

	numList[sequence] += 1;
}
void spriteSheet::render(int x, int y, int num, std::string sequence, Camera cam)
{
	apply_texture(x, y, image, renderer, cam, &animList[sequence][num]);
}
void spriteSheet::renderTest(int x, int y, Camera cam)
{
	apply_texture(x, y, image, renderer, cam);
}

bool spriteSheet::renderNext(int x, int y, Camera cam,bool loop=false, std::string sequence="") // changeFrames == amount of frames per change
{
	if(currNum >= numList[sequence])
	{
		if(loop)
			currNum = 0;
		else
			return false;
	}
	//std::cout << currNum << " " << interChange << " " << changeList[sequence] << " " << numList[sequence] << std::endl;
	render(x,y,currNum, sequence, cam);

	//currNum += 1;
	interChange++;
	if (interChange >= changeList[sequence])
	{
		//std::cout << "Changing Frame" << std::endl;
		interChange = 0;
		currNum += 1;
	}
	return true;
}

void spriteSheet::clean()
{
	SDL_DestroyTexture(image);
}