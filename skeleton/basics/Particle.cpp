#include "Particle.h"

Particle::Particle(const Particle& other) :
	Particle(other.pose.p, other.velocity, other.acceleration, other.damping, other.size, other.startlifeTime)
{}

Particle::Particle(Vector3 Pos) : Particle(Pos, { 0,0,0 }, { 0,0,0 })
{
}

Particle::Particle(Vector3 Pos, Vector3 Vel) : Particle(Pos, Vel, { 0,0,0 }, 1, 1, 2)
{
}
Particle::Particle(Vector3 Pos, Vector3 Vel, float mass) : Particle(Pos, Vel, { 0,0,0 }, 1, 1, 2, mass)
{
}

Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc, float Dmp, float siz, float lifet, float mas) :
	velocity(Vel), acceleration(Acc), damping(Dmp), mass(mas)
{
	pose = physx::PxTransform(Pos);
	size = siz;
	startlifeTime = lifet;

	color = { 0.5, 1, 1, 1.0 };
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(siz)), &pose, color);

}

Particle::~Particle()
{
	cout << "-----PARTICULA ELIMINADA -----" << endl;
	DeregisterRenderItem(renderItem);
}

//void Particle::changeShape(physx::PxShape* shap)
//{
//	if (renderItem == nullptr)
//		renderItem = new RenderItem(shap, &pose, color);
//	else
//		renderItem->shape = shap;
//}


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

	// para particulas que no se mueven
	if (immovible) return true;

	// Aplicacion de las fuerzas:
	applyForce();

	// Metodo que hace los calculos para integrar la posicion
	integrate(t);

	if (pose.p.y <= floor)
		pose.p.y = floor;


	//cout << acceleration.x << "/" << acceleration.y << "/" << acceleration.z << endl;
	return true;
}

void Particle::applyGravity()
{
	gravitable = !gravitable;
}

void Particle::setVisibility(bool visibility)
{
	visibility ?
		RegisterRenderItem(renderItem) :
		DeregisterRenderItem(renderItem);
}



void Particle::applyForce()
{
	// calculamos la fuerza acumulada
	Vector3 totalForc = { 0,0,0 };
	for (auto f : forces)
		totalForc += f;
	forces.clear();

	// F=m*a
	acceleration = totalForc / mass;

	// Aplica la gravedad si es un objeto con gravedad
	if (gravitable)
		acceleration += gravity;
}
