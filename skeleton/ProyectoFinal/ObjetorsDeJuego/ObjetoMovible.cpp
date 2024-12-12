#include "ObjetoMovible.h"
#include"../../basics/Scene.h"
#include <typeinfo>

ObjetoMovible::ObjetoMovible(string nam, Scene* scn, PxPhysics* gPhysics, PxScene* gScene, TipoModulo type) : RBStatic("mov" + nam, scn, gPhysics, gScene), tipo(type) {
	// aniade el callback para alternar si se esta arrastrando el modulo o no
	addCallback([this]() {this->alternateMoviendo(); });

	switch (type)
	{
	case CABINA:
		setShape(CreateShape(PxSphereGeometry(5)), { 5, 5, 5 });
		setColor({ 0.5,0.5,1,0 });
		break;
	case TANQUE:
		setShape(CreateShape(PxBoxGeometry(5, 5, 5)), { 5, 5, 5 });
		setColor({ 1,1,1,1 });
		break;
	case PROPULSOR:
		setShape(CreateShape(PxSphereGeometry(5)), { 5, 5, 5 });
		setColor({ 1,0.5,0.5,1 });
		baseCono = new Widget("widBaseCono", scene, getPosition(), CreateShape(PxBoxGeometry(5, 2.5, 5)));
		scene->addGameObject(baseCono);
		baseCono->setColor({ 1,0.5,0.5,1 });
		break;
	default:
		break;
	}
}

bool ObjetoMovible::update(double t)
{

	// si estoy arrastrando al modulo sigue a la camara
	if (moviendo) {
		setPosition({ GetCamera()->getEye().x,  GetCamera()->getEye().y, getPosition().z });
		if (baseCono) baseCono->setPosition({ GetCamera()->getEye().x,  GetCamera()->getEye().y - 2.5f, getPosition().z });
		//cout << "MOVIENDOOOO--" << endl;
	}

	return RBActor::update(t);
}

void ObjetoMovible::onCollision(GameObject* other)
{
	// los objetos que empiezen por mov son objetos movibles que no interactuan entre ellos
	if (other->getName().substr(0, 3) == "mov") {
		ObjetoMovible* otherOM = (ObjetoMovible*)other;
		// si es el que se esta moviendo entonces detecto por donde viene para attacharlo
		if (otherOM->moviendo)
			addAnchor(otherOM);
		return;
	}
	// callbacks de colisiones
	GameObject::onCollision(other);
	cout << "Colision " << getName() << " con " << other->getName() << endl;
}

void ObjetoMovible::addAnchor(ObjetoMovible* anch)
{
	Vector3 posAnch = anch->getPosition();
	Vector3 sizeAnch = anch->getSize();
	Vector3 posThis = getPosition();
	Vector3 sizeThis = getSize();

	// si esta entre los limites verticales de  este objeto:
	if (posAnch.y > posThis.y - sizeThis.y && posAnch.y < posThis.y + sizeThis.y)
	{
		// esta entrando por la izquierda
		if (posAnch.x < posThis.x - sizeThis.x) // la posicion x del otro objeto es menor que el limite izquierdo de este objeto
		{
			//cout << "IZQUIERDA" << endl;
			if (izquierda == nullptr) {
				izquierda = anch;
				anch->derecha = this;
				anch->alternateMoviendo();
				anch->setPosition(Vector3(posThis.x - sizeAnch.x - sizeThis.x - 1, posThis.y, posThis.z));
				cout << anch->getPosition().x << "/" << anch->getPosition().y << "/" << anch->getPosition().z << endl;
			}
		} // esta entrando por la derecha
		else if (posAnch.x > posThis.x + sizeThis.x) // la posicion x del otro objeto es menor que el limite derecho de este objeto
		{
			//cout << "DERECHA" << endl;
			if (derecha == nullptr) {
				derecha = anch;
				anch->izquierda = this;
				anch->alternateMoviendo();
				anch->setPosition(Vector3(posThis.x + sizeAnch.x + sizeThis.x + 1, posThis.y, posThis.z));
				cout << anch->getPosition().x << "/" << anch->getPosition().y << "/" << anch->getPosition().z << endl;
			}
		}
	}
	// si esta entre los limites horizontales de  este objeto:
	else if (posAnch.x > posThis.x - sizeThis.x && posAnch.x < posThis.x + sizeThis.x) {
		// esta entrando por abajo
		if (posAnch.y < posThis.y - sizeThis.y)// la posicion y del otro objeto es menor que el limite inferior de este objeto
		{
			cout << "ABAJO" << endl;
			if (abajo == nullptr) {
				abajo = anch;
				anch->arriba = this;
				anch->alternateMoviendo();
				anch->setPosition(Vector3(posThis.x, posThis.y - sizeAnch.y - sizeThis.y - 1, posThis.z));
				cout << anch->getPosition().x << "/" << anch->getPosition().y << "/" << anch->getPosition().z << endl;
			}
		} // esta entrando por arriba
		else if (posAnch.y > posThis.y + sizeThis.y)// la posicion y del otro objeto es menor que el limite inferior de este objeto
		{
			cout << "ARRIBA" << endl;
			if (arriba == nullptr) {
				arriba = anch;
				anch->abajo = this;
				anch->alternateMoviendo();
				anch->setPosition(Vector3(posThis.x, posThis.y + sizeAnch.y + sizeThis.y + 1, posThis.z));
				cout << anch->getPosition().x << "/" << anch->getPosition().y << "/" << anch->getPosition().z << endl;
			}
		}
	}

	if (baseCono) baseCono->setPosition({ getPosition().x,  getPosition().y - 2.5f, getPosition().z });
	// si no no hace nada
}

void ObjetoMovible::deAtachAllAnch()
{
	if (derecha) derecha->deAtachAnch(2);
	if (abajo) abajo->deAtachAnch(3);
	if (izquierda) izquierda->deAtachAnch(0);
	if (arriba) arriba->deAtachAnch(1);

	derecha = nullptr;
	abajo = nullptr;
	izquierda = nullptr;
	arriba = nullptr;
}

void ObjetoMovible::deAtachAnch(int id)
{
	switch (id)
	{
	case 0: derecha = nullptr; break;
	case 1: abajo = nullptr; break;
	case 2: izquierda = nullptr; break;
	case 3: arriba = nullptr; break;
	default:
		cout << "Estas intentando desatachar fuera del los lados del modulo" << endl;
		break;
	}
}

ModuloInfo* ObjetoMovible::generateModulo()
{
	ModuloInfo* base = new ModuloInfo();

	// Asignamos el tipo de módulo
	base->tipo = this->tipo;
	tamanioCohete.x += sizeModul;
	tamanioCohete.y += sizeModul;

	// Relacionamos los modulos adyacentes, usando las propiedades de izquierda, derecha, arriba y abajo
	if (this->derecha != nullptr) {
		this->derecha->izquierda = nullptr; // eliminamos la referencia izquierda del modulo derecho (this)
		ModuloInfo* modDer = generateModulo(this->derecha, base);
		base->derecha = modDer; // asignamos el modulostruct al modulo base
		tamanioCohete.y += sizeModul; // Actualizacion tamanio cohete
	}
	if (this->abajo != nullptr) {
		this->abajo->arriba = nullptr; // eliminamos la referencia izquierda del modulo derecho (this)
		ModuloInfo* modAbaj = generateModulo(this->abajo, base);
		base->abajo = modAbaj; // asignamos el modulostruct al modulo base
		tamanioCohete.y += sizeModul; // Actualizacion tamanio cohete
	}
	if (this->izquierda != nullptr) {
		this->izquierda->derecha = nullptr; // eliminamos la referencia izquierda del modulo derecho (this)
		ModuloInfo* modIzq = generateModulo(this->izquierda, base);
		base->izquierda = modIzq; // asignamos el modulostruct al modulo base
		tamanioCohete.y += sizeModul; // Actualizacion tamanio cohete
	}
	if (this->arriba != nullptr) {
		this->arriba->abajo = nullptr; // eliminamos la referencia izquierda del modulo derecho (this)
		ModuloInfo* modArr = generateModulo(this->arriba, base);
		base->arriba = modArr; // asignamos el modulostruct al modulo base
		tamanioCohete.y += sizeModul; // Actualizacion tamanio cohete
	}

	return base;
}

