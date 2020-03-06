#ifndef PARTICLE_H
#define PARTICLE_H

#include "MathUtils.hpp"
#include "GraphicElements.hpp"

namespace StructSim
{
    class Particle
    {
    public:
        // Constructor/Destructor
        Particle(MyMath::Vector initPos, MyMath::Vector initVel, float initMass);
        ~Particle() {}

        //Accesors
        MyMath::Vector GetPosition();
        void SetPosition(MyMath::Vector newPos);
        void Move(MyMath::Vector dPos);
        MyMath::Vector GetVelocity();
        void SetVelocity(MyMath::Vector newVel);
        void Accelerate(MyMath::Vector dVel);

        //Functions
        void ApplyForce(MyMath::Vector force, float dt); // Applies force during interval dt
        void Update(MyGraphics::GraphicElements *graphics, float dt); // Updates the particles position with timestep dt

    private:
        // Local variables
        struct ParticleData
        {
            MyMath::Vector pos;
            MyMath::Vector vel;
            float mass;
        };
        ParticleData data;
    };
}

#endif