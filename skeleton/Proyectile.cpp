#include "Proyectile.h"

Proyectile::Proyectile(Vector3 Pos, Vector3 Vel, Vector3 Acc, Vector3 grav, float Dmp, float mas) :
	gravity(grav), mass(mas), Particle(Pos, Vel, gravity, Dmp)
{
}

Proyectile::~Proyectile()
{
}

void Proyectile::update(double t)
{

	// Update base
	Particle::update(t);


	//if (pose.p.y <= 0)
}

