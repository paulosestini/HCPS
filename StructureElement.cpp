#include "StructureElement.hpp"

namespace hc
{
    /* --- Bond forces related functions --- */

    // BONDS ACTION, BREAKING AND DRAWING

    void StructureElement::bondBreaking(int i)
    {
        if (bonds[i]->isBroken())
        {
            bonds.erase(bonds.begin() + i);
        }
    }

    void StructureElement::act(hc::GraphicElements *graphics, double dt)
    {
        for(int i=0; i<bonds.size(); i++)
        {
            bonds[i]->act(dt);
            graphics->drawBond(bonds[i]->calculatedForce, bonds[i]->p1->getPosition(), bonds[i]->p2->getPosition(), 255);
            bondBreaking(i);
        }
    }

    /* --- Selection related functions --- */

    // PARTICLES SELECTION (select particles inside a certain radius around the mouse)
    bool StructureElement::selectAParticle(hc::Inputs inputs, double dt)
    {
        // OBS:There is a priority for selecting fixed particles
        for (auto particle: fixedParticles)
        {
            float distX = inputs.mousePos.x - particle->getPosition().x;
            float distY = inputs.mousePos.y - particle->getPosition().y;
            if (distX*distX + distY*distY <= NODE_SELECTION_RADIUS)
            {
                selectedParticle = particle;
                alreadySelected = true;
                return true;
            }
        }
        for (auto particle: particles)
        {
            float distX = inputs.mousePos.x - particle->getPosition().x;
            float distY = inputs.mousePos.y - particle->getPosition().y;
            if (distX*distX + distY*distY <= NODE_SELECTION_RADIUS)
            {
                selectedParticle = particle;
                alreadySelected = true;
                return false;
            }
        }
        alreadySelected = false;
    }

    // SELECTED PARTICLES WILL BE FIXED
    void StructureElement::fixMode()
    {
        selectedParticle->setAcceleration(MathUtils::Vector{0,0});
        selectedParticle->setVelocity(MathUtils::Vector{0,0});
        fix(selectedParticle);
    }

    // SELECTED PARTICLES WILL BE UNFIXED
    void StructureElement::unfixMode()
    {
        selectedParticle->setAcceleration(MathUtils::Vector{0,0});
        selectedParticle->setVelocity(MathUtils::Vector{0,0});
        unfix(selectedParticle);
    }

    // MOUSE APPLIES FORCE TO SELECTED PARTICLES
    void StructureElement::mouseDragMode(hc::Inputs inputs, double dt)
    {
        MathUtils::Vector dist{
        inputs.mousePos.x - selectedParticle->getPosition().x,
        inputs.mousePos.y - selectedParticle->getPosition().y
        };

        selectedParticle->setVelocity(MathUtils::vectorScale(dist, 1/dt));
    }

    /* --- Collision forces related functions --- */

    void StructureElement::particlesCollision(GraphicElements *graphics)
    {
        for (auto p1=particles.begin(); p1!=particles.end(); ++p1)
        {
            for (auto p2=p1+1; p2!=particles.end(); ++p2)
            {
                MathUtils::Vector r = MathUtils::vectorSub((*p1)->getPosition(),(*p2)->getPosition());
                if (MathUtils::vectorMag(r) < (*p1)->getRadius() + (*p2)->getRadius())
                {
                    MathUtils::Vector v = MathUtils::vectorSub((*p1)->getVelocity(), (*p2)->getVelocity());

                    double r_mag = MathUtils::vectorMag(r);
                    MathUtils::Vector r_hat = MathUtils::normalize(r);
                    MathUtils::Vector equilibrium_r = MathUtils::vectorScale(r_hat, (*p1)->getRadius() + (*p2)->getRadius());

                    MathUtils::Vector axial_v = MathUtils::vectorProj(v,r);
                    
                    MathUtils::Vector F_el = MathUtils::vectorScale(vectorSub(r, equilibrium_r), COLLISION_K_CONSTANT);
                    MathUtils::Vector F_at = MathUtils::vectorScale(axial_v, COLLISION_C_CONSTANT);
                    MathUtils::Vector calculatedForce = MathUtils::vectorAdd(F_el, F_at);

                    (*p2)->applyForce(calculatedForce);
                    (*p1)->applyForce(MathUtils::vectorScale(calculatedForce, -1));
                    graphics->drawBond(calculatedForce, (*p1)->getPosition(), (*p2)->getPosition(), 70);
                }
            }
        }
    }

    /* --- External forces --- */

    // GRAVITY AND FIELD DISSIPATION
    void StructureElement::applyExtForces(double dt)
    {
        for(auto particle: particles)
        {
            // Some external dissipation of energy
            particle->applyForce(MathUtils::vectorScale(MathUtils::vectorScale(particle->getVelocity(), MathUtils::vectorMag(particle->getVelocity())), -FIELD_DISSIPATION));

            // Gravity aplication
            particle->accelerate(MathUtils::vectorScale(GRAVITY_FORCE, dt));
        }
    }

