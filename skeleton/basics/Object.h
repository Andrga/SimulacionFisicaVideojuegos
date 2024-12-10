#pragma once

#include <PxPhysicsAPI.h>
#include <string>
#include "iostream"

using namespace std;
using namespace physx;

class Object
{
protected:
	bool alive = true;
public:
	Object() {};
	~Object() {};

	virtual bool update(double t) = 0;

	// getters
	bool getAlive() const noexcept { return alive; }
	// setters
	void setAlive(bool alv) noexcept { alive = alv; }
};

