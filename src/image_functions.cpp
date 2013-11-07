#include "image_functions.h"
#include "player.h"
/*
def complex_camera(camera, target_rect):
	l, t, _, _ = target_rect
	_, _, w, h = camera
	l, t, _, _ = -l+HALF_WIDTH, -t+HALF_HEIGHT, w, h

	l = min(0, l)                           # stop scrolling at the left edge
	l = max(-(camera.width-WIN_WIDTH)-600, l)   # stop scrolling at the right edge
	t = max(-(camera.height-WIN_HEIGHT)-800, t) # stop scrolling at the bottom
	t = min(0, t)                           # stop scrolling at the top
	return Rect(l, t, w, h)
*/

class Entity
{
public:
	int w, h, x, y;
	Entity::Entity(){};
};

int min(int a, int b)
{
	if(a > b)
		return b;
	return a;
}
int max(int a, int b)
{
	if(b > a)
		return b;
	return a;
}

SDL_Rect* complex_camera(SDL_Rect* state, Entity target_rect, int window_height, int window_width)
{
	int x, y, w, h;
	x = target_rect.x;
	y = target_rect.y;
	w = state->w;
	h = state->h;
	x -= window_width/2;
	y -= window_height/2;

	x = min(600, x);
	x = max(0, x);
	y = max(0, y);
	y = min(800, y);

	SDL_Rect *rect = new SDL_Rect();
	rect->x = x;
	rect->y = y;
	//printf("CMPLX CAM %i %i\n", rect->x, rect->y);
	rect->w = w;
	rect->h = h;

	return rect;
}

Camera Camera::operator = (const Camera equar)
{
	Camera boobs;
	boobs.state = equar.state;
	return boobs;
}



Camera::Camera()
{
	state = new SDL_Rect();
	state->w = 800;
	state->h = 600;
}

void Camera::update(player plyr)
{
	Entity plag;
	plag.x = plyr.getCoordSet().getTopLeft().xV;
	plag.y = plyr.getCoordSet().getTopLeft().yV;
	//printf("PLYR %i %i\n", plag.x, plag.y);
	state = complex_camera(state, plag, 600, 800);
	//printf("NEWSTATE %i %i\n", state->x, state->y);
}

SDL_Rect Camera::apply(SDL_Rect target_rect)
{
	SDL_Rect news;
	news.x = target_rect.x;
	news.y = target_rect.y;
	news.w = target_rect.w;
	news.h = target_rect.h;

	//printf("LOL %i %i\n", news.x, news.y);
	//printf("STATE %i %i\n", state->x,state->y);
	//printf("##################\n");
	news.x -= state->x;
	news.y -= state->y;

	return news;
}


SDL_Texture* load_image(char* filename, SDL_Renderer* renderer)
{
	//Temporary storage for the image that's loaded
	SDL_Surface* loadedImage = NULL;

	//The hardware-accelerated texture that will be used
	SDL_Texture* loadedTexture = NULL;

	//Load the image
	loadedImage = IMG_Load(filename);

	//If nothing went wrong in loading the image
	if (loadedImage != NULL)
	{
		//Create texture from image
		loadedTexture = SDL_CreateTextureFromSurface(renderer, loadedImage);

		//Free the old image
		SDL_FreeSurface(loadedImage);
	}

	//loadedTexture will be null if the condition wasn't satisfied, so return either null or a loaded texture
	return loadedTexture;
}



void apply_texture(int x, int y, SDL_Texture* source, SDL_Renderer* destination, Camera cam, SDL_Rect* sS)
{
	SDL_Rect offset;

	offset.x = x;
	offset.y = y;

	//printf("ORIGINAL %i %i\n", offset.x,offset.y);

	offset = cam.apply(offset);

	//printf("CAM AT %i %i\n", offset.x, offset.y);

	SDL_QueryTexture(source, NULL, NULL, &offset.w, &offset.h);

	if (sS != NULL) { if (sS->w != NULL) { offset.w = sS->w; } if (sS->h != NULL) { offset.h = sS->h; } }

	SDL_RenderCopy(destination, source, sS, &offset);
}

void apply_background(SDL_Texture* source, SDL_Renderer* destination)
{
	SDL_RenderCopy(destination, source, NULL, NULL);
}