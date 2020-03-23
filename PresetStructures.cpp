#include "StructureElement.hpp"

namespace hc
{
    void StructureElement::build_RectShape_XGrid(const double mass, const double hardness, const double steadiness, double width, double height, double dx, double dy, const double collisionRadius, const double maxDistFactor, MathUtils::Vector initialPos)
    {
        int particles_x = (int)(width/dx);
        int particles_y = (int)(height/dy);
        double k = hardness*mass;
        double c = steadiness*mass;

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
                bond(particles[particles_x*i+j], particles[particles_x*i+j+1], maxDistFactor, k, c);
            }
        }
        for(int i = 0; i < particles_y-1; i++){
            for(int j = 0; j < particles_x; j++){
                bond(particles[particles_x*i+j], particles[particles_x*(i+1)+j], maxDistFactor, k, c);
            }
        }
        for(int i = 0; i < particles_y-1; i++){
            for(int j = 0; j < particles_x-1; j++){
                bond(particles[particles_x*i+j], particles[particles_x*(i+1)+j+1], maxDistFactor, k, c);
            }
        }
        for(int i = particles_y-1; i > 0; i--){
            for(int j = 0; j < particles_x-1; j++){
                bond(particles[particles_x*i+j], particles[particles_x*(i-1)+j+1], maxDistFactor, k, c);
            }
        }
    }

    void StructureElement::build_Fluid(double density, double width, double height, double collisionRadius, MathUtils::Vector initialPos)
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

    void StructureElement::build_Box()
    {
        
    }
}