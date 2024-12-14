#pragma once
#include "Object.h"
#include "../RenderUtils.hpp"
#include <string>
#include <PxPhysicsAPI.h> 
#include <functional>
#include "../Global.h"

class Scene;

class GameObject : public Object
{
protected:
	// gestion de particulas
	Scene* scene;
	string name;

	// propiedades fisicas de los objetos
	RenderItem* renderItem;
	PxShape* shape;
	Vector4 color;
	physx::PxTransform* pose;
	Vector3 size = { 3,3,3 };
	float mass = 1;
	Vector3 velocity = { 0,0,0 };

	// propiedades de vida por tiempo de la particula
	float lifeTime = 0;
	float startlifeTime = 10;
public:
	GameObject(string nam, Scene* scn) :name(nam), scene(scn), Object() {};
	virtual ~GameObject() { DeregisterRenderItem(renderItem); };

	virtual bool update(double t) override;

	// cambiar la visibilidad del objeto
	virtual void setVisibility(bool visibility) {
		visibility ?
			RegisterRenderItem(renderItem) :
			DeregisterRenderItem(renderItem);
	};

	//getters
#pragma region Getters
	virtual Vector3 getPosition() { return pose->p; };
	virtual PxQuat getRotation() { return pose->q; };
	Vector3 getSize() { return size; };
	string getName() { return name; };
	virtual float getMass() { return mass; };
	Vector3 getVelocity() { return velocity; };
#pragma endregion

	// setters
#pragma region Setters
	virtual void setPosition(Vector3 pos) { pose->p = pos; };
	virtual void setRotation(const PxQuat rot) { pose->q = rot; renderItem->transform = pose; };
	virtual void setShape(PxShape* shp, Vector3 siz);
	void setName(string nam) { name = nam; };
	void setColor(Vector4 col) { renderItem->color = col; color = col; };
	void setSize(Vector3 siz) noexcept { size = siz; };
	void setMass(float mas) noexcept { mass = mas; };
	void setVelocity(Vector3 vel) noexcept { velocity = vel; }
	void setStartLifeTime(float life) { startlifeTime = life; }
#pragma endregion

	//gestion de fuerzas
protected:
public:
	// Aniade fuerza
	virtual void addForce(float x, float y, float z) {}
	// Aniade fuerza
	virtual void addForce(Vector3 fc) {}


	// gestion de colisiones (llamado a callbacks)
protected:
	using ColCallback = std::function<void()>;
	vector<ColCallback> callbacks;
public:
	// aniade callback a la lista
	void addCallback(const ColCallback& cb) { callbacks.push_back(cb); }
	// ejecuta los callbacks del objeto
	virtual void onCollision(GameObject* other) { for (auto c : callbacks) c(); };
};

