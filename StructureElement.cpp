#include "StructureElement.hpp"

namespace hc
{
    // Functions
    void SimpleTower::act(hc::GraphicElements *graphics, double dt) //OBSERVACAO: QUERIA DEFINIR ESSA FUNCAO NA CLASSE BOND, MAS O PROGRAMO BUGAVA
    {
        for(auto bond: bonds)
        {
            bond->act(dt);
            graphics->drawBond(bond->getCalculatedForce(), bond->getParticle1Ptr()->getPosition(), bond->getParticle2Ptr()->getPosition());
        }
    }

    void SimpleTower::update(hc::GraphicElements *graphics, double dt) //OBSERVACAO: QUERIA DEFINIR ESSA FUNCAO NA CLASSE BOND, MAS O PROGRAMO BUGAVA
    {
        for(auto particle: particles)
        {   
            particle->update(dt);
            if (particle->isSelected)
                graphics->drawSelectedNode(particle->getPosition());
            else
                graphics->drawFreeNode(particle->getPosition());
        }
        for(auto particle: fixedParticles)
        {   
            graphics->drawFixedNode(particle->getPosition());
        }
    }

    SimpleTower::SimpleTower(const int particles_y, const double y_spacing, const double x_spacing, double timeScale, bool fixBot, bool fixTop) : StructureElement()
    {
        // Sets the free particles
        float mass = 20.f/particles_y;
        for(int i = 0; i < particles_y; i++)
        {
            particles.push_back(new Particle(MathUtils::Vector{-x_spacing/2.f, 6.f-(i+1)*y_spacing}, MathUtils::Vector{0.f, 0.f}, mass));
            particles.push_back(new Particle(MathUtils::Vector{+x_spacing/2.f, 6.f-(i+1)*y_spacing}, MathUtils::Vector{0.f, 0.f}, mass));
        }
    
        // Sets the bonds between the free particles as an X type grid
        float k=100000*timeScale*timeScale, c=100*timeScale;
        for(int i = 0; i < particles_y; i += 1)
        {   
            bonds.push_back(new SimpleBond(particles[2*i], particles[2*i+1], 
                            vectorMag(vectorSub(particles[2*i]->getPosition(), particles[2*i+1]->getPosition())), k, c));
            if(i != particles_y-1)
            {
                bonds.push_back(new SimpleBond(particles[2*i], particles[2*i+2],
                                vectorMag(vectorSub(particles[2*i]->getPosition(), particles[2*i+2]->getPosition())), k, c));

                bonds.push_back(new SimpleBond(particles[2*i], particles[2*i+3],
                                vectorMag(vectorSub(particles[2*i]->getPosition(), particles[2*i+3]->getPosition())), k, c));

                bonds.push_back(new SimpleBond(particles[2*i+1], particles[2*i+2], 
                                vectorMag(vectorSub(particles[2*i+1]->getPosition(), particles[2*i+2]->getPosition())), k, c));

                bonds.push_back(new SimpleBond(particles[2*i+1], particles[2*i+3], 
                                vectorMag(vectorSub(particles[2*i+1]->getPosition(), particles[2*i+3]->getPosition())), k, c));
            }
        }

        // Sets (if true) the bottom and top particles as fixed
        if (fixBot)
        {
            fix(0);
            fix(0);
        }
        if (fixTop)
        {
            fix(particles.size()-1);
            fix(particles.size()-1);
        }
    }
}