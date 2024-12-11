#pragma once
#include "../../basics/RBStatic.h"
#include "Anchor.h"
#include "../../basics/Widget.h"

class ObjetoMovible : public RBStatic
{
protected:
	bool moviendo = false;

	Widget* baseCono = nullptr;

	TipoModulo tipo = TANQUE;

	ObjetoMovible* derecha = nullptr;
	ObjetoMovible* abajo = nullptr;
	ObjetoMovible* izquieda = nullptr;
	ObjetoMovible* arriba = nullptr;

public:
	ObjetoMovible(string nam, Scene* scn, PxPhysics* gPhysics, PxScene* gScene, TipoModulo type);
	~ObjetoMovible() {};

	bool update(double t) override;


	// ejecuta los callbacks del objeto
	void onCollision(GameObject* other) override;

	// aniade una particula a la lista de anchors que son objetos que anclan objetos movibles
	void addAnchor(ObjetoMovible* anch);

	// quita los modulos de su alrededor
	void deAtachAllAnch();

	// 0:derecha, 1:abajo, 2:izquierda, 3:arriba
	void deAtachAnch(int id);

	void setType(TipoModulo type) noexcept { tipo = type; };
	TipoModulo getType() noexcept { return tipo; };
	ObjetoMovible* getDerecha() noexcept { return derecha; }
	ObjetoMovible* getAbajo() noexcept { return abajo; }
	ObjetoMovible* getIzquierda() noexcept { return izquieda; }
	ObjetoMovible* getArriba() noexcept { return arriba; }

	ModuloInfo* generateModulo();

	void alternateMoviendo();

	void setVisibility(bool vis) override;

};

