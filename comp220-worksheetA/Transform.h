#pragma once

struct Transform
{
	float x, y, z;			// Transform
	float qW, qX, qY, qZ;	// Rotation
	float sX, sY, sZ;		// Scale
	void Init(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}
};