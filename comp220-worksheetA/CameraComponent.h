#pragma once

struct CameraComponent
{
	float x, y, z;
	float lookX, lookY, lookZ;
	float upX, upY, upZ;
	float fov;
	float aspectWidth, aspectHeight;
	float nearClip, farClip;

	float view[16];
	float projection[16];

	void Init(float _x, float _y, float _z, float lx, float ly, float lz, float ux, float uy, float uz, float _fov, float _aspectWidth, float _aspectHeight, float _nearClip, float _farClip)
	{
		x = _x;
		y = _y;
		z = _z;
		lookX = lx;
		lookY = ly;
		lookZ = lz;
		upX = ux;
		upY = uy;
		upZ = uz;
		fov = _fov;
		aspectWidth = _aspectWidth;
		aspectHeight = _aspectHeight;
		nearClip = _nearClip;
		farClip = _farClip;
	}
};