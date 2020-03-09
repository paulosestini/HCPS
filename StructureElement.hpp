#pragma once

#include <iostream>
#include <vector>

#include "MathUtils.hpp"
#include "Particle.hpp"
#include "Interactions.hpp"
#include "GraphicElements.hpp"

namespace hc
{
    class StructureElement
    {
    public:
        // Constructor/Destructor
        StructureElement() {}
        ~StructureElement() {}

        // Functions
        virtual void act(hc::GraphicElements *graphics, double dt) {}
        virtual void update(hc::GraphicElements *graphics, double dt) {}

        // Global Objects (Particles and Interactions)
        std::vector<Particle*> fixedParticles;
        std::vector<Particle*> particles;
        std::vector<Bond*> bonds;
    };

    class SimpleTower : public StructureElement
    {
    public:
        // Structure setting utils
        void fix(int particle_index)
        {
            fixedParticles.push_back(std::move(particles.at(particle_index)));
            particles.erase(particles.begin()+particle_index);
        }

        // Constructor/Destructor
        SimpleTower(const int particles_y, const double y_spacing, const double x_spacing, double timeScale, bool fixBot, bool fixTop);
        ~SimpleTower() {}

        // Functions
        void act(hc::GraphicElements *graphics, double dt);
        void update(hc::GraphicElements *graphics, double dt);

        // Global Objects (Particles and Interactions)
        std::vector<Particle*> fixedParticles;
        std::vector<Particle*> particles;
        std::vector<Bond*> bonds;
    };
}
