#pragma once

#include "MathUtils.hpp"
#include "GraphicElements.hpp"

namespace hc
{
    class Particle
    {
    public:
        // Constructor/Destructor
        Particle(MathUtils::Vector initPos, MathUtils::Vector initVel, double initMass);
        ~Particle() {}

        //Accesors
        MathUtils::Vector getPosition();
        void setPosition(MathUtils::Vector newPos);
        void move(MathUtils::Vector dPos);

        MathUtils::Vector getVelocity();
        void setVelocity(MathUtils::Vector newVel);
        void accelerate(MathUtils::Vector dVel);

        MathUtils::Vector getAcceleration();
        void setAcceleration(MathUtils::Vector newAcc);
        void applyForce(MathUtils::Vector force);

        //Functions
        void update(double dt); // Updates the particles position with timestep dt

        // Global variables
        bool isSelected = false;

    private:
        // Local variables
        MathUtils::Vector pos;
        MathUtils::Vector vel;
        MathUtils::Vector acc;
        double mass;
    };
}
