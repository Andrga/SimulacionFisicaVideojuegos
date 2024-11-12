#pragma once
#include "ForceGenerator.h"
class VientoGenerador : public ForceGenerator
{
protected:
	//velocidad del viento
	Vector3 vientoVel = { 0,0,0 };
	//coheficientes de rozamiento
	float k1 = 1;
	Vector3 k2 = { 0,0,0 };
public:
	VientoGenerador(Vector3 org, Vector3 vVel);
	~VientoGenerador();

	Vector3 generateForce(Vector3 pos, Vector3 velocity) override;
};

