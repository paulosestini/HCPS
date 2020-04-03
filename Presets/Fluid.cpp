#include "Fluid.hpp"

namespace hc
{
    void Fluid::build()
    {
        int particles_x = (int)(width/collisionRadius/2)+1;
        int particles_y = (int)(height/collisionRadius/2);
        double mass = density * particles_x*collisionRadius*2 * particles_y*collisionRadius*2;

        // Sets the free particles and their initial pos, vel, mass and collision radius
        for(int i = 0; i < particles_x; i++)
        {
            for(int j = 0; j < particles_y; j++)
            {
                particles.push_back(new Particle(MathUtils::Vector{initialPos.x+i*2*collisionRadius, initialPos.y+j*2*collisionRadius}, MathUtils::Vector{0.f, 0.f}, mass/particles_x/particles_y, collisionRadius));
            }
        }
    }
}