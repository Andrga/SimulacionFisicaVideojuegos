#include "Particle.h"

Particle::Particle(Vector3 Pos, Vector3 Vel):
	Particle(Pos, Vel, { 0,0,0 }, 1)
{}

Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc) :
	Particle(Pos, Vel, Acc, 1)
{}

Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc, float Dmp)
{
	pose = physx::PxTransform(Pos);
	vel = Vel;
	acc = Acc;
	dmp = Dmp;

	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(3)), &pose, { 0.5, 1, 1, 1.0 });
}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
}

void Particle::integrate(double t)
{
	pose.p = pose.p + t * vel;
	vel = vel + t * acc;
	vel = vel * pow(dmp, t);
}

