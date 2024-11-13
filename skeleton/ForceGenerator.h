#pragma once
#include "Particle.h"

class ForceSystem;

class ForceGenerator
{
protected:
	// Propiedades inicio
	float radious = 0;
	Vector3 origen = { 0,0,0 };

public:
	ForceGenerator(Vector3 org);
	virtual~ForceGenerator() = 0;


	virtual Vector3 generateForce(Vector3 pos, Vector3 velocity) = 0;
	bool onRadious(Vector3 Pos);

	void setRadious(float rad) { radious = rad; }
};

