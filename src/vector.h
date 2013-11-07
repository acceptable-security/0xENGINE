#ifndef VEC
#define VEC
class Vector2D
{
	public:		
		int xV, yV;

		//Init Function
		Vector2D(){ xV = 0; yV = 0; };
		Vector2D(int, int);

		//Operators
		Vector2D operator + (Vector2D);
		Vector2D operator - (Vector2D);
		Vector2D operator * (Vector2D);
		Vector2D operator / (Vector2D);
		Vector2D operator = (const Vector2D&);
		Vector2D operator += (const Vector2D&);
		Vector2D operator -= (const Vector2D&);
		Vector2D operator *= (const Vector2D&);
		Vector2D operator /= (const Vector2D&);
		
		//Other Functions
		int dotproduct(Vector2D);
		int distance(Vector2D);

		int xValue();
		int yValue();
};

#endif