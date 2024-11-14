#include "ForceGenerator.h"
#include "../basics/Scene.h"

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

Vector3 TorvellinoGenerator::generateForce(Particle& particle)
{
	Vector3 force(0, 0, 0),
		partPos = particle.getPose().p;

	//calculo de la fuerza en torvellino
	force = k * Vector3(-(partPos.z - origen.z), 50 - (partPos.y - origen.y), partPos.x - origen.x);

	force -= particle.getVelocity();

	return force;
}
