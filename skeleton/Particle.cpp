#include "Particle.h"

Particle::Particle(const Particle& other):
	Particle(other.pose.p, other.velocity, other.acceleration, other.damping, other.size, other.startlifeTime)
{}

Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc, float Dmp, float siz, float lifet) :
	pose(physx::PxTransform(Pos)), velocity(Vel), acceleration(Acc), damping(Dmp), size(siz), startlifeTime(lifet)
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

	if (lifeTime > startlifeTime)
	{
		alive = false;
		return false;
	}
	else
		lifeTime += t;

	// Metodo que hace los calculos para integrar la posicion
	integrate(t);

	return true;
}

void Particle::setPosition(Vector3 pos)
{
	pose.p = pos;
}
