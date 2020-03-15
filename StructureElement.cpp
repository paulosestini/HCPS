#include "StructureElement.hpp"

namespace hc
{
    /* --- Functions --- */

    // BONDS ACTION AND DRAWING
    void StructureElement::act(hc::GraphicElements *graphics, double dt) //OBSERVACAO: QUERIA DEFINIR ESSA FUNCAO NA CLASSE BOND, MAS O PROGRAMO BUGAVA
    {
        for(auto bond: bonds)
        {
            bond->act(dt);
            graphics->drawBond(bond->calculatedForce, bond->p1->getPosition(), bond->p2->getPosition());
        }
    }

    // PARTICLES SELECTION (select particles inside a certain radius around the mouse)
    void StructureElement::selectParticles(hc::GraphicElements *graphics, hc::Inputs inputs, double dt)
    {
        for (auto particle: particles)
        {
            stayInBoxBound(particle);
            particle->update(dt);

            float distX = inputs.mousePos.x - particle->getPosition().x*graphics->scale;
            float distY = inputs.mousePos.y - particle->getPosition().y*graphics->scale;
            if (distX*distX + distY*distY <= graphics->freeNodeShape.getRadius()*graphics->scale)
            {
                //graphics->drawSelectedNode(particle->getPosition());
                particle->isSelected = true;
            }
            else
            {
                particle->isSelected = false;
                //graphics->drawFreeNode(particle->getPosition());
            }
        }
        for (auto particle: fixedParticles)
        {
            float distX = inputs.mousePos.x - particle->getPosition().x*graphics->scale;
            float distY = inputs.mousePos.y - particle->getPosition().y*graphics->scale;
            if (distX*distX + distY*distY <= graphics->freeNodeShape.getRadius()*graphics->scale)
            {
                particle->isSelected = true;
            }
            else
                particle->isSelected = false;
            //graphics->drawFixedNode(particle->getPosition());
        }
    }

    // SELECTED PARTICLES WILL BE FIXED
    void StructureElement::fixMode()
    {
        for (int i=0; i<particles.size(); i++)
        {
            if (particles[i]->isSelected)
            {
                particles[i]->isSelected = false;
                fix(i);
            }
        }
    }

    // SELECTED PARTICLES WILL BE UNFIXED
    void StructureElement::unfixMode()
    {
        for (int i=0; i<fixedParticles.size(); i++)
        {
            if (fixedParticles[i]->isSelected)
            {
                fixedParticles[i]->setAcceleration(MathUtils::Vector{0,0});
                fixedParticles[i]->isSelected = false;
                unfix(i);
            }
        }
    }

    // MOUSE APPLIES FORCE TO SELECTED PARTICLES
    void StructureElement::mouseDragMode(hc::GraphicElements *graphics, hc::Inputs inputs, const double timeScale)
    {
        for (auto particle: particles)
        {
            float distX = inputs.mousePos.x - particle->getPosition().x*graphics->scale;
            float distY = inputs.mousePos.y - particle->getPosition().y*graphics->scale;
            if (particle->isSelected)
            {
                particle->applyForce(MathUtils::Vector({distX*1000*mouseForceScale*timeScale*timeScale, distY*mouseForceScale*1000*timeScale*timeScale}));
                particle->isSelected = false;
            }
        }
        for (auto particle: fixedParticles)
        {
            particle->isSelected = false;
        }
    }

    // FREE FROM INPUTS SIMULATION
    void StructureElement::notSelectedMode(hc::GraphicElements *graphics, double dt)
    {
        for (auto particle: particles)
        {
            stayInBoxBound(particle);
            particle->update(dt);
            //graphics->drawFreeNode(particle->getPosition());
        }
        for(auto particle: fixedParticles)
        {   
            //graphics->drawFixedNode(particle->getPosition());
        }
    }

