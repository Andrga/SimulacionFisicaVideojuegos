#pragma once
#include <PxPhysicsAPI.h>
#include "core.hpp"
#include <string>
#include "iostream"

class ParticleGenerator;
class GameObject;

struct GameObjectInfo
{
	GameObject* gameObject;
	ParticleGenerator* partGen;
};

extern GameObject* MovingObj;
extern bool Moving;

