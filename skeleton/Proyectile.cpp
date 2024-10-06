#include "Proyectile.h"

Proyectile::Proyectile(Vector3 Pos, Vector3 Vel, Vector3 Acc, Vector3 grav, float Dmp, float mas) :
	gravity(grav), mass(mas), Particle(Pos, Vel, Acc + grav, Dmp)
{

}

bool Proyectile::update(double t)
{
	// si esta por debajo de una posicion, marca la particula para eliminar
	if (pose.p.y <= -10)
		alive = false;

	// Update base
	return Particle::update(t);

}

