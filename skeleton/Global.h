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

//	para la construccion del cohete
// tipos de modulos que puede contener el cohete
enum TipoModulo {
	CABINA, TANQUE, PROPULSOR
};

// informacion que contiene cada modulo
struct ModuloInfo
{
	TipoModulo tipo;
	ModuloInfo* derecha;
	ModuloInfo* abajo;
	ModuloInfo* izquierda;
	ModuloInfo* arriba;
};

// vector que indica los modulos del cohete
extern ModuloInfo* Cohete;