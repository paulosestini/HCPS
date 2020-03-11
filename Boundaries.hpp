#pragma once

#include "Particle.hpp"

namespace hc
{
    static bool isColliding(Particle* particle) // Boundarie delimitation function
    {
        if (particle->getPosition().y >= 6 && particle->getVelocity().y > 0)
            return true;
        return false;
    }

    static bool collideWithBounds(Particle* particle)
    {
        if (isColliding(particle))
        {
            if (particle->getVelocity().y>0)
            {
                particle->accelerate(MathUtils::Vector{0, -particle->getVelocity().y});
                particle->setPosition(MathUtils::Vector{particle->getPosition().x, 6});
            }
            particle->accelerate(MathUtils::Vector{-0.01*particle->getVelocity().x,0});
            return true;
        }
        return false;
    }
}