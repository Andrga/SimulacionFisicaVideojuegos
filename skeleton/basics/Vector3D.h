#pragma once
#include <cmath>

using namespace std;

class Vector3D
{
private:
	float x, y, z;

public:
	Vector3D();
	Vector3D(float _x, float _y, float _z);
	~Vector3D();

	// Setters
	void setX(float _x);
	void setY(float _y);
	void setZ(float _z);
	// Getters
	float getX();
	float getY();
	float getZ();

	// Obten el modulo del vector
	float module(Vector3D const vec) const;

	// Normaliza el vector dado
	void normalize(Vector3D& vec);

	//Producto escalar de un vector por otro
	friend float operator*(const Vector3D& vec) const;

	//Producto de un vector por un escalar
	friend Vector3D operator*(float esc) const;

	//Suma de dos vectores
	friend Vector3D operator+(const Vector3D& vec) const;

	//Resta de dos vectores
	friend Vector3D operator-(const Vector3D& vec) const;

	//Igualar dos vectores
	friend Vector3D& operator=(const Vector3D& vec) const;

};

