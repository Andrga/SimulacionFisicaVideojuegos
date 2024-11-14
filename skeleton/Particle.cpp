#include "Particle.h"

Particle::Particle(const Particle& other) :
	Particle(other.pose.p, other.velocity, other.acceleration, other.damping, other.size, other.startlifeTime)
{}

Particle::Particle(Vector3 Pos, Vector3 Vel) : Particle(Pos, Vel, { 0,0,0 }, 1, 1, 2)
{
}
Particle::Particle(Vector3 Pos, Vector3 Vel, float mass) : Particle(Pos, Vel, { 0,0,0 }, 1, 1, 2, mass)
{
}

Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc, float Dmp, float siz, float lifet, float mas) :
	pose(physx::PxTransform(Pos)), velocity(Vel), acceleration(Acc), damping(Dmp), size(siz), startlifeTime(lifet), mass(mas)
{
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(siz)), &pose, { 0.5, 1, 1, 1.0 });

}

Particle::~Particle()
{
	//cout << "-----PARTICULA ELIMINADA -----" << endl;
	DeregisterRenderItem(renderItem);
}

void Particle::integrate(double t)
{
	// selecciona si euler semi-implicito
	if (eulerSemiimplicito) {
		velocity = velocity + t * acceleration;
		pose.p = pose.p + t * velocity;
		velocity = velocity * pow(damping, t);
	}
	else {
		pose.p = pose.p + t * velocity;
		velocity = velocity + t * acceleration;
		velocity = velocity * pow(damping, t);
	}
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
	// Aplicacion de las fuerzas:
	if (forces.size() > 0)
		applyForce();

	// Metodo que hace los calculos para integrar la posicion
	integrate(t);

	//cout << acceleration.x << "/" << acceleration.y << "/" << acceleration.z << endl;
	return true;
}

void Particle::applyGravity()
{
	gravitable = !gravitable;

	gravitable ?
		acceleration += gravity :
		acceleration -= gravity;
}

void Particle::setVisibility(bool visibility)
{
	//cout << visibility << endl;
	visibility ?
		RegisterRenderItem(renderItem) :
		DeregisterRenderItem(renderItem);
	//renderItem->setVisible(visibility);
}

void Particle::setPosition(Vector3 pos)
{
	pose.p = pos;
}

void Particle::applyForce()
{
	Vector3 totalForce = { 0, 0, 0 };
	for (auto f : forces)
	{
		totalForce += f;
	}

	// F=m*a
	acceleration += totalForce / mass;
	forces.clear();
}
