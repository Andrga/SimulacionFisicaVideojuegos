#include "Particle.h"

Particle::Particle(Vector3 Pos, Vector3 Vel):
	Particle(Pos, Vel, { 0,0,0 }, 1)
{}

Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc) :
	Particle(Pos, Vel, Acc, 1)
{}

Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc, float Dmp):
	pose(physx::PxTransform(Pos)), velocity(Vel), acceleration(Acc), damping(Dmp), alive(true)
{
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(3)), &pose, { 0.5, 1, 1, 1.0 });
}

Particle::~Particle()
{
	cout << "-----PARTICULA ELIMINADA -----" << endl;
	DeregisterRenderItem(renderItem);
}

void Particle::integrate(double t)
{
	pose.p = pose.p + t * velocity;
	velocity = velocity + t * acceleration;
	velocity = velocity * pow(damping, t);
}

bool Particle::update(double t)
{
	if (!alive)
		return false;

	// Metodo que hace los calculos para integrar la posicion
	integrate(t);
	
	return true;
}

