#include "Particle.h"
#include "Scene.h"

Particle::Particle(const Particle& other) : GameObject(other.name, other.scene)
{
	pose = new physx::PxTransform(other.pose->p);
	velocity = other.velocity;
	acceleration = other.acceleration;
	damping = other.damping;
	size = other.size;
	startlifeTime = other.startlifeTime;

	color = { 0.5, 1, 1, 1.0 };
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(size)), pose, color);

}

Particle::Particle(string nam, Scene* scn, Vector3 Pos) : GameObject(nam, scn)
{
	pose = new physx::PxTransform(Pos);
	velocity = { 0,0,0 };
	acceleration = { 0,0,0 };
	damping = 0.5;
	size = 5;
	startlifeTime = 10;

	color = { 0.5, 1, 1, 1.0 };
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(size)), pose, color);

}


Particle::~Particle()
{
	cout << "-----PARTICULA ELIMINADA -----" << endl;;
}



void Particle::integrate(double t)
{
	// selecciona si euler semi-implicito
	if (eulerSemiimplicito) {
		velocity = velocity + t * acceleration;
		pose->p = pose->p + t * velocity;
		velocity = velocity * pow(damping, t);
	}
	else {
		pose->p = pose->p + t * velocity;
		velocity = velocity + t * acceleration;
		velocity = velocity * pow(damping, t);
	}
}

bool Particle::update(double t)
{
	// ANDRES AQUI LAS PARTICULAS QUE SE MUEVEN NO TIENEN BIEN PUESTAS LAS COORDENADAS (NAN) o el transform hace cosas raras en algun punto
	//cout << velocity.x << "/" << velocity.y << "/" << velocity.x << name << endl;
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

	if (pose->p.y <= floor)
		pose->p.y = floor;


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
