#include <iostream>

#include <chrono>
#include <thread>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>

#include "StructureElement.hpp"
#include "SimpleBond.hpp"
#include "MathUtils.hpp"

using namespace StructSim;

int main()
{   
    StructureElement structure;

    // The fixed particles
    structure.fixedParticles.push_back(new StructureElement::Particle(MyMath::Vector{2+2.25, 6}, MyMath::Vector{0, 0}, 1));
    structure.fixedParticles.push_back(new StructureElement::Particle(MyMath::Vector{2+2.25, 6}, MyMath::Vector{0, 0}, 1));

    float particles_y = 30; // How many particles of height the tower will have
    float y_spacing = 5/particles_y; // Vertical spacing between particles in the tower

    for(int i = 0; i < particles_y; i++)
    {
        structure.particles.push_back(new StructureElement::Particle(MyMath::Vector{2+1.75, 6-(i+1)*y_spacing}, MyMath::Vector{0, 0}, 1));
        structure.particles.push_back(new StructureElement::Particle(MyMath::Vector{2+2.25, 6-(i+1)*y_spacing}, MyMath::Vector{0, 0}, 1));
    }
    
    // Sets the bonds between the fixed particles and the first two free particles
    structure.bonds.push_back(new SimpleBond(structure.fixedParticles[0], structure.particles[0],
                    vectorGetMag(vectorGetSub(structure.fixedParticles[0]->GetPosition(), structure.particles[0]->GetPosition()))));

    structure.bonds.push_back(new SimpleBond(structure.fixedParticles[1], structure.particles[0],
                    vectorGetMag(vectorGetSub(structure.fixedParticles[1]->GetPosition(), structure.particles[0]->GetPosition()))));

    structure.bonds.push_back(new SimpleBond(structure.fixedParticles[0], structure.particles[1],
                    vectorGetMag(vectorGetSub(structure.fixedParticles[0]->GetPosition(), structure.particles[1]->GetPosition()))));

    structure.bonds.push_back(new SimpleBond(structure.fixedParticles[1], structure.particles[1],
                    vectorGetMag(vectorGetSub(structure.fixedParticles[1]->GetPosition(), structure.particles[1]->GetPosition()))));

    
    for(int i = 0; i < particles_y; i += 1)
    {   
        structure.bonds.push_back(new SimpleBond(structure.particles[2*i], structure.particles[2*i+1], 
                        vectorGetMag(vectorGetSub(structure.particles[2*i]->GetPosition(), structure.particles[2*i+1]->GetPosition()))));
        if(i != particles_y-1)
        {
            structure.bonds.push_back(new SimpleBond(structure.particles[2*i], structure.particles[2*i+2],
                            vectorGetMag(vectorGetSub(structure.particles[2*i]->GetPosition(), structure.particles[2*i+2]->GetPosition()))));

            structure.bonds.push_back(new SimpleBond(structure.particles[2*i], structure.particles[2*i+3],
                            vectorGetMag(vectorGetSub(structure.particles[2*i]->GetPosition(), structure.particles[2*i+3]->GetPosition()))));

            structure.bonds.push_back(new SimpleBond(structure.particles[2*i+1], structure.particles[2*i+2], 
                            vectorGetMag(vectorGetSub(structure.particles[2*i+1]->GetPosition(), structure.particles[2*i+2]->GetPosition()))));

            structure.bonds.push_back(new SimpleBond(structure.particles[2*i+1], structure.particles[2*i+3], 
                            vectorGetMag(vectorGetSub(structure.particles[2*i+1]->GetPosition(), structure.particles[2*i+3]->GetPosition()))));
        }
    }

    // structure.fixedParticles.push_back(new Particle(Vector{2+1.75, 6-(particles_y+1)*y_spacing}, 1));
    // structure.fixedParticles.push_back(new Particle(Vector{2+2.25, 6-(particles_y+1)*y_spacing}, 1));

    // bonds.push_back(Bond(structure.fixedParticles[2], particles[particles_y*2-1],
    //                 vectorGetMag(vectorGetSub(structure.fixedParticles[2]->GetPosition(), particles[particles_y*2-1]->GetPosition()))));

    // bonds.push_back(Bond(structure.fixedParticles[3], particles[particles_y*2-1],
    //                 vectorGetMag(vectorGetSub(structure.fixedParticles[3]->GetPosition(), particles[particles_y*2-1]->GetPosition()))));

    // bonds.push_back(Bond(structure.fixedParticles[2], particles[particles_y*2-2],
    //                 vectorGetMag(vectorGetSub(structure.fixedParticles[2]->GetPosition(), particles[particles_y*2-2]->GetPosition()))));

    // bonds.push_back(Bond(structure.fixedParticles[3], particles[particles_y*2-2],
    //                 vectorGetMag(vectorGetSub(structure.fixedParticles[3]->GetPosition(), particles[particles_y*2-2]->GetPosition()))));

    // Constants
    constexpr float dt = 0.05;
    constexpr int scale = 100;
    constexpr int circleRadius = 3;
    MyMath::Vector gravity{0, 0.001};
    
    // Windows and geometry
    sf::RenderWindow window(sf::VideoMode(800, 800), "Simulation");
    sf::CircleShape circle(circleRadius); // It's used for drawing the particles
    sf::Vertex line[2] = {sf::Vector2f(0, 0), sf::Vector2f(0, 0)}; // It's used for drawing the lines
    sf::RectangleShape rect(sf::Vector2f(100, 5)); // Represents the force being applied
    rect.setFillColor(sf::Color::Yellow);

    // Switches
    bool shouldApplyForce = true;

    sf::Event event;
    while(window.isOpen())
    {
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
            if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::F) shouldApplyForce = !shouldApplyForce;
            }
        }

        window.clear(sf::Color::Black);

        // Updating bonds and drawing the connection lines
        for(auto bond: structure.bonds)
        {
            bond->Act(dt);
            line[0].position = sf::Vector2f(bond->GetParticle1Ref()->GetPosition().x*scale+circleRadius, 
                                            bond->GetParticle1Ref()->GetPosition().y*scale+circleRadius);
            line[1].position = sf::Vector2f(bond->GetParticle2Ref()->GetPosition().x*scale+circleRadius, 
                                            bond->GetParticle2Ref()->GetPosition().y*scale+circleRadius);
            window.draw(line, 2, sf::Lines);    
        }

        // Drawing fixed particles
        circle.setFillColor(sf::Color::Red);
        for(auto particle: structure.fixedParticles)
        {   
            circle.setPosition(sf::Vector2f(particle->GetPosition().x*scale, particle->GetPosition().y*scale));
            window.draw(circle);
        }

        // Applying forces to the tower
        for(int i = 21; i < 31; i += 2)
        {   
            if(!shouldApplyForce) break;
            structure.particles[particles_y*2-i]->ApplyForce(MyMath::Vector({-0.005, 0}), dt);

            float x = structure.particles[particles_y*2-i]->GetPosition().x*scale;
            float y = structure.particles[particles_y*2-i]->GetPosition().y*scale;
            
            rect.setPosition(sf::Vector2f(x, y));
            window.draw(rect);

        }

        // Updating and drawing free particles
        circle.setFillColor(sf::Color::White);
        for(auto particle: structure.particles)
        {   
            //particle->applyForce(gravity, dt);
            particle->Update(dt);
            //circle.setPosition(sf::Vector2f(particle->GetPosition().x*scale, particle->GetPosition().y*scale));
            //window.draw(circle);
        }

        window.display();        

    }

    

    return 0;
}