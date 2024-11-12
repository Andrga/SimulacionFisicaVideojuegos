#include "System.h"

System::System(Scene* scn): scene(scn)
{
}

System::~System()
{
}

bool System::update(double t)
{
    for (auto g : generators) {
        g ->update(t);
    }

    return false;
}

void System::addGenerator(Generator* generator)
{
    generators.push_back(generator);
}
