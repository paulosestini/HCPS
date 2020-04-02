#pragma once

#include <iostream>

#include "../DEFINITIONS.hpp"
#include "../Utils/MathUtils.hpp"
#include "../Interface/InputHandler.hpp"
#include "Particle.hpp"
#include "Interactions.hpp"
#include "Boundaries.hpp"

namespace hc
{
    class ParticleSystem
    {
    private:
        // Internal actions
        void breakBond(int i);
        void actBonds(double dt);
        void internalCollisions(double collisionK, double collisionC);
        
        // User inserted actions (particle selection)
        bool selectParticle(hc::InputHandler *inputHandler, double dt);
        void actFixMode();
        void actUnfixMode();
        void actMouseDragMode(hc::InputHandler *inputHandler, double dt);

    public:
        // Constructor/Destructor
        ParticleSystem() {}
        ~ParticleSystem() {}

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
        void bind(Particle* p1, Particle *p2, double maxDistFactor, float k, float c)
        {
            bonds.push_back(new RealBond(p1, p2,
                    MathUtils::vectorMag(MathUtils::vectorSub(p1->getPosition(), p2->getPosition())), maxDistFactor, k, c));
        }

        // Update functions
        void internalAct(double collisionK, double collisionC, double dt); // Act forces internal to the particle system (internal forces)
        void externalAct(double dt); // Act forces external to the particle system (environmental forces)
        void selectionAct(hc::InputHandler *inputHandler, double dt); // Act user-input forces
        static void interAct(ParticleSystem *str1, ParticleSystem *str2, double collisionK, double collisionC); // Interact two particle systems (inter-structure forces)
        void finalUpdate(double dt); // Update the particles

        // Global Objects (Particles and Interactions)
        std::vector<Particle*> fixedParticles;
        std::vector<Particle*> particles;
        std::vector<Bond*> bonds;

        // Global variables (particle selection related)
        bool alreadySelected = false;
        bool isSelectedFixed;
        Particle* selectedParticle;
    };
}
