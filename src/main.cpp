//The headers
#include <SDL.h>
#include <SDL_mixer.h>
#include "image_functions.h"
#include "world.h"
#include "level.h"
#include "template.h"
#include "sound.h"
#include "timer.h"
//#include "anim.h"
#include <string>
#include <iostream>
#ifdef _WIN32
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2_mixer.lib")
#endif
using namespace std;

//The attributes of the screen
extern const int SCREEN_WIDTH = 800;
extern const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;
const int FRAMES_PER_SECOND = 60;

//The surfaces that will be used
SDL_Surface *message = NULL;
background *back = NULL;

//SDL2 variables
SDL_Window* mainwindow;
SDL_Renderer* renderer;

SDL_Event event;

//Keyboard
bool upKey = false, downKey = false, leftKey = false, rightKey = false;

bool init() {
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        return 1;
    }

	mainwindow = SDL_CreateWindow("0xENGINE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);

	if (mainwindow == NULL)
	{
		return 1;
	}

	renderer = SDL_CreateRenderer(mainwindow, -1, NULL);

	if (renderer == NULL)
	{
		return 1;
	}

	if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) == NULL)
	{
		return 1;
	}

	return true;
}

int main( int argc, char* args[] )
{
	init();

	//Sound music ("LOOPABLE1.wav",true);
	spriteSheet *teste = new spriteSheet("Untitled.png",renderer);
	teste->newSequence("first",0);
	teste->addCoords(0,0,1099,57,"first");

	Object objtest(*teste, 0, Vector2D(0,300),renderer, 0, "first");

	spriteSheet *test = new spriteSheet("testspritesheet.png", renderer);

	test->newSequence("still",30);
	test->addCoords(0,0,128,128,"still");

	test->newSequence("jumping",10);
	test->addCoords(0,256,128,128,"jumping");
	test->addCoords(128,256,128,128,"jumping");

	test->newSequence("running",15);
	test->addCoords(0,0,128,128,"running");
	test->addCoords(128,0,128,128,"running");

	test->newSequence("falling",10);
	test->addCoords(0,128,128,128,"falling");
	test->addCoords(128,128,128,128,"falling");

	Camera cam;
	player *plyr = new player(Vector2D(0,0), test, 10, 15, 6, 128, 128);

	World wrld(1, "stars.png", cam, renderer, plyr);
	///wrld.addObject(objtest);

	Level lvl(renderer,"level.lvl");
	lvl.Load();
	//lvl.addObject(objtest);
	lvl.loadToWorld(&wrld);

	bool alive = true;
	bool music_bool = true;
	bool music2_bool = true;
	int frame = 0;
	Timer fps;
	//music.play();
	//lvl.playMusic();
	while(alive)
	{
		fps.start();

		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
				alive = false;
			else if(event.type == SDL_KEYDOWN)
			{
				switch(event.key.keysym.sym)
				{
					case SDLK_UP:
						upKey=true;
						break;
					case SDLK_DOWN:
						downKey=true;
						break;
					case SDLK_LEFT:
						leftKey=true;
						break;
					case SDLK_RIGHT:
						rightKey=true;
						break;
				}
			}
			else if (event.type == SDL_KEYUP)
			{
				switch (event.key.keysym.sym)
				{
					case SDLK_UP:
						upKey = false;
						break;
					case SDLK_DOWN:
						downKey = false;
						break;
					case SDLK_LEFT:
						leftKey = false;
						break;
					case SDLK_RIGHT:
						rightKey = false;
						break;	
				}
			}
		}
		wrld.update(upKey, downKey, leftKey, rightKey);
		
		wrld.render();
		SDL_RenderPresent(renderer);

		frame++;

		if(fps.get_ticks() < 1000 / FRAMES_PER_SECOND)
		{
			SDL_Delay(1000/FRAMES_PER_SECOND - fps.get_ticks());
		}
	}

	test->clean();
	wrld.clean();
	//lvl.clean();
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(mainwindow);
	
    //Quit SDL
    SDL_Quit();

	return 0;
}
