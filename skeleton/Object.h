#pragma once
class Object
{
protected:
	bool alive = true;

public:
	Object();
	virtual ~Object();

	virtual bool update(double t) = 0;

	bool getAlive() const { return alive; }
};

