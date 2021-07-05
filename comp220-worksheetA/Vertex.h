#pragma once


struct Vertex
{
	float x, y, z;								// Transform
	float r, g, b, a;							// Color
	float tu, tv;								// UV coordinates
	float xNormal, yNormal, zNormal;			// Normal Vector
	float tangentX, tangentY, tangentZ;			// Tangent Vector
	float biTangentX, biTangentY, biTangentZ;	// BiTangent Vector

#pragma region Inits
	void Init(float _x, float _y, float _z, float _r, float _g, float _b, float _a, float _tu, float _tv, float _xNormal, float _yNormal, float _zNormal, float _tangentX, float _tangentY, float _tangentZ, float _biTangentX, float _biTangentY, float _biTangentZ)
	{
		x = _x;
		y = _y;
		z = _z;
		r = _r;
		g = _g;
		b = _b;
		a = _a;
		tu = _tu;
		tv = _tv;
		xNormal = _xNormal;
		yNormal = _yNormal;
		zNormal = _zNormal;
		tangentX = _tangentX;
		tangentY = _tangentY;
		tangentZ = _tangentZ;
		biTangentX = _biTangentX;
		biTangentY = _biTangentY;
		biTangentZ = _biTangentZ;
	}

	void Init(float _values[18])
	{
		x = _values[0];
		y = _values[1];
		z = _values[2];
		r = _values[3];
		g = _values[4];
		b = _values[5];
		a = _values[6];
		tu = _values[7];
		tv = _values[8];
		xNormal = _values[9];
		yNormal = _values[11];
		zNormal = _values[12];
		tangentX = _values[13];
		tangentY = _values[14];
		tangentZ = _values[15];
		biTangentX = _values[16];
		biTangentY = _values[17];
		biTangentZ = _values[18];

	}

	void Init(float _transform[3], float _colour[4], float _uvs[2], float _normals[3], float _tan[3], float _bitan[3])
	{
		x = _transform[0];
		y = _transform[1];
		z = _transform[2];
		r = _colour[0];
		g = _colour[1];
		b = _colour [2] ;
		a = _colour[3];
		tu = _uvs[0];
		tv = _uvs[1];
		xNormal = _normals[0];
		yNormal = _normals[1];
		zNormal = _normals[2];
		tangentX = _tan[0];
		tangentY = _tan[1];
		tangentZ = _tan[2];
		biTangentX = _bitan[0];
		biTangentY = _bitan[1];
		biTangentZ = _bitan[2];

	}
#pragma endregion
};
