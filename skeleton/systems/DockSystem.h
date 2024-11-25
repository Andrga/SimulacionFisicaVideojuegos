#pragma once
#include <map>
#include "../basics/System.h"
#include <algorithm>

struct Dock {
	Particle* Particle1;
	Particle* Particle2;

	float k;
	float resting_length;
};

class DockSystem : public System
{
protected:
	// part1, part2, k, resting_length
	vector<Dock> docks;

	Dock findDock(Particle* part);
public:
	DockSystem() {};
	~DockSystem() {};

	void addDock(Particle* obj1, Particle* obj2, float k, float rest_length) {
		docks.push_back({ obj1, obj2,k, rest_length});
	}
	void deRegisterDock(Particle* key);

	bool update(double t) override;
	void generateForce(Dock& dock);
};

