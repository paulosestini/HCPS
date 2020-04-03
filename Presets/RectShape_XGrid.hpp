#pragma once

#include "../DEFINITIONS.hpp"
#include "../Utils/MathUtils.hpp"
#include "../Simulation/ParticleSystem.hpp"

namespace hc
{
    class RectShape_XGrid : public ParticleSystem
    {
    public:
        RectShape_XGrid() {}
        ~RectShape_XGrid() {}
        double mass                  = 1.0;
        double hardness              = 1.0;
        double steadiness            = 1.0;
        double width                 = 1.0;
        double height                = 1.0;
        double dx                    = 1.0;
        double dy                    = 1.0;
        double collisionRadius       = 0.5;
        double maxDistFactor         = 100.0;
        MathUtils::Vector initialPos = MathUtils::Vector{0.0, 0.0};

        void setScale(double scale);
        void build(int typeID);
    };

    class HardBlock : public RectShape_XGrid
    {
    public:
        HardBlock(double scale)
        {
            mass            = 5000.0        *scale*scale*scale;
            hardness        = 20000.0       /scale;
            steadiness      = 10.00           /scale;
            width           = 1.0           *scale;
            height          = 1.0           *scale;
            dx              = 0.1           *scale;
            dy              = 0.1           *scale;
            collisionRadius = dx/10.0;
            maxDistFactor   = 20.0;
            initialPos      = CENTER_TOP;
        }
        ~HardBlock() {}
    };

    class JelloBlock : public RectShape_XGrid
    {
    public:
        JelloBlock(double scale)
        {
            mass            = 1300.0        *scale*scale;
            hardness        = 8000.0        ;
            steadiness      = 1.0           *scale;
            width           = 1.0           *scale;
            height          = 1.0           *scale;
            dx              = 0.1           *scale;
            dy              = 0.1           *scale;
            collisionRadius = dx/10.0          *scale;
            maxDistFactor   = 5.0          *scale;
            initialPos      = CENTER_TOP;
        }
        ~JelloBlock() {}
    };

    class JellyfishBlock : public RectShape_XGrid
    {
    public:
        JellyfishBlock(double scale)
        {
            mass            = 1000.0        *scale*scale;
            hardness        = 7000.0        ;
            steadiness      = 0.5           *scale;
            width           = 1.0           *scale;
            height          = 1.0           *scale;
            dx              = 0.05           *scale;
            dy              = 0.05           *scale;
            collisionRadius = dx*4.0           *scale;
            maxDistFactor   = 20.0          *scale;
            initialPos      = CENTER_TOP;
        }
        ~JellyfishBlock() {}
    };
}