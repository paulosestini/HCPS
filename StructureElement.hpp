#pragma once

#include <iostream>
#include <vector>

#include "DEFINITIONS.hpp"
#include "MathUtils.hpp"
#include "Particle.hpp"
#include "Interactions.hpp"
#include "GraphicElements.hpp"
#include "Boundaries.hpp"

namespace hc
{
    class StructureElement
    {
    public:
        // Structure building utils
        void fix(int particle_index)
        {
            fixedParticles.push_back(std::move(particles.at(particle_index)));
            particles.erase(particles.begin()+particle_index);
        }
        void unfix(int particle_index)
        {
            particles.push_back(std::move(fixedParticles.at(particle_index)));
            fixedParticles.erase(fixedParticles.begin()+particle_index);
        }
        void bond(Particle* p1, Particle *p2, float k, float c)
        {
            bonds.push_back(new SimpleBond(p1, p2, 
                    MathUtils::vectorMag(MathUtils::vectorSub(p1->getPosition(), p2->getPosition())), k, c));
        }

        // Constructor/Destructor
        StructureElement() {}
        ~StructureElement() {}

        // Functions
        void act(hc::GraphicElements *graphics, double dt);
        void selectParticles(hc::GraphicElements *graphics, hc::Inputs inputs, double dt);
        void fixMode();
        void unfixMode();
        void mouseDragMode(hc::GraphicElements *graphics, hc::Inputs inputs, const double timeScale);
        void notSelectedMode(hc::GraphicElements *graphics, double dt);
        void update(hc::GraphicElements *graphics, hc::Inputs inputs, const double timeScale, double dt);

        // Global Objects (Particles and Interactions)
        std::vector<Particle*> fixedParticles;
        std::vector<Particle*> particles;
        std::vector<Bond*> bonds;
        double mouseForceScale = 1;
    };

    class SimpleTower : public StructureElement
    {
    public:
        // Constructor/Destructor
        SimpleTower(const double mass, const int particles_y, const double y_spacing, const double x_spacing, double timeScale, bool fixBot, bool fixTop);
        ~SimpleTower() {}
    };

    class RectangularBody : public StructureElement
    {
    public:
        RectangularBody(const double mass, const int particles_y, const int particles_x, const double y_spacing, const double x_spacing, double timeScale);
        ~RectangularBody() {}
    };
}
