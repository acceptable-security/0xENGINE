#include "template.h"
#include "image_functions.h"
#include "SDL.h"
#include <string>
#include <iostream>

spriteSheet::spriteSheet(const char* _filename, SDL_Renderer* rendr)
{
	renderer = rendr;
	image = load_image((char *)_filename,renderer);
	number=0;
	filename = (std::string)_filename;
	currNum = 0;
	interChange=0;
	num=0;
}

spriteSheet::spriteSheet(std::string _filename, SDL_Renderer* rendr)
{
	renderer = rendr;
	image = load_image((char *)_filename.c_str(),renderer);
	number=0;
	filename = _filename;
	currNum = 0;
	interChange=0;
}
void spriteSheet::newSequence(std::string name, int changeTime)
{
	std::vector<SDL_Rect> image;
	animList[name] = image;
	changeList[name] = changeTime;
	numList[name] = 0;
	keyList.push_back(name);
}
void spriteSheet::addCoords(int x, int y, int w, int h, std::string sequence)
{
	int num = numList[sequence];
	SDL_Rect imga;
	animList[sequence].push_back(imga);

	animList[sequence][num].x = x;
	animList[sequence][num].y = y;
	animList[sequence][num].w = w;
	animList[sequence][num].h = h;

	numList[sequence] += 1;
}
void spriteSheet::render(int x, int y, int rnum, std::string sequence, Camera cam)
{
	if(numList[sequence] != 0 && numList[sequence] > rnum)
		apply_texture(x, y, image, renderer, cam, &animList[sequence][rnum]);

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
	render(x,y,currNum, sequence, cam);

	interChange++;
	if (interChange >= changeList[sequence])
	{
		interChange = 0;
		currNum += 1;
	}
	return true;
}

void spriteSheet::clean()
{
	SDL_DestroyTexture(image);
}