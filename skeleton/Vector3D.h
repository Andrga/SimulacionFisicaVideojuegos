#include <cmath>
#pragma once

using namespace std;

class Vector3D
{
	float x, y, z;

	Vector3D() : x(0.0), y(0.0), z(0.0) {}
	Vector3D(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
	~Vector3D(){}

	// Obten el modulo del vector
	float module(Vector3D const vec) {
		return sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
	}

	// Normaliza el vector dado
	void normalize(Vector3D& vec) {
		float mod = module(vec);

		vec.x = vec.x / mod;
		vec.y = vec.y / mod;
		vec.z = vec.z / mod;
	}

	//

};

