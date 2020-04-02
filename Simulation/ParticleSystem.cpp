#include "ParticleSystem.hpp"

namespace hc
{
    /* --- Internal actions --- */

    void ParticleSystem::breakBond(int i)
    {
        if (bonds[i]->isBroken())
        {
            bonds.erase(bonds.begin() + i);
        }
    }

    void ParticleSystem::actBonds(double dt)
    {
        for(int i=0; i<bonds.size(); i++)
        {
            bonds[i]->act(dt);
            breakBond(i);
        }
    }

    void ParticleSystem::internalCollisions(double collisionK, double collisionC)
    {
        for (auto p1=particles.begin(); p1!=particles.end(); ++p1)
        {
            for (auto p2=p1+1; p2!=particles.end(); ++p2)
            {
                MathUtils::Vector r = MathUtils::vectorSub((*p1)->getPosition(),(*p2)->getPosition());
                double r_mag = MathUtils::vectorMag(r);
                if (r_mag < (*p1)->getRadius() + (*p2)->getRadius())
                {
                    double eqDist = (*p1)->getRadius()+(*p2)->getRadius();
                    MathUtils::Vector calculatedForce = Bond::findSpringForce(*p1, *p2, eqDist, collisionK, collisionC);

                    (*p2)->applyForce(calculatedForce);
                    (*p1)->applyForce(MathUtils::vectorScale(calculatedForce, -1));
                }
            }
        }
    }

    /* --- Wrapper action application function --- */

    // FREE PARTICLES ACTION APPLICATION
    void ParticleSystem::internalAct(double collisionK, double collisionC, double dt) //OBSERVACAO: QUERIA DEFINIR ESSA FUNCAO NA CLASSE BOND, MAS O PROGRAMO BUGAVA
    {
        // Updating bonds
        actBonds(dt);

        // Applying the very dynamic interactions
        internalCollisions(collisionK, collisionC);
    }

    /* --- Environmental forces --- */

    void ParticleSystem::externalAct(double dt)
    {
        for(auto particle: particles)
        {
            // Some external dissipation of energy
            particle->applyForce(MathUtils::vectorScale(MathUtils::vectorScale(particle->getVelocity(), MathUtils::vectorMag(particle->getVelocity())), -FIELD_DISSIPATION));

            // Gravity aplication
            particle->accelerate(MathUtils::vectorScale(GRAVITY_FORCE, dt));
        }
    }

    /* --- User inserted actions (particle selection) --- */

    // PARTICLES SELECTION (select particles inside a certain radius around the mouse)
    bool ParticleSystem::selectParticle(hc::InputHandler *inputs, double dt)
    {
        // OBS:There is a priority for selecting fixed particles
        for (auto particle: fixedParticles)
        {
            float distX = inputs->mousePos.x - particle->getPosition().x;
            float distY = inputs->mousePos.y - particle->getPosition().y;
            if (distX*distX + distY*distY <= NODE_SELECTION_RADIUS)
            {
                selectedParticle = particle;
                alreadySelected = true;
                return true;
            }
        }
        for (auto particle: particles)
        {
            float distX = inputs->mousePos.x - particle->getPosition().x;
            float distY = inputs->mousePos.y - particle->getPosition().y;
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
    void ParticleSystem::actFixMode()
    {
        selectedParticle->setAcceleration(MathUtils::Vector{0,0});
        selectedParticle->setVelocity(MathUtils::Vector{0,0});
        fix(selectedParticle);
    }

    // SELECTED PARTICLES WILL BE UNFIXED
    void ParticleSystem::actUnfixMode()
    {
        selectedParticle->setAcceleration(MathUtils::Vector{0,0});
        selectedParticle->setVelocity(MathUtils::Vector{0,0});
        unfix(selectedParticle);
    }

    // MOUSE APPLIES FORCE TO SELECTED PARTICLES
    void ParticleSystem::actMouseDragMode(hc::InputHandler *inputs, double dt)
    {
        MathUtils::Vector dist{
        inputs->mousePos.x - selectedParticle->getPosition().x,
        inputs->mousePos.y - selectedParticle->getPosition().y
        };

        selectedParticle->setAcceleration(MathUtils::Vector{0,0});
        selectedParticle->setVelocity(MathUtils::vectorScale(dist, 1/dt));
    }

    // SELECTION ACTIONS APPLICATION
    void ParticleSystem::selectionAct(hc::InputHandler *inputs, double dt)
    {
        if (inputs->isSelectionModeOn)
        {
            if (!alreadySelected)
            {
                isSelectedFixed = selectParticle(inputs, dt);
            }
            if (alreadySelected)
            {
                // Selected particle will be fixed (Activate with mouseclick + F)
                if (inputs->isFixModeOn && !isSelectedFixed)
                {
                    actFixMode();
                    alreadySelected = false;
                }
                // Selected particle will be unfixed (Activate with mouseclick + U)
                else if (inputs->isUnfixModeOn && isSelectedFixed)
                {
                    actUnfixMode();
                    alreadySelected = false;
                }
                // Selected particle will be dragged by the mouse (Activate with just the mouseclick)
                else
                {
                    actMouseDragMode(inputs, dt);
                }
            }
        }
        else
            alreadySelected = false;
    }

    /* --- Inter-structure forces --- */

    void ParticleSystem::interAct(ParticleSystem *str1, ParticleSystem *str2, double collisionK, double collisionC)
    {
        for (auto p1=str1->particles.begin(); p1!=str1->particles.end(); ++p1)
        {
            for (auto p2=str2->particles.begin(); p2!=str2->particles.end(); ++p2)
            {
                MathUtils::Vector r = MathUtils::vectorSub((*p1)->getPosition(),(*p2)->getPosition());
                double r_mag = MathUtils::vectorMag(r);
                if (r_mag < (*p1)->getRadius() + (*p2)->getRadius())
                {
                    double eqDist = (*p1)->getRadius()+(*p2)->getRadius();
                    MathUtils::Vector calculatedForce = Bond::findSpringForce(*p1, *p2, eqDist, collisionK, collisionC);

                    (*p2)->applyForce(calculatedForce);
                    (*p1)->applyForce(MathUtils::vectorScale(calculatedForce, -1));
                }
            }
        }
    }

    void ParticleSystem::finalUpdate(double dt)
    {
        // Final update of the particles movement
        for (auto particle: particles)
        {
            stayInBoxBound(particle);
            particle->update(dt);
        }
    }
}