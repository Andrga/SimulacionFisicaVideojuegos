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
Vector3 EXPLOSION_VELOCITY = {100,100,100};
float FUERZA_PROPULSOR = 300000;

float RADIO_PLANETA_TIERRA = 6378; // 6.378 km
float RADIO_GRAVEDAD_TIERRA = RADIO_PLANETA_TIERRA*4; // 1.500.000 km

float RADIO_LUNA = 1737; // 1.737 km
float RADIO_GRAVEDAD_LUNA = RADIO_LUNA*5; // 58.000 km
float DISTANCIA_TIERRA_LUNA = 19220; // 384.400 km


float RADIO_MARTE = 3396; // 3.396 km
float RADIO_GRAVEDAD_MARTE = RADIO_MARTE*5; // 1.000.000 km
float DISTANCIA_TIERRA_MARTE = 54600; // 54.600.000 km


float RADIO_VENUS = 12051; // 6.051 km
float RADIO_GRAVEDAD_VENUS = RADIO_VENUS*5; // 1.000.000 km
float DISTANCIA_TIERRA_VENUS = 85000; // 170.000.000 km
