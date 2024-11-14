#include "Proyectile.h"

Proyectile::Proyectile(Vector3 Pos, Vector3 Vel, float siz) :
	Proyectile(Pos, Vel, { 0,0,0 }, 1, 1, siz)
{
}

Proyectile::Proyectile(Vector3 Pos, Vector3 Vel, Vector3 Acc, float Dmp, float mas, float siz) :
	Particle(Pos, Vel, Acc, Dmp, siz)
{
	mass = mas;
	Particle::applyGravity();
}

bool Proyectile::update(double t)
{
	// si esta por debajo de una posicion, marca la particula para eliminar
	if (pose.p.y <= -10)
		alive = false;
	// Update base
	return Particle::update(t);

}

