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

        // Functions
        virtual void act(double dt) {} // Applies the forces

        // Local variables
        MathUtils::Vector calculatedForce;
        Particle* p1;
        Particle* p2;
    };

    // Defines an ideal spring like bi-polar interaction with internal energy dissipation
    class SimpleBond : public Bond
    {
    public:
        // Constructor/Destructor
        SimpleBond(Particle* part1, Particle* part2, double equilibriumDistance, double k, double c)
        : Bond(), eqDist(equilibriumDistance), k(k), c(c) {p1=(part1); p2=(part2);}
        ~SimpleBond() {}

        // Functions
        void act(double dt); // Applies the forces
        MathUtils::Vector calculateForce();

    private:
        // Local specific variables
        double eqDist;
        double k;
        double c;
    };
}
