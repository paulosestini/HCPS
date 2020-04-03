#include "RectShape_XGrid.hpp"

namespace hc
{
    void RectShape_XGrid::build()
    {
        int particles_x = (int)(width/dx);
        int particles_y = (int)(height/dy);
        mass = mass;
        double k = hardness*mass*dx;
        double c = steadiness*mass*dx;

        // Sets the free particles and their initial pos, vel, mass and collision radius
        for(int i = 0; i < particles_x; i++)
        {
            for(int j = 0; j < particles_y; j++)
            {
                particles.push_back(new Particle(MathUtils::Vector{initialPos.x+i*dx, initialPos.y+j*dy}, MathUtils::Vector{0.f, 0.f}, mass/particles_x/particles_y, collisionRadius));
            }
        }
        
        // Sets the bonds between the free particles as an X type grid
        for(int i = 0; i < particles_y; i++){
            for(int j = 0; j < particles_x-1; j++){
                bind(particles[particles_x*i+j], particles[particles_x*i+j+1], maxDistFactor, k, c);
            }
        }
        for(int i = 0; i < particles_y-1; i++){
            for(int j = 0; j < particles_x; j++){
                bind(particles[particles_x*i+j], particles[particles_x*(i+1)+j], maxDistFactor, k, c);
            }
        }
        for(int i = 0; i < particles_y-1; i++){
            for(int j = 0; j < particles_x-1; j++){
                bind(particles[particles_x*i+j], particles[particles_x*(i+1)+j+1], maxDistFactor, k, c);
            }
        }
        for(int i = particles_y-1; i > 0; i--){
            for(int j = 0; j < particles_x-1; j++){
                bind(particles[particles_x*i+j], particles[particles_x*(i-1)+j+1], maxDistFactor, k, c);
            }
        }
    }
}