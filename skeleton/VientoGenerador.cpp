#include "VientoGenerador.h"


VientoGenerador::VientoGenerador(Vector3 org, Vector3 vVel) : ForceGenerator(org), vientoVel(vVel)
{
	setRadious(10);
}

VientoGenerador::~VientoGenerador()
{
}

Vector3 VientoGenerador::generateForce(Vector3 pos, Vector3 velocity)
{
	Vector3 force(0, 0, 0);
	// calculo de la fuerza en un viento no turbulento
	force = k1 * (vientoVel - velocity) + k2;
	//cout << force.x << "/" << force.y << "/" << force.z << endl;
	return force;
}

