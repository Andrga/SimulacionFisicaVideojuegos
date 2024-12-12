#include "Global.h"

// construccion del cohete
GameObject* MovingObj = nullptr;
bool Moving = false;
ModuloInfo* Cohete = nullptr;

float sizeModul = 11;
Vector3 tamanioCohete = { 0,0, 0 };

// CONSTANTES DE JUEGO
float FUERZA_PROPULSOR = 500;

float RADIO_PLANETA_TIERRA = 600; // 6.378 km
float RADIO_GRAVEDAD_TIERRA = 2000; // 20.000 km
