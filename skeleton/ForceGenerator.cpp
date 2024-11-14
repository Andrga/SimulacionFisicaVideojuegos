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