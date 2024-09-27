#include "Particle.h"

Particle::Particle(Vector3 Pos, Vector3 Vel)
{
	pose = physx::PxTransform(Pos);
	vel = Vel;

	renderItem = new RenderItem(CreateShape(physx:: PxSphereGeometry(3)), &pose, { 0.5, 1, 1, 1.0 });

}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
}

void Particle::integrate(double t)
{
	pose.p = pose.p + t * vel;
}

