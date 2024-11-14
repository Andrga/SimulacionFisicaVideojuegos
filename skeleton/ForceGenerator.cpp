#include "ForceGenerator.h"

void ForceGenerator::generateRadiousSphere()
{
	if (!renderItem)
	{
		//DeregisterRenderItem(renderItem);
		renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(radious)), &physx::PxTransform(origen), { 1, 0.0, 0.0, 0.0 });
	}

	renderItem->shape = CreateShape(physx::PxSphereGeometry(radious));
	//RegisterRenderItem(renderItem);
}

ForceGenerator::ForceGenerator(Vector3 org) : origen(org)
{
	generateRadiousSphere();
}

ForceGenerator::~ForceGenerator()
{
}

bool ForceGenerator::onRadious(Vector3 Pos)
{
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
	
	/*cout << "Generated force: " << force.x << "/" << force.y << "/" << force.z << endl;
	cout << "velocidad particle: " << particle.getVelocity().x << "/" << particle.getVelocity().y << "/" << particle.getVelocity().z << endl;
	*/

	return force;
}

