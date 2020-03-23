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
        void selectAndAct(hc::Inputs inputs, double dt);

        // Very dynamic forces related functions
        void particlesCollision(GraphicElements *graphics, double collisionK, double collisionC);

        // External forces
        void applyExtForces(double dt);

        // Main update function
        void update(hc::GraphicElements *graphics, hc::Inputs inputs, double collisionK, double collisionC, double dt);

        // Interactions between structures
        static void interactStructures(StructureElement *str1, StructureElement *str2, GraphicElements *graphics, double collisionK, double collisionC);

        // Global Objects (Particles and Interactions)
        std::vector<Particle*> fixedParticles;
        std::vector<Particle*> particles;
        std::vector<Bond*> bonds;

        // Global variables (particle selection related)
        bool alreadySelected = false;
        bool isSelectedFixed;
        Particle* selectedParticle;

        // PRESET STRUCTURES
        void build_RectShape_XGrid(const double mass, const double hardness, const double steadiness, double width, double height, double dx, double dy, const double collisionRadius, const double maxDistFactor, MathUtils::Vector initialPos);
        void build_Fluid(double density, double width, double height, double collisionRadius, MathUtils::Vector initialPos);
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
