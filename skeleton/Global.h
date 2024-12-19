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
extern Vector3 EXPLOSION_VELOCITY;

//	para la construccion del cohete
// tipos de modulos que puede contener el cohete
enum TipoModulo {
	CABINA, TANQUE, PROPULSOR
};

// informacion que contiene cada modulo
struct ModuloInfo
{
	TipoModulo tipo;
	ModuloInfo* derecha = nullptr;
	ModuloInfo* abajo = nullptr;
	ModuloInfo* izquierda = nullptr;
	ModuloInfo* arriba = nullptr;

	ModuloInfo() {};
	ModuloInfo(TipoModulo tp) :tipo(tp) { derecha = nullptr; izquierda = nullptr; arriba = nullptr; abajo = nullptr; };
	ModuloInfo(TipoModulo tp, ModuloInfo* der, ModuloInfo* abj, ModuloInfo* izq, ModuloInfo* arr) :tipo(tp), derecha(der), abajo(abj), izquierda(izq), arriba(arr) {};
};

// vector que indica los modulos del cohete
extern ModuloInfo* CoheteInfo;

extern float TENSION_ENTRE_MODULOS;
extern float sizeModule;
extern Vector3 tamanioCohete;

extern float SimulateTime;

extern Vector3 POS_INI_CABINA_LAUNCH;

extern ModuloInfo cohetePrefab;
extern Vector3 tamanioCohetePrefab;

// constantes juego
extern float FUERZA_PROPULSOR;

extern float RADIO_PLANETA_TIERRA;
extern float RADIO_GRAVEDAD_TIERRA;

extern float RADIO_LUNA;
extern float RADIO_GRAVEDAD_LUNA;
extern float DISTANCIA_TIERRA_LUNA;


extern float RADIO_MARTE;
extern float RADIO_GRAVEDAD_MARTE;
extern float DISTANCIA_TIERRA_MARTE;


extern float RADIO_VENUS;
extern float RADIO_GRAVEDAD_VENUS;
extern float DISTANCIA_TIERRA_VENUS;
