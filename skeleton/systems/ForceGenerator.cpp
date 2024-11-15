#include "ForceGenerator.h"
#include "../basics/Scene.h"

#include <cmath>

void ForceGenerator::generateRadiousSphere()
{
	if (radious <= 0)
		return;
	// si ya existe un render item, elimina el que esta y crea uno nuevo con el nuevo radio
	if (!widget)
	{
		widget = new Widget(origen, radious);

		scene->addObject(widget);
	}

	widget->changeShape(CreateShape(physx::PxSphereGeometry(radious)));
}

ForceGenerator::ForceGenerator(Vector3 org, Scene* scn) : origen(org), scene(scn)
{
	generateRadiousSphere();
}

ForceGenerator::~ForceGenerator()
{
}

bool ForceGenerator::onRadious(Vector3 Pos)
{
	if (radious == 0)
		return true;
	return (Pos - origen).magnitude() <= radious;
}

void ForceGenerator::setRadious(float rad)
{
	radious = rad;
	generateRadiousSphere();
}

// ------- GENERADOR DE VIENTO --------
Vector3 VientoGenerador::generateForce(Particle& particle)
{
	Vector3 force(0, 0, 0);
	// calculo de la fuerza en un viento no turbulento
	force = k1 * (vientoVel - particle.getVelocity()) + k2;

	return force;
}

// ------- GENERADOR DE TORVELLINO -------
Vector3 TorbellinoGenerator::generateForce(Particle& particle)
{
	Vector3 force(0, 0, 0),
		partPos = particle.getPose().p;

	//calculo de la fuerza en torvellino
	force = k * Vector3(-(partPos.z - origen.z), 50 - (partPos.y - origen.y), partPos.x - origen.x);

	force -= particle.getVelocity();

	return force;
}

// -------- GENERADOR DE EXPLOSION --------
Vector3 ExplosionGenerator::generateForce(Particle& particle)
{
	Vector3 force(0, 0, 0);
	simuleTime;

	if (simuleTime < 0 || simuleTime >= 4 * tau) return force;


	// distancia al centro de la explosion
	float r = (particle.getPose().p - origen).magnitude();
	// si la distancia es menor que el radio la fuerza es 0
	if (r >= radious) return force; // creo que esto no hace falta, porque si entra al metodo es porque r<radious

	force = ((k / r * r) * (particle.getPose().p - origen)) * exp(-simuleTime / tau);



	return force;
}
