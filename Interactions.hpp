#pragma once

#include "Particle.hpp"
#include "GraphicElements.hpp"

#include <iostream>

namespace hc
{
    // Defines any general bi-polar interaction
    class Bond
    {
    public:
        // Constructor/Destructor
        Bond() {}
        ~Bond() {}

        // Acessors
        virtual Particle *getParticle1Ptr() {}
        virtual Particle *getParticle2Ptr() {}
        virtual MathUtils::Vector getCalculatedForce() {}

        // Functions
        virtual void act(double dt) {} // Applies the forces
    };

    // Defines an ideal spring like bi-polar interaction with internal energy dissipation
    class SimpleBond : public Bond
    {
    public:
        // Constructor/Destructor
        SimpleBond(Particle* part1, Particle* part2, double equilibriumDistance, double k, double c)
        : Bond(), p1(part1), p2(part2), eqDist(equilibriumDistance), k(k), c(c) {}
        ~SimpleBond() {}

        // Acessors
        Particle *getParticle1Ptr() {return this->p1;}
        Particle *getParticle2Ptr() {return this->p2;}
        MathUtils::Vector getCalculatedForce() {return this->calculatedForce;}

        // Functions
        void act(double dt); // Applies the forces
        MathUtils::Vector calculateForce();

    private:
        // Objects (2 bonded objects)
        Particle* p1;
        Particle* p2;
        
        // Local variables
        MathUtils::Vector calculatedForce;
        double eqDist;
        double k;
        double c;
    };
}