    // PARTICLES CONDITIONAL UPDATE AND DRAWING
    void StructureElement::update(hc::GraphicElements *graphics, hc::Inputs inputs, const double timeScale, double dt) //OBSERVACAO: QUERIA DEFINIR ESSA FUNCAO NA CLASSE BOND, MAS O PROGRAMO BUGAVA
    {
        // Normal mode (Updates and draws nodes)
        if (!inputs.isSelectionModeOn)
        {
            notSelectedMode(graphics, dt);
        }
        // Selection mode (Same as normal mode, but some particles are in selected condition)
        else // (Activate with mouseclick)
        {
            selectParticles(graphics, inputs, dt);
            // Selected condition = fix the particle (Activate with mouseclick + F)
            if (inputs.isFixModeOn)
            {
                fixMode();
            }
            // Selected condition = unfix the particle (Activate with mouseclick + U)
            else if (inputs.isUnfixModeOn)
            {
                unfixMode();
            }
            // Selected condition = drag particle with mouse (Activate with just the mouseclick)
            else
            {
                mouseDragMode(graphics, inputs, timeScale);
            }
        }
    }

    // PRESET STRUCTURE CONSTRUCTOR
    SimpleTower::SimpleTower(const double mass, const int particles_y, const double y_spacing, const double x_spacing, double timeScale, bool fixBot, bool fixTop) : StructureElement()
    {
        // Sets the free particles and their initial pos, vel and mass
        this->mouseForceScale = mass*particles_y*2;
        for(int i = 0; i < particles_y; i++)
        {
            particles.push_back(new Particle(MathUtils::Vector{
                (BOUND_BOX_POS_POS_X + BOUND_BOX_POS_WIDTH/2)/SPATIAL_SCALE - x_spacing/2.f,
                -(i+0)*y_spacing},
                MathUtils::Vector{0.f, 0.f}, mass)
            );
            particles.push_back(new Particle(MathUtils::Vector{
                (BOUND_BOX_POS_POS_X + BOUND_BOX_POS_WIDTH/2)/SPATIAL_SCALE + x_spacing/2.f,
                -(i+0)*y_spacing},
                MathUtils::Vector{0.f, 0.f}, mass)
            );
        }
    
        // Sets the bonds between the free particles as an X type grid
        float k=400*particles_y*particles_y*timeScale*timeScale, c=20*particles_y*timeScale;
        for(int i = 0; i < particles_y; i ++)
        {   
            bond(particles[2*i], particles[2*i+1], k, c);
            if(i < particles_y-1)
            {
                bond(particles[2*i+0], particles[2*i+2], k, c);
                bond(particles[2*i+0], particles[2*i+3], k, c);
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

    RectangularBody::RectangularBody(const double mass, const int particles_y, const int particles_x, const double y_spacing, const double x_spacing, double timeScale) : StructureElement()
    {
        // Sets the free particles and their initial pos, vel and mass
        this->mouseForceScale = mass;
        for(int i = 0; i < particles_y; i++)
        {
            for(int j = 0; j < particles_x; j++)
            {
                particles.push_back(new Particle(MathUtils::Vector{
                (BOUND_BOX_POS_POS_X + BOUND_BOX_POS_WIDTH/2)/SPATIAL_SCALE + (j - particles_x/2)*x_spacing,
                -(i)*y_spacing},
                MathUtils::Vector{0.f, 0.f}, mass)
                );
            }
        }
    
        // Sets the bonds between the free particles as an X type grid
        float k=800*particles_y*particles_y*timeScale*timeScale, c=20*particles_y*timeScale;

        for(int i = 0; i < particles_y; i++){
            for(int j = 0; j < particles_x-1; j++){
                bond(particles[particles_x*i+j], particles[particles_x*i+j+1], k, c);
            }
        }

        for(int i = 0; i < particles_y-1; i++){
            for(int j = 0; j < particles_x; j++){
                bond(particles[particles_x*i+j], particles[particles_x*(i+1)+j], k, c);
            }
        }

        for(int i = 0; i < particles_y-1; i++){
            for(int j = 0; j < particles_x-1; j++){
                bond(particles[particles_x*i+j], particles[particles_x*(i+1)+j+1], k, c);
            }
        }

        for(int i = particles_y-1; i > 0; i--){
            for(int j = 0; j < particles_x-1; j++){
                bond(particles[particles_x*i+j], particles[particles_x*(i-1)+j+1], k, c);
            }
        }
    }
}