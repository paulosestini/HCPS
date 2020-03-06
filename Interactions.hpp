#ifndef INTERACTIONS_H
#define INTERACTIONS_H

#include "Particle.hpp"
#include "GraphicElements.hpp"

#include <iostream>

namespace StructSim
{
    // Defines any general bi-polar interaction
    class Bond
    {
    public:
        // Constructor/Destructor
        Bond() {}
        ~Bond() {}

        // Acessors
        Particle *GetParticle1Ptr() {return p1;}
        Particle *GetParticle2Ptr() {return p2;}

        // Functions
        virtual void Act(MyGraphics::GraphicElements *graphics, float dt) {} // Applies the forces

        // Objects (2 bonded objects)
        Particle *p1;
        Particle *p2;
    };

    // Defines an ideal spring like bi-polar interaction
    class SimpleBond : public Bond
    {
    public:
        // Constructor/Destructor
        SimpleBond(Particle* part1, Particle* part2, float equilibriumDistance)
        : Bond(), p1( part1 ) , p2( part2 ), eqDist( equilibriumDistance ) {}
        ~SimpleBond() {}

        // Acessors
        Particle *GetParticle1Ref();
        Particle *GetParticle2Ref();

        // Functions
        void Act(MyGraphics::GraphicElements *graphics, float dt); // Applies the forces

        // Objects (2 bonded objects)
        Particle* p1;
        Particle* p2;

    private:
        // Local variables
        float eqDist;
        static constexpr float k = 10;
    };
}

#endif