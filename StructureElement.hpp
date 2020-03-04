#pragma once

#include <iostream>
#include <vector>

#include "MathUtils.hpp"

namespace StructSim
{
    class StructureElement
    {
    public:
        StructureElement() {}

        class Particle
        {
        public:
            Particle(MyMath::Vector initPos, MyMath::Vector initVel, float initMass);
            ~Particle() {}

            struct ParticleData
            {
                MyMath::Vector pos;
                MyMath::Vector vel;
                float mass;
            };

            //Accesors
            MyMath::Vector GetPosition();
            void SetPosition(MyMath::Vector newPos);
            void Move(MyMath::Vector dPos);
            MyMath::Vector GetVelocity();
            void SetVelocity(MyMath::Vector newVel);
            void Accelerate(MyMath::Vector dVel);

            //Functions
            void ApplyForce(MyMath::Vector force, float dt); // Applies force during interval dt
            void Update(float dt); // Updates the particles position with timestep dt

        private:
            ParticleData _data;
        };

        class Bond
        {
        public:
            Bond() {}
            ~Bond() {}

            virtual Particle *GetParticle1Ref() {}
            virtual Particle *GetParticle2Ref() {}

            virtual void Act(float dt) {} // Applies the forces
        };

        std::vector<Particle*> particles;
        std::vector<Particle*> fixedParticles;
        std::vector<Bond*> bonds;
    };
}