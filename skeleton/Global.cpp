#include "Global.h"

// construccion del cohete
GameObject* MovingObj = nullptr;
bool Moving = false;
ModuloInfo* Cohete = nullptr;

float TENSION_ENTRE_MODULOS = 100000;
float sizeModul = 10;
Vector3 tamanioCohete = { 0,0, 0 };

float SimulateTime = 1;

// CONSTANTES DE JUEGO
float FUERZA_PROPULSOR = 10000;

float RADIO_PLANETA_TIERRA = 6378; // 6.378 km
float RADIO_GRAVEDAD_TIERRA = 20000; // 20.000 km

float RADIO_LUNA = 3244; // 6.378 km
float RADIO_GRAVEDAD_LUNA = 10000; // 20.000 km
