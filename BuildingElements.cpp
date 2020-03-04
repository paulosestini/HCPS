#include "BuildingElements.h"
/* ---class "Particle" definitions--- */

Particle::Particle(Vector pos, float mass)
{
    this->pos = pos;
    this->mass = mass;
}

void Particle::applyForce(Vector force, float dt)
{   
    // Changes velocity according to the force applied
    Vector acc = vectorScale(force, mass);
    vel = vectorAdd(vel, vectorScale(acc, dt));
}

void Particle::update(float dt)
{   
    // Some dissipation of energy
    vel = vectorAdd(vel, vectorScale(vectorScale(vel, vectorMag(vel)), -0.9));
    
    // Updating position
    pos = vectorAdd(pos, vectorScale(vel, dt));

}

/* ---class "Bond" definitions--- */

Bond::Bond(Particle * p1, Particle * p2, float equilibriumDistance)
    : p1(p1), p2(p2)   
{
    this->equilibriumDistance = equilibriumDistance;
}

void Bond::act(float dt)
{   
    /* Applies the force F = k*(r-r_equilbrium)
     * where r is the vector connecting particle p2 to p1 
     * and r_equilibrium is the vector giving the point
     * of equilibrium of the spring
     */
    Vector r = vectorSub(p1->pos, p2->pos);

    float r_mag = vectorMag(r);
    Vector r_hat = normalize(r);
    Vector equilibrium_r = vectorScale(r_hat, equilibriumDistance);
    
    Vector force = vectorScale(vectorSub(r, equilibrium_r), k);

    p2->applyForce(force, dt);
    p1->applyForce(vectorScale(force, -1), dt);
}

