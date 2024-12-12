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

extern float sizeModul;
extern Vector3 tamanioCohete;

// constantes juego
extern float FUERZA_PROPULSOR;

extern float RADIO_PLANETA_TIERRA;
extern float RADIO_GRAVEDAD_TIERRA;
