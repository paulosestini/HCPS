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
        void act(double dt) // Applies the forces
        {
            MathUtils::Vector force = calculateForce();

            p2->applyForce(force);
            p1->applyForce(MathUtils::vectorScale(force, -1));
        }
        virtual bool isBroken() {}                      // Returns if bond is broken
        virtual MathUtils::Vector calculateForce() {}   // Calculate force bond aplplies on particles

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
        bool isBroken();                    // Returns if bond is broken (never)
        MathUtils::Vector calculateForce(); // Calculate force bond aplplies on particles (F = kx + cv)

    private:
        // Local specific variables
        double eqDist;
        double k;
        double c;
    };

    // Defines an ideal spring like bi-polar interaction with internal energy dissipation
    class LimitedBond : public Bond
    {
    public:
        // Constructor/Destructor
        LimitedBond(Particle* part1, Particle* part2, double equilibriumDistance, double maxDistanceFactor, double k, double c)
        : Bond(), eqDist(equilibriumDistance), maxDistFactor(maxDistanceFactor), k(k), c(c) {p1=(part1); p2=(part2);}
        ~LimitedBond() {}

        // Functions
        bool isBroken();                    // Returns if bond is broken (too far apart particles)
        MathUtils::Vector calculateForce(); // Calculate force bond aplplies on particles (F = kx + cv)

    private:
        // Local specific variables
        double maxDistFactor;
        double eqDist;
        double k;
        double c;
    };
}
