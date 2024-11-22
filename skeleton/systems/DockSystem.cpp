#include "DockSystem.h"

bool DockSystem::update(double t)
{
	for (auto p : docks) {
		if (!p.first || !p.second.first)
			continue;
		generateForce(p.first);
	}

	return false;
}

void DockSystem::generateForce(Particle* part1)
{
	Vector3 force{ 0,0,0 };
	Particle* part2 = docks[part1].first;
	float k = docks[part1].second.first, restLenth = docks[part1].second.second;

	const float length = (part1->getPose().p - part2->getPose().p).normalize();
	const float delta_x = length - restLenth;

	force = (part1->getPose().p - part2->getPose().p) * delta_x * k;

	part2->addForce(force);
}
