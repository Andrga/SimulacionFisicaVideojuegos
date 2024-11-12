#include "ForceGenerator.h"

ForceGenerator::ForceGenerator(Vector3 org): origen(org)
{
}

ForceGenerator::~ForceGenerator()
{
}

bool ForceGenerator::onRadious(Vector3 Pos)
{
	return (Pos - origen).magnitude() <= radious;
}