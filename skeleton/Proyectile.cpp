#include "Proyectile.h"

Proyectile::Proyectile(Vector3 Pos, Vector3 Vel, float siz) :
	Proyectile(Pos, Vel, { 0,0,0 }, { 0,-9.8,0 }, 1, 1, siz)
{
}

Proyectile::Proyectile(Vector3 Pos, Vector3 Vel, Vector3 Acc, Vector3 grav, float Dmp, float mas, float siz) :
	gravity(grav), mass(mas), Particle(Pos, Vel, Acc + grav, Dmp, siz)
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

