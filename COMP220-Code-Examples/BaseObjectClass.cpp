#include "BaseObjectClass.h"



BaseObjectClass::BaseObjectClass(float xa, float ya, float za, float xb, float yb, float zb, float xc, float yc, float zc)
{
	addPoints(xa, ya, za, xb, yb, zb, xc, yc, zc);
}


BaseObjectClass::~BaseObjectClass()
{
}

void BaseObjectClass::addPoints(float xa, float ya, float za, float xb, float yb, float zb, float xc, float yc, float zc)
{
	pointList.push_back(Vect3D(xa, ya, za));
	pointList.push_back(Vect3D(xb, yb, zb));
	pointList.push_back(Vect3D(xc, yc, zc));
}

float * BaseObjectClass::getpoints()
{
	return &(pointList[0].x, pointList[0].y, pointList[0].z, pointList[1].x, pointList[1].y);
}
