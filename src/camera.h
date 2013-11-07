#include <SDL.h>
#include "player.h"
class Camera
{
	SDL_Rect* state;
public:
	Camera::Camera();
	Camera::Camera(int width, int height);
	void update(player);
}