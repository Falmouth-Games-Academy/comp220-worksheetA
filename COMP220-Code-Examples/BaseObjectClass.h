#pragma once

#include <vector>

//#define origin  Vect3D(0.0, 0.0, 0.0)

class BaseObjectClass
{

public:
	BaseObjectClass(float xa, float ya, float za, float xb, float yb, float zb, float xc, float yc, float zc );
	~BaseObjectClass();

	void addPoints(float xa, float ya, float za, float xb, float yb, float zb, float xc, float yc, float zc);

	struct Vect3D { 
		Vect3D(float ix, float iy, float iz) : x(ix), y(iy), z(iz) {}
		float x, y, z;
	};
	float * getpoints();
	std::vector<Vect3D> pointList;
};

