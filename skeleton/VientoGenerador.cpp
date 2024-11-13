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

	force = (vientoVel - velocity);
	//cout << force.x << "/" << force.y << "/" << force.z << endl;
	return force;
}

