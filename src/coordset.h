#ifndef COORDSET
#define COORDSET
class Object;
#include "vector.h"
//#include "object.h"
#include "SDL.h"


class CoordSet
{
	private:
		SDL_Surface *surface;
		Vector2D position;
		int w, h;
		bool initialized;
		Object *prnt;

		Vector2D centre, left, right, top, bottom, tleft, tright, bleft, bright;

	public:
		CoordSet();
		CoordSet(Vector2D posn, SDL_Surface *surf);
		CoordSet(Vector2D posn, int w, int h);
		void init(Vector2D posn, SDL_Surface *surf);
		void init(Vector2D posn, int w, int h);
		bool getInit();
		void setCoords();
		void setPosition(Vector2D);

		Vector2D getPosition();
		int getWidth();
		int getHeight();
		Vector2D getLeft();
		void setLeft(Vector2D);
		Vector2D getRight();
		void setRight(Vector2D);
		Vector2D getTop();
		void setTop(Vector2D);
		Vector2D getBottom();
		void setBottom(Vector2D);
		Vector2D getCentre();
		Vector2D getCenter();
		Vector2D getTopLeft();
		Vector2D getTopRight();
		Vector2D getBottomLeft();
		Vector2D getBottomRight();
		void CoordSet::setCoordsFromPos(Vector2D pos, int from);

		void setParent(Object *par);
		void update();
};
#endif