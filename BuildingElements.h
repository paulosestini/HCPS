#ifndef BUILDINGELEMENTS_H
#define BUILDINGELEMENTS_H

#include "MathUtils.hpp"

class Particle
{
public:
    Vector pos;
    Vector vel;
    float mass;

    Particle(Vector pos, float mass);
    void applyForce(Vector force, float dt); // Applies force during interval dt
    void update(float dt); // Updates the particles position with timestep dt
};

class Bond
{
public:
    float equilibriumDistance;
    Particle * p1;
    Particle * p2;
    static constexpr float k = 10;

    Bond(Particle * p1, Particle * p2, float equilibriumDistance);
    void act(float dt); // Applies the forces
};


#endif