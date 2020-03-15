#pragma once

#include "DEFINITIONS.hpp"
#include "MathUtils.hpp"
#include "GraphicElements.hpp"
#include "Particle.hpp"

namespace hc
{
    // If crossed a boundary, returns the vector representing the "way out of it". If not, return {0, 0}
    static MathUtils::Vector getBoundOverstep(MathUtils::Vector pos)
    {   
        if (pos.y > (BOUND_BOX_POS_HEIGHT + BOUND_BOX_POS_POS_Y) / SPATIAL_SCALE)
        {
            return MathUtils::Vector {0, (BOUND_BOX_POS_HEIGHT + BOUND_BOX_POS_POS_Y) / SPATIAL_SCALE - pos.y};
        }
        else if (pos.x < BOUND_BOX_POS_POS_X / SPATIAL_SCALE)
        {
            return MathUtils::Vector {BOUND_BOX_POS_POS_X / SPATIAL_SCALE - pos.x, 0};
        }
        else if (pos.x > (BOUND_BOX_POS_POS_X + BOUND_BOX_POS_WIDTH) / SPATIAL_SCALE)
        {
            return MathUtils::Vector {(BOUND_BOX_POS_POS_X + BOUND_BOX_POS_WIDTH) / SPATIAL_SCALE - pos.x, 0};
        }
        return MathUtils::Vector{0, 0};
    }

    static bool stayInBoxBound(Particle* particle)
    {
        MathUtils::Vector boundOverstep = getBoundOverstep(particle->getPosition());
        if (boundOverstep.x != 0 || boundOverstep.y != 0)
        {
            // Wall collision
            particle->accelerate(MathUtils::vectorScale(MathUtils::vectorProj(particle->getVelocity(), boundOverstep),-1));
            particle->move(boundOverstep);
            // Friction
            particle->accelerate(MathUtils::vectorScale(particle->getVelocity(), -0.02));

            return true;
        }
        return false;
    }
}