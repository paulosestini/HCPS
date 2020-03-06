#ifndef STRUCTUREELEMENT_H
#define STRUCTUREELEMENT_H

#include <iostream>
#include <vector>

#include "MathUtils.hpp"
#include "Particle.hpp"
#include "Interactions.hpp"
#include "GraphicElements.hpp"

namespace StructSim
{
    class StructureElement
    {
    public:
        // Constructor/Destructor
        StructureElement() {}
        ~StructureElement() {}

        // Functions
        virtual void Act(MyGraphics::GraphicElements *graphics, float dt) {}
        virtual void Update(MyGraphics::GraphicElements *graphics, float dt) {}
    };

    class SimpleTower : public StructureElement
    {
    public:
        // Constructor/Destructor
        SimpleTower(int particles_y, float y_spacing);
        ~SimpleTower() {}

        // Functions
        void Act(MyGraphics::GraphicElements *graphics, float dt);
        void Update(MyGraphics::GraphicElements *graphics, float dt);

        // Global Objects (Particles and Interactions)
        std::vector<Particle*> fixedParticles;
        std::vector<Particle*> particles;
        std::vector<Bond*> bonds;
    };
}

#endif