#include "Vector3D.h"

Vector3D::Vector3D() : x(0.0), y(0.0), z(0.0) {}

Vector3D::Vector3D(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

Vector3D::~Vector3D() {}

// Setters
void Vector3D::setX(float _x) : x(_x) {}
void Vector3D::setY(float _y) : y(_y) {}
void Vector3D::setZ(float _z) : z(_z) {}
// Getters
float Vector3D::getX() { return x; }
float Vector3D::getY() { return y; }
float Vector3D::getZ() { return z; }

// Obten el modulo del vector
float Vector3D::module(Vector3D const vec) const {
	return sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
}

// Normaliza el vector dado
void Vector3D::normalize(Vector3D& vec) {
	float mod = module(vec);

	vec.x = vec.x / mod;
	vec.y = vec.y / mod;
	vec.z = vec.z / mod;
}

//Producto escalar de un vector por otro
float operator*(const Vector3D& vec) const
{
	return ((x * vec.getX()) + (y * vec.getY()) + (z * vec.getZ());
}

//Producto de un vector por un escalar
Vector3D operator*(float esc) const
{
	return Vector3D(x * esc, y * esc, z * esc);
}

Vector3D operator+(const Vector3D& vec) const
{
	return Vector3D(x + vec.getX(), y + vec.getY(), z + vec.getZ());
}

Vector3D operator-(const Vector3D& vec) const
{
	return Vector3D(x - vec.getX(), y - vec.getY(), z - vec.getZ());
}

Vector3D& operator=(const Vector3D& vec) const
{
	if (this != vec)
	{
		x = vec.getX();
		y = vec.getY();
		z = vec.getZ();
	}

	return *this;
}
