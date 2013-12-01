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
	filename = (char *)_filename;
	currNum = 0;
	interChange=0;
}

spriteSheet::spriteSheet(char* _filename, SDL_Renderer* rendr)
{
	renderer = rendr;
	image = load_image(_filename,renderer);
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
	printf("%s - ADDING COORDS (%d,%d) %d-%d\n",(const char*)filename,x,y,w,h);
	int num = numList[sequence];
	SDL_Rect imga;
	animList[sequence].push_back(imga);

	animList[sequence][num].x = x;
	animList[sequence][num].y = y;
	animList[sequence][num].w = w;
	animList[sequence][num].h = h;


	printf("%s - %s[%d] INIT SUCCESS\n",(const char*)filename,sequence.c_str(),numList[sequence]);
	numList[sequence] += 1;
}
void spriteSheet::render(int x, int y, int num, std::string sequence, Camera cam)
{
	printf(":)\n");
	printf("%s - GETTING SEQ %s[%d]\n", (const char*)filename, sequence.c_str(), num);
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