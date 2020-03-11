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

    void SimpleTower::update(hc::GraphicElements *graphics, hc::Inputs inputs, const double spatialScale, const double timeScale, double dt) //OBSERVACAO: QUERIA DEFINIR ESSA FUNCAO NA CLASSE BOND, MAS O PROGRAMO BUGAVA
    {
        // Selection mode (Updates and draws dragged nodes with mouse and free nodes)
        if (inputs.isMouseClicked)
        {
            int nSelected = 0;
            for (auto particle: particles)
            {
                collideWithBounds(particle);
                particle->update(dt);

                float distX = inputs.mousePos.x - particle->getPosition().x*spatialScale;
                float distY = inputs.mousePos.y - particle->getPosition().y*spatialScale;
                if (distX*distX + distY*distY <= graphics->circleWhite.getRadius()*spatialScale)
                {
                    graphics->drawSelectedNode(particle->getPosition());
                    particle->isSelected = true;
                    nSelected++;
                }
                else
                    graphics->drawFreeNode(particle->getPosition());
            }
            for (auto particle: particles)
            {
                float distX = inputs.mousePos.x - particle->getPosition().x*spatialScale;
                float distY = inputs.mousePos.y - particle->getPosition().y*spatialScale;
                if (particle->isSelected)
                {
                    particle->applyForce(MathUtils::Vector({distX*1000*timeScale*timeScale, distY*1000*timeScale*timeScale}));
                    particle->isSelected = false;
                }
            }
        }
        // Normal mode (Updates and draws free nodes)
        else
        {
            for (auto particle: particles)
            {
                collideWithBounds(particle);
                particle->update(dt);
                graphics->drawFreeNode(particle->getPosition());
            }
        }
        // Draws (and don't update) fixed nodes
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
        float k=1000*particles_y*particles_y*timeScale*timeScale, c=1*particles_y*timeScale;
        for(int i = 0; i < particles_y; i ++)
        {   
            bond(particles[2*i], particles[2*i+1], k, c);
            if(i < particles_y-1)
            {
                bond(particles[2*i], particles[2*i+2], k, c);
                bond(particles[2*i], particles[2*i+3], k, c);
                bond(particles[2*i+1], particles[2*i+2], k, c);
                bond(particles[2*i+1], particles[2*i+3], k, c);
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