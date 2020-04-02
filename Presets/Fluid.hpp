#pragma once

#include "../DEFINITIONS.hpp"
#include "../Utils/MathUtils.hpp"
#include "../Simulation/ParticleSystem.hpp"

namespace hc
{
    class Fluid : public ParticleSystem
    {
    public:
        Fluid() {}
        ~Fluid() {}
        double density               = 1.0;
        double width                 = 1.0;
        double height                = 1.0;
        double collisionRadius       = 0.5;
        double damping               = 1.0;
        double viscosity             = 1.0;
        MathUtils::Vector initialPos = MathUtils::Vector{0.0, 0.0};

        void build(int typeID);
    };

    class Water : public Fluid
    {
    public:
        Water()
        {
            density         = 1000.0;
            width           = BOUND_BOX_WIDTH;
            height          = 1.0;
            collisionRadius = 10.0*NODE_SHAPE_RADIUS/SPATIAL_SCALE;
            initialPos      = CENTER_BOT;
            damping         = 4e-6*collisionRadius*collisionRadius*2*2;
            viscosity       = 1e-4;
        }
        ~Water() {}
    };

    class Oil : public Fluid
    {
    public:
        Oil()
        {
            density         = 900.0;
            width           = BOUND_BOX_WIDTH;
            height          = 1.0;
            collisionRadius = 10.0*NODE_SHAPE_RADIUS/SPATIAL_SCALE;
            initialPos      = CENTER_BOT;
            damping         = 4e-6*collisionRadius*collisionRadius*2*2;
            viscosity       = 1e-1;
        }
        ~Oil() {}
    };

    class Goo : public Fluid
    {
    public:
        Goo()
        {
            density         = 1500.0;
            width           = BOUND_BOX_WIDTH;
            height          = 1.0;
            collisionRadius = 10.0*NODE_SHAPE_RADIUS/SPATIAL_SCALE;
            initialPos      = CENTER_BOT;
            damping         = 1e-4*collisionRadius*collisionRadius*2*2;
            viscosity       = 1e3;
        }
        ~Goo() {}
    };
}