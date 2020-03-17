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
    struct StructData
    {
        double totalMass = 1;
        MathUtils::Vector shape = MathUtils::Vector{1.f, 1.f};
        MathUtils::Vector position = MathUtils::Vector{0.f, 0.f};
    };

    class StructureElement
    {
    public:
        // Structure building utils
        void fix(Particle* particle)
        {
            fixedParticles.push_back(std::move((particle)));
            particles.erase(std::remove(particles.begin(), particles.end(), particle), particles.end());
        }
        void unfix(Particle* particle)
        {
            particles.push_back(std::move((particle)));
            fixedParticles.erase(std::remove(fixedParticles.begin(), fixedParticles.end(), particle), fixedParticles.end());
        }
        void bond(Particle* p1, Particle *p2, double maxDistFactor, float k, float c)
        {
            bonds.push_back(new LimitedBond(p1, p2, 
                    MathUtils::vectorMag(MathUtils::vectorSub(p1->getPosition(), p2->getPosition())), maxDistFactor, k, c));
            // bonds.push_back(new SimpleBond(p1, p2, 
            //         MathUtils::vectorMag(MathUtils::vectorSub(p1->getPosition(), p2->getPosition())), k, c));
        }

        // Constructor/Destructor
        StructureElement() {}
        ~StructureElement() {}

        // Bond forces related functions
        void bondBreaking(int i);
        void act(hc::GraphicElements *graphics, double dt);

        // Selection related functions
        bool selectAParticle(hc::Inputs inputs, double dt);
        void fixMode();
        void unfixMode();
        void mouseDragMode(hc::Inputs inputs, double dt);

        // Very dynamic forces related functions
        void particlesCollision(GraphicElements *graphics);

        // External forces
        void applyExtForces(double dt);

        // Main update function
        void update(hc::GraphicElements *graphics, hc::Inputs inputs, double dt);

        // Global Objects (Particles and Interactions)
        std::vector<Particle*> fixedParticles;
        std::vector<Particle*> particles;
        std::vector<Bond*> bonds;

        // Global variables (particle selection related)
        bool alreadySelected = false;
        bool isSelectedFixed;
        Particle* selectedParticle;

        // PRESET STRUCTURES
        void build_RectShape_XGrid(const double density, const int particles_y, const int particles_x, const double y_spacing, const double x_spacing, double collisionRadius);
        void build_Fluid(double density, int particles_y, int particles_x, double collisionRadius);
        void build_Box();
    };

    // RectShape_XGrid      (mass, shape, pos)
    // RectShape_RectGrid   ()
    // RectShape_TriGrid    ()
    // RectShape_HexGrid    ()
    // TriShape_TriGrid     ()
    // HexShape_HexGrid     ()
    // HexShape_RectGrid    ()
    // HexShape_TriGrid     ()

}
