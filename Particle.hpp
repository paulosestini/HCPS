#pragma once

#include "MathUtils.hpp"
#include "GraphicElements.hpp"

namespace hc
{
    class Particle
    {
    public:
        // Constructor/Destructor
        Particle(MathUtils::Vector initPos, MathUtils::Vector initVel, double initMass, double initRad);
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

        double getMass();

        double getRadius();

        //Functions
        void update(double dt); // Updates the particles position with timestep dt

    private:
        // Local variables
        MathUtils::Vector pos;
        MathUtils::Vector vel;
        MathUtils::Vector acc;
        double mass;
        double rad;
    };
}
