#pragma once
#include "SDL.h"
#include <map>
#include <vector>
#include <string>
#include "image_functions.h"

class spriteSheet
{
	int number;
	int interChange;
	int currNum;
	//std::vector<SDL_Rect[]> images;
	SDL_Texture* image;
	SDL_Renderer* renderer;
	std::string filename;
	std::string currAnim;


	public:
		int num;
		std::map<std::string,std::vector<SDL_Rect>> animList;
		std::map<std::string,int> changeList;
		std::vector<std::string> keyList;
		std::map<std::string,int> numList;
		spriteSheet(){};
		spriteSheet(std::string filename, SDL_Renderer*);
		spriteSheet(const char* filename, SDL_Renderer*);

		void setNum(int num);

		void newSequence(std::string, int);

		void addCoords(int, int, int, int, std::string); //x, y, w, h, sequence
		
		void render(int, int, int, std::string, Camera); //x, y, frame, sequence

		SDL_Texture* getImage() { return image; }

		bool renderNext(int, int, Camera cam,bool, std::string); //x, y, loop, framePerChange, sequence

		void renderTest(int, int, Camera); //x, y

		void clean();
}; 