#include "VientoGenerador.h"


VientoGenerador::VientoGenerador(Vector3 org, Vector3 vVel) : ForceGenerator(org), vientoVel(vVel)
{
}

VientoGenerador::~VientoGenerador()
{
}

Vector3 VientoGenerador::generateForce(Vector3 pos, Vector3 velocity)
{
	Vector3 force(0, 0, 0);

	force = k1 * (vientoVel - velocity) + k2;
	return force;
}