    /* --- Main update function --- */

    // PARTICLES CONDITIONAL UPDATE AND DRAWING
    void StructureElement::update(hc::GraphicElements *graphics, hc::Inputs inputs, double dt) //OBSERVACAO: QUERIA DEFINIR ESSA FUNCAO NA CLASSE BOND, MAS O PROGRAMO BUGAVA
    {
        // Updating bonds and drawing the connection lines
        act(graphics, dt);

        // Applying selection input tools
        if (inputs.isSelectionModeOn)
        {
            if (!alreadySelected)
            {
                isSelectedFixed = selectAParticle(inputs, dt);
            }
            if (alreadySelected)
            {
                // Selected particle will be fixed (Activate with mouseclick + F)
                if (inputs.isFixModeOn && !isSelectedFixed)
                {
                    fixMode();
                    alreadySelected = false;
                }
                // Selected particle will be unfixed (Activate with mouseclick + U)
                else if (inputs.isUnfixModeOn && isSelectedFixed)
                {
                    unfixMode();
                    alreadySelected = false;
                }
                // Selected particle will be dragged by the mouse (Activate with just the mouseclick)
                else
                {
                    mouseDragMode(inputs, dt);
                }
            }
        }
        else
            alreadySelected = false;

        // Applying the very dynamic interactions
        particlesCollision(graphics);
        
        // Applying natural external forces
        applyExtForces(dt);
        
        // Updating and drawing the particles
        for (auto particle: particles)
        {
            stayInBoxBound(particle);
            particle->update(dt);
            graphics->drawFreeNode(particle->getPosition());
        }
        if (alreadySelected)
            graphics->drawSelectedNode(selectedParticle->getPosition());
        for(auto particle: fixedParticles)
        {
            graphics->drawFixedNode(particle->getPosition());
        }
    }

    // PRESET STRUCTURE BUILDERS

    void StructureElement::build_RectShape_XGrid(const double density, const int particles_y, const int particles_x, const double y_spacing, const double x_spacing, double collisionRadius)
    {
        double mass = density * y_spacing * x_spacing;
        // Sets the free particles and their initial pos, vel and mass
        for(int i = 0; i < particles_y; i++)
        {
            for(int j = 0; j < particles_x; j++)
            {
                particles.push_back(new Particle(MathUtils::Vector{
                (BOUND_BOX_POS_POS_X + BOUND_BOX_POS_WIDTH/2) + (j - particles_x/2)*x_spacing,
                -(i)*y_spacing
                }, MathUtils::Vector{0.f, 0.f}, mass, collisionRadius));
            }
        }
    
        // Sets the bonds between the free particles as an X type grid
        for(int i = 0; i < particles_y; i++){
            for(int j = 0; j < particles_x-1; j++){
                bond(particles[particles_x*i+j], particles[particles_x*i+j+1], BLOCK_MAX_DIST_FACTOR_CONSTANT, STRUCTURE_K_CONSTANT, STRUCTURE_C_CONSTANT);
            }
        }
        for(int i = 0; i < particles_y-1; i++){
            for(int j = 0; j < particles_x; j++){
                bond(particles[particles_x*i+j], particles[particles_x*(i+1)+j], BLOCK_MAX_DIST_FACTOR_CONSTANT, STRUCTURE_K_CONSTANT, STRUCTURE_C_CONSTANT);
            }
        }
        for(int i = 0; i < particles_y-1; i++){
            for(int j = 0; j < particles_x-1; j++){
                bond(particles[particles_x*i+j], particles[particles_x*(i+1)+j+1], BLOCK_MAX_DIST_FACTOR_CONSTANT, STRUCTURE_K_CONSTANT, STRUCTURE_C_CONSTANT);
            }
        }
        for(int i = particles_y-1; i > 0; i--){
            for(int j = 0; j < particles_x-1; j++){
                bond(particles[particles_x*i+j], particles[particles_x*(i-1)+j+1], BLOCK_MAX_DIST_FACTOR_CONSTANT, STRUCTURE_K_CONSTANT, STRUCTURE_C_CONSTANT);
            }
        }
    }

    void StructureElement::build_Fluid(const double density, int particles_y, int particles_x, double collisionRadius)
    {
        double mass = density * collisionRadius*2 * collisionRadius*2;
        for(int i = 0; i < particles_y; i++)
        {
            for(int j = 0; j < particles_x; j++)
            {
                particles.push_back(new Particle(MathUtils::Vector{
                (BOUND_BOX_POS_POS_X + BOUND_BOX_POS_WIDTH/2) + (j - particles_x/2)*2*collisionRadius*0.99,
                BOUND_BOX_POS_POS_Y + BOUND_BOX_POS_HEIGHT-(i+1)*2*collisionRadius
                }, MathUtils::Vector{0.f, 0.f}, mass, collisionRadius));
            }
        }
    }

    void StructureElement::build_Box()
    {
        
    }
}