#include <SDL.h>
#include <vector>
#include "template.h"
#include "phys.h"
#include "object.h"
#include "player.h"
#include "vector.h"
#include "coordset.h"
#include "image_functions.h"

bool starts_with(std::string a, std::string b)
{
	std::string prefix(b);
	if(!a.compare(0, prefix.size(), prefix))
	{
		return true;
	}
	return false;
}

player::player(Vector2D startpos, spriteSheet* anim, int frT, int _jump, int _speed, int _width, int _height)
{
	width = _width;
	height = _height;
	//position = startpos;
	sequences = anim;
	velocity = Vector2D(0,0);
	frameTime = frT;
	shouldFlip = false;
	hasFlipped = false;
	currAnimName = "still";
	jump = _jump;
	speed = _speed;
	onGround = false;
	cords = CoordSet(startpos, _width, _height);
	prev_state = "";
}

void player::update(bool up, bool down, bool left, bool right, std::vector<Object> object_list)
{
	std::vector<bool> list;
	list.push_back(up);
	list.push_back(down);
	list.push_back(left);
	list.push_back(right);

	phys_update(list, object_list);
	anim_update();
}

void player::anim_update()
{
	//currAnimName = "still";
	//return;

	//experimental code, keeping outfor now.
	
	if(!onGround && velocity.yV != 0)
	{
		if(velocity.yV < 0)
		{
			if(currAnimName != "jumping")
			{
				currAnimName = "jumping";
			}
		}
		else
		{
			currAnimName = "falling";
		}
	}
	else
	{
		if(velocity.xV == 0)
		{
			currAnimName = "still";
		}
		else
		{
			currAnimName = "running";
			if(velocity.xV < 0)
			{
				shouldFlip = true;
			}
			else
			{
				shouldFlip = false;
			}
		}
	}

}

void player::do_collisions(int velX, int velY, std::vector<Object> object_list)
{
	Object obj;
	for(int i = 0; i < object_list.size();i++)
	{
		obj = object_list[i];
		if(obj.isColliding())
		{
			//printf("CHEKING AT %i %i\n", cords.getPosition().xV, cords.getPosition().yV);
			if(is_colliding(cords, obj.getCoordSet()))
			{
				//printf("COLLISION BITCHES\n");
				if(obj.getDamage() > 0)
				{
					//take damage like a man.
				}
				if(velX > 0)
				{
					cords.setCoordsFromPos(Vector2D(obj.getCoordSet().getLeft().xV - 1, cords.getRight().yV),3);
					velocity.xV = 0;
				}
				if(velX < 0)
				{
					cords.setCoordsFromPos(Vector2D(obj.getCoordSet().getRight().xV + 1, cords.getLeft().yV),2);
					velocity.xV = 0;
				}
				if(velY > 0)
				{
					cords.setCoordsFromPos(Vector2D(cords.getBottom().xV, obj.getCoordSet().getTop().yV - 1),1);
					onGround = true;			
					velocity.yV = 0;
				}
				if(velY < 0)
				{
					cords.setCoordsFromPos(Vector2D(cords.getTop().xV, obj.getCoordSet().getBottom().yV + 1),0);
				}

			}
		}
	}
}


void player::phys_update(std::vector<bool> list, std::vector<Object> object_list)
{
	if(list[0])
	{
		if(onGround)
			velocity.yV -= jump;
	}
	if(list[2])
	{
		velocity.xV = -1 * speed;
	}
	if(list[3])
	{
		velocity.xV = speed;
	}
	if(!onGround)
	{
		velocity.yV += 1; //gravity
		if(velocity.yV > 30)
		{
			velocity.yV = 30;
		}
	}
	if((!list[2] && !list[3]))
		velocity.xV = 0;

	cords.setPosition(Vector2D(cords.getPosition().xV + velocity.xV, cords.getPosition().yV));
	do_collisions(velocity.xV, 0, object_list);
	
	cords.setPosition(Vector2D(cords.getPosition().xV, cords.getPosition().yV + velocity.yV));
	onGround = false;
	do_collisions(0,velocity.yV, object_list);
}

void player::render(Camera cam)
{
//	if(shouldFlip && !hasFlipped)
//	{
//		hasFlipped = true;
		//flip image
//	}
	Vector2D *position = &getPosition();
	int x = position->xV;
	int y = position->yV;

	sequences->renderNext(x, y,  cam,true, currAnimName);
	//hasFlipped = false;
}
/*
void player::rendertest()
{
	Vector2D *position = &getPosition();
	int x = position->xV;
	int y = position->yV;
	sequences->rendertest(x, y, "still");
}
*/
void player::clean()
{
	sequences->clean();
}