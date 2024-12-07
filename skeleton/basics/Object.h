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
	string name;
public:
	Object() {};
	Object(string nam) :name(nam) {};
	virtual ~Object() {};

	virtual bool update(double t) = 0;

	// getters
	void setName(string nam) { name = nam; }
	// setters
	bool getAlive() const noexcept { return alive; }
	string getName() { return name; }
};

