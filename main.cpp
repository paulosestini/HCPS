#include <iostream>
#include "BuildingElements.h"
#include "MathUtils.hpp"
#include <chrono>
#include <thread>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>

using namespace std;

int main()
{   
    // Particles and bonds storage
    vector<Particle*> fixedParticles;
    vector<Particle*> particles;
    vector<Bond> bonds;

    // The fixed particles
    fixedParticles.push_back(new Particle(Vector{2+1.75, 6}, 1));
    fixedParticles.push_back(new Particle(Vector{2+2.25, 6}, 1));

    float particles_y = 30; // How many particles of height the tower will have
    float y_spacing = 5/particles_y; // Vertical spacing between particles in the tower

    for(int i = 0; i < particles_y; i++)
    {
        particles.push_back(new Particle(Vector{2+1.75, 6-(i+1)*y_spacing}, 1));
        particles.push_back(new Particle(Vector{2+2.25, 6-(i+1)*y_spacing}, 1));
    }
    
    // Sets the bonds between the fixed particles and the first two free particles
    bonds.push_back(Bond(fixedParticles[0], particles[0],
                    vectorMag(vectorSub(fixedParticles[0]->pos, particles[0]->pos))));

    bonds.push_back(Bond(fixedParticles[1], particles[0],
                    vectorMag(vectorSub(fixedParticles[1]->pos, particles[0]->pos))));

    bonds.push_back(Bond(fixedParticles[0], particles[1],
                    vectorMag(vectorSub(fixedParticles[0]->pos, particles[1]->pos))));

    bonds.push_back(Bond(fixedParticles[1], particles[1],
                    vectorMag(vectorSub(fixedParticles[1]->pos, particles[1]->pos))));

    
    for(int i = 0; i < particles_y; i += 1)
    {   
        bonds.push_back(Bond(particles[2*i], particles[2*i+1], 
                        vectorMag(vectorSub(particles[2*i]->pos, particles[2*i+1]->pos))));
        if(i != particles_y-1)
        {
            bonds.push_back(Bond(particles[2*i], particles[2*i+2],
                            vectorMag(vectorSub(particles[2*i]->pos, particles[2*i+2]->pos))));

            bonds.push_back(Bond(particles[2*i], particles[2*i+3],
                            vectorMag(vectorSub(particles[2*i]->pos, particles[2*i+3]->pos))));

            bonds.push_back(Bond(particles[2*i+1], particles[2*i+2], 
                            vectorMag(vectorSub(particles[2*i+1]->pos, particles[2*i+2]->pos))));

            bonds.push_back(Bond(particles[2*i+1], particles[2*i+3], 
                            vectorMag(vectorSub(particles[2*i+1]->pos, particles[2*i+3]->pos))));
        }
    }

    // fixedParticles.push_back(new Particle(Vector{2+1.75, 6-(particles_y+1)*y_spacing}, 1));
    // fixedParticles.push_back(new Particle(Vector{2+2.25, 6-(particles_y+1)*y_spacing}, 1));

    // bonds.push_back(Bond(fixedParticles[2], particles[particles_y*2-1],
    //                 vectorMag(vectorSub(fixedParticles[2]->pos, particles[particles_y*2-1]->pos))));

    // bonds.push_back(Bond(fixedParticles[3], particles[particles_y*2-1],
    //                 vectorMag(vectorSub(fixedParticles[3]->pos, particles[particles_y*2-1]->pos))));

    // bonds.push_back(Bond(fixedParticles[2], particles[particles_y*2-2],
    //                 vectorMag(vectorSub(fixedParticles[2]->pos, particles[particles_y*2-2]->pos))));

    // bonds.push_back(Bond(fixedParticles[3], particles[particles_y*2-2],
    //                 vectorMag(vectorSub(fixedParticles[3]->pos, particles[particles_y*2-2]->pos))));

    // Constants
    constexpr float dt = 0.05;
    constexpr int scale = 100;
    constexpr int circleRadius = 3;
    Vector gravity{0, 0.001};
    
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
        for(auto bond: bonds)
        {
            bond.act(dt);
            line[0].position = sf::Vector2f(bond.p1->pos.x*scale+circleRadius, 
                                            bond.p1->pos.y*scale+circleRadius);
            line[1].position = sf::Vector2f(bond.p2->pos.x*scale+circleRadius, 
                                            bond.p2->pos.y*scale+circleRadius);
            window.draw(line, 2, sf::Lines);    
        }

        // Drawing fixed particles
        circle.setFillColor(sf::Color::Red);
        for(auto particle: fixedParticles)
        {   
            circle.setPosition(sf::Vector2f(particle->pos.x*scale, particle->pos.y*scale));
            window.draw(circle);
        }

        // Applying forces to the tower
        for(int i = 21; i < 31; i += 2)
        {   
            if(!shouldApplyForce) break;
            particles[particles_y*2-i]->applyForce(Vector({-0.005, 0}), dt);

            float x = particles[particles_y*2-i]->pos.x*scale;
            float y = particles[particles_y*2-i]->pos.y*scale;
            
            rect.setPosition(sf::Vector2f(x, y));
            window.draw(rect);

        }

        // Updating and drawing free particles
        circle.setFillColor(sf::Color::White);
        for(auto particle: particles)
        {   
            //particle->applyForce(gravity, dt);
            particle->update(dt);
            //circle.setPosition(sf::Vector2f(particle->pos.x*scale, particle->pos.y*scale));
            //window.draw(circle);
        }

        window.display();        

    }

    

    return 0;
}