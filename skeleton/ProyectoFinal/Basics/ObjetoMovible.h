#pragma once
#include "../../basics/RBStatic.h"

class ObjetoMovible : public RBStatic
{
	bool moviendo = false;
public:
	ObjetoMovible(string nam, Scene* scn, PxPhysics* gPhysics);
	~ObjetoMovible() {};

	bool update(double t) override;

	void alternateMoviendo();

};

