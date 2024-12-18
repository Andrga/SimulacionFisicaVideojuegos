#include "Global.h"

// construccion del cohete
GameObject* MovingObj = nullptr;
bool Moving = false;
ModuloInfo* CoheteInfo = nullptr;

float TENSION_ENTRE_MODULOS = 10000;
float sizeModule = 10;
Vector3 tamanioCohete = { 0,0, 0 };

float SimulateTime = 1;

Vector3 POS_INI_CABINA_LAUNCH = { 0,0,0 };

ModuloInfo cohetePrefab(CABINA, new ModuloInfo(PROPULSOR), new ModuloInfo(TANQUE, nullptr, new ModuloInfo(PROPULSOR), nullptr, nullptr), new ModuloInfo(PROPULSOR), nullptr);
Vector3 tamanioCohetePrefab = { sizeModule,3 * sizeModule,0 };

// CONSTANTES DE JUEGO
float FUERZA_PROPULSOR = 300000;

float RADIO_PLANETA_TIERRA = 6378; // 6.378 km
float RADIO_GRAVEDAD_TIERRA = 20000; // 20.000 km

float RADIO_LUNA = 3244; // 6.378 km
float RADIO_GRAVEDAD_LUNA = 10000; // 20.000 km