ModuloInfo* ObjetoMovible::generateModulo(ObjetoMovible* nuevomodOBJ, ModuloInfo* nuevomodInfo)
{
	if (nuevomodOBJ == nullptr) return nullptr;

	ModuloInfo* base = new ModuloInfo();
	// Asignamos el tipo de modulo
	base->tipo = nuevomodOBJ->tipo;


	// Relacionamos los modulos adyacentes, usando las propiedades de izquierda, derecha, arriba y abajo
	if (nuevomodOBJ->derecha != nullptr) {
		nuevomodOBJ->derecha->izquierda = nullptr; // eliminamos la referencia izquierda del modulo derecho (this)
		ModuloInfo* modDer = generateModulo(nuevomodOBJ->derecha, base);
		base->derecha = modDer; // asignamos el modulostruct al modulo base
		tamanioCohete.y += sizeModul; // Actualizacion tamanio cohete
	}
	if (nuevomodOBJ->abajo != nullptr) {
		nuevomodOBJ->abajo->arriba = nullptr; // eliminamos la referencia izquierda del modulo derecho (this)
		ModuloInfo* modAbaj = generateModulo(nuevomodOBJ->abajo, base);
		base->abajo = modAbaj; // asignamos el modulostruct al modulo base
		tamanioCohete.y += sizeModul; // Actualizacion tamanio cohete
	}
	if (nuevomodOBJ->izquierda != nullptr) {
		nuevomodOBJ->izquierda->derecha = nullptr; // eliminamos la referencia izquierda del modulo derecho (this)
		ModuloInfo* modIzq = generateModulo(nuevomodOBJ->izquierda, base);
		base->izquierda = modIzq; // asignamos el modulostruct al modulo base
		tamanioCohete.y += sizeModul; // Actualizacion tamanio cohete
	}
	if (nuevomodOBJ->arriba != nullptr) {
		nuevomodOBJ->arriba->abajo = nullptr; // eliminamos la referencia izquierda del modulo derecho (this)
		ModuloInfo* modArr = generateModulo(nuevomodOBJ->arriba, base);
		base->arriba = modArr; // asignamos el modulostruct al modulo base
		tamanioCohete.y += sizeModul; // Actualizacion tamanio cohete
	}

	return base;
}

void ObjetoMovible::alternateMoviendo() {

	moviendo = !moviendo;

	// si estas moviendo a este objeto, y quieres dejar de moverlo:
	if (MovingObj == this && !moviendo) { MovingObj = nullptr, Moving = false; }
	// si no estas moviendo ningun objeto y quieres mover este objeto:
	else if (MovingObj == nullptr && moviendo) { MovingObj = this; Moving = true; }
	// si estoy moviendo otro objeto y quiero mover este:
	else if (MovingObj != this && moviendo) { moviendo = false; return; }




	//cout << (moviendo ? "MOVIENDO EL OBJETO " : "NO MOVIENDO: ") << getName() << endl;

	if (moviendo)
	{
		deAtachAllAnch();
		setPosition({ getPosition().x, getPosition().y, getPosition().z + 10 });
		if (baseCono) baseCono->setPosition({ GetCamera()->getEye().x,  GetCamera()->getEye().y - 2.5f, getPosition().z });
	}
	else
	{
		setPosition({ getPosition().x, getPosition().y, getPosition().z - 10 });

		if (baseCono) baseCono->setPosition({ GetCamera()->getEye().x,  GetCamera()->getEye().y - 2.5f, getPosition().z });
	}
	cout << moviendo << endl;

}

void ObjetoMovible::setVisibility(bool vis)
{
	RBStatic::setVisibility(vis);

}
