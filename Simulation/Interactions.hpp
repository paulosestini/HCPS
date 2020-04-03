#pragma once

#include <iostream>

#include "../DEFINITIONS.hpp"
#include "Particle.hpp"

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
        void act(double dt); // Applies the forces
        static MathUtils::Vector findSpringForce(Particle *p1, Particle *p2, double eqDist, double k, double c);
        
        virtual bool isBroken() = 0;                      // Returns if bond is broken
        virtual MathUtils::Vector calculateForce() = 0;   // Calculate force bond aplplies on particles

        // Local variables
        MathUtils::Vector calculatedForce;
        Particle *p1;
        Particle *p2;
    };

    // An ideal spring like bi-polar interaction with internal energy dissipation
    class IdealBond : public Bond
    {
    public:
        // Constructor/Destructor
        IdealBond(Particle *part1, Particle *part2, double equilibriumDistance, double k, double c)
        : Bond(), eqDist(equilibriumDistance), k(k), c(c) {p1=(part1); p2=(part2);}
        ~IdealBond() {}

        // Functions
        bool isBroken();            // Returns if bond is broken (never)
        MathUtils::Vector calculateForce(); // Calculate force that bond applies on particles (F = kx + cv)

        // Local specific variables
        double eqDist;
        double k;
        double c;
    };

    // A not ideal spring like bi-polar interaction with internal energy dissipation
    class RealBond : public Bond
    {
    public:
        // Constructor/Destructor
        RealBond(Particle* part1, Particle* part2, double equilibriumDistance, double maxDistanceFactor, double k, double c)
        : Bond(), eqDist(equilibriumDistance), maxDistFactor(maxDistanceFactor), k(k), c(c) {p1=(part1); p2=(part2);}
        ~RealBond() {}

        // Functions
        bool isBroken();                    // Returns if bond is broken (if deformation is too big)
        MathUtils::Vector calculateForce(); // Calculate force that bond applies on particles (F = kx + cv)

        // Local specific variables
        double eqDist;
        double maxDistFactor;
        double k;
        double c;
    };
}
