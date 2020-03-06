#include <iostream>

#include <chrono>
#include <thread>
#include <cstdlib>
#include <vector>

#include "StructureElement.hpp"
#include "GraphicElements.hpp"
#include "MathUtils.hpp"

// Constants
constexpr float dt = 0.05f;
constexpr int scale = 100.f;
constexpr int circleRadius = 3.f;
const float particles_y = 30.f; // How many particles of height the tower will have
const float y_spacing = 5.f/particles_y; // Vertical spacing between particles in the tower
const float dissipationFactor = 0.9f;
MyMath::Vector gravity{0, 0.001f};

// Switches
bool shouldApplyForce = false;

// Graphic elements
MyGraphics::GraphicElements* graphics = new MyGraphics::GraphicElements(800, 800, circleRadius, scale, dt);

int main()
{
    StructSim::SimpleTower tower = StructSim::SimpleTower(particles_y, y_spacing);

    while(graphics->IsWindowOpen())
    {
        shouldApplyForce = graphics->PollEvents(shouldApplyForce);

        graphics->Clear();

        // Updating bonds and drawing the connection lines
        tower.Act(graphics, dt); 

        // Updating and drawing free particles
        tower.Update(graphics, dt);

        // Applying natural external forces to the tower
        for(auto particle: tower.particles)
        {
            // Some dissipation of energy
            particle->Accelerate(MyMath::vectorSetScale(MyMath::vectorSetScale(particle->GetVelocity(), MyMath::vectorGetMag(particle->GetVelocity())), -dissipationFactor));

            // Gravity
            particle->Accelerate(MyMath::vectorSetScale(gravity, dt));
        }

        // Applying eventual external forces to the tower
        if (shouldApplyForce)
        {
            for(int i = 21; i < 31; i += 2)
            { 
                tower.particles[particles_y*2-i]->ApplyForce(MyMath::Vector({-0.005, 0}), dt);

                float x = tower.particles[particles_y*2-i]->GetPosition().x*scale;
                float y = tower.particles[particles_y*2-i]->GetPosition().y*scale;
                
                graphics->rect.setPosition(sf::Vector2f(x, y));
                graphics->window.draw(graphics->rect);
            }
        }

        // Drawing fixed particles
        for(auto particle: tower.fixedParticles)
        {   
            graphics->DrawNode(particle->GetPosition(), sf::Color::Red);
        }

        graphics->Display();       
    }
 
    return 0;
}