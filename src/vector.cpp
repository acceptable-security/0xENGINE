#include "vector.h"
#include <math.h>
Vector2D::Vector2D(int a, int b){
	xV = a;
	yV = b;
}
Vector2D Vector2D::operator+(Vector2D additor){
	Vector2D temp;
	temp.xV = xV + additor.xV;
	temp.yV = yV + additor.yV;
	return temp;
}
Vector2D Vector2D::operator-(Vector2D subtractor){
	Vector2D temp;
	temp.xV = xV - subtractor.xV;
	temp.yV = yV - subtractor.yV;
	return temp;
}
Vector2D Vector2D::operator*(Vector2D multiplier){
	Vector2D temp;
	temp.xV = xV - multiplier.xV;
	temp.yV = yV - multiplier.yV;
	return temp;
}
Vector2D Vector2D::operator/(Vector2D divisor){
	Vector2D temp;
	temp.xV = xV - divisor.xV;
	temp.yV = yV - divisor.yV;
	return temp;
}

Vector2D Vector2D::operator=(const Vector2D &equar)
{
	xV = equar.xV;
	yV = equar.yV;
	return *this;
}

Vector2D Vector2D::operator+=(const Vector2D &arg)
{
	xV += arg.xV;
	yV += arg.yV;
	return *this;
}

Vector2D Vector2D::operator-=(const Vector2D &arg)
{
	xV -= arg.xV;
	yV -= arg.yV;
	return *this;
}

Vector2D Vector2D::operator*=(const Vector2D &arg)
{
	xV *= arg.xV;
	yV *= arg.yV;
	return *this;
}

Vector2D Vector2D::operator/=(const Vector2D &arg)
{
	xV /= arg.xV;
	yV /= arg.yV;
	return *this;
}

int Vector2D::distance(Vector2D other){
	int nX = other.xV - xV;
	int nY = other.yV - yV;
	return (int)(sqrt((float)nX*nX + (float)nY*nY));
}
int Vector2D::dotproduct(Vector2D other){
	return (xV * yV + other.xV * other.yV);
}

int Vector2D::xValue()
{
	return xV;
}
int Vector2D::yValue()
{
	return yV;
}