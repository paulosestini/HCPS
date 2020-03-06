#include "StructureElement.hpp"

namespace StructSim
{
    // Functions
    void SimpleTower::Act(MyGraphics::GraphicElements *graphics, float dt) //OBSERVACAO: QUERIA DEFINIR ESSA FUNCAO NA CLASSE BOND, MAS O PROGRAMO BUGAVA
    {
        for(auto bond: bonds)
        {
            bond->Act(graphics, dt);
        }
    }

    void SimpleTower::Update(MyGraphics::GraphicElements *graphics, float dt) //OBSERVACAO: QUERIA DEFINIR ESSA FUNCAO NA CLASSE BOND, MAS O PROGRAMO BUGAVA
    {
        for(auto particle: particles)
        {   
            particle->Update(graphics, dt);
        }
    }

    // Constructor
    SimpleTower::SimpleTower(int particles_y, float y_spacing) : StructureElement()
    {
        fixedParticles.push_back(new Particle(MyMath::Vector{2+1.75, 6}, MyMath::Vector{0, 0}, 1));
        fixedParticles.push_back(new Particle(MyMath::Vector{2+2.25, 6}, MyMath::Vector{0, 0}, 1));

        for(int i = 0; i < particles_y; i++)
        {
            particles.push_back(new Particle(MyMath::Vector{2+1.75, (float)(6.f-(i+1.f)*y_spacing)}, MyMath::Vector{0.f, 0.f}, 1));
            particles.push_back(new Particle(MyMath::Vector{2+2.25, (float)(6.f-(i+1.f)*y_spacing)}, MyMath::Vector{0.f, 0.f}, 1));
        }

        // Sets the bonds between the fixed particles and the first two free particles
        bonds.push_back(new SimpleBond(fixedParticles[0], particles[0],
                        vectorGetMag(vectorGetSub(fixedParticles[0]->GetPosition(), particles[0]->GetPosition()))));

        bonds.push_back(new SimpleBond(fixedParticles[1], particles[0],
                        vectorGetMag(vectorGetSub(fixedParticles[1]->GetPosition(), particles[0]->GetPosition()))));

        bonds.push_back(new SimpleBond(fixedParticles[0], particles[1],
                        vectorGetMag(vectorGetSub(fixedParticles[0]->GetPosition(), particles[1]->GetPosition()))));

        bonds.push_back(new SimpleBond(fixedParticles[1], particles[1],
                        vectorGetMag(vectorGetSub(fixedParticles[1]->GetPosition(), particles[1]->GetPosition()))));

        for(int i = 0; i < particles_y; i += 1)
        {   
            bonds.push_back(new SimpleBond(particles[2*i], particles[2*i+1], 
                            vectorGetMag(vectorGetSub(particles[2*i]->GetPosition(), particles[2*i+1]->GetPosition()))));
            if(i != particles_y-1)
            {
                bonds.push_back(new SimpleBond(particles[2*i], particles[2*i+2],
                                vectorGetMag(vectorGetSub(particles[2*i]->GetPosition(), particles[2*i+2]->GetPosition()))));

                bonds.push_back(new SimpleBond(particles[2*i], particles[2*i+3],
                                vectorGetMag(vectorGetSub(particles[2*i]->GetPosition(), particles[2*i+3]->GetPosition()))));

                bonds.push_back(new SimpleBond(particles[2*i+1], particles[2*i+2], 
                                vectorGetMag(vectorGetSub(particles[2*i+1]->GetPosition(), particles[2*i+2]->GetPosition()))));

                bonds.push_back(new SimpleBond(particles[2*i+1], particles[2*i+3], 
                                vectorGetMag(vectorGetSub(particles[2*i+1]->GetPosition(), particles[2*i+3]->GetPosition()))));
            }
        }
    }

}