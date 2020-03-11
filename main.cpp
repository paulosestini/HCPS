#include <iostream>

#include "StructureElement.hpp"
#include "GraphicElements.hpp"
#include "MathUtils.hpp"

// Constants
constexpr double dt = 0.0000000000000005f; // Simulation's time step (change to alter simulation precision)
constexpr double timeScale = 0.0005f/dt; // Simulation's speed (change to speed up/down the simulation)
constexpr double clock_dt = timeScale*dt/1000000; // Display clock dt (change ONLY for calibration purposes)
// OBSERVATION: THIS NUMBERS WERE DETERMINED BY EXPERIMENTATION
// TASK: DETERMINE THIS NUMBERS WITH A BETTER METHOD

constexpr double spatialScale = 100.f;

constexpr int circleRadius = 3;
const int particles_y = 15; // How many particles of height the tower will have
const double y_spacing = 5.f/particles_y; // Vertical spacing between particles in the tower
const double x_spacing = 1.f;
const double fieldDissipation = 0.f;
MathUtils::Vector gravity{0.f, 9.8f*timeScale*timeScale};

// Inputs
hc::Inputs inputs;

// Graphic elements
hc::GraphicElements* graphics = new hc::GraphicElements(800, 800, circleRadius, spatialScale, clock_dt);

int main()
{
    hc::SimpleTower tower = hc::SimpleTower(particles_y, y_spacing, x_spacing, timeScale, false, false);

    while(graphics->isWindowOpen())
    {
        graphics->update(&inputs);

        graphics->clear();

        // Applying natural external forces to the tower
        for(auto particle: tower.particles)
        {
            // Some dissipation of energy
            particle->applyForce(MathUtils::vectorScale(MathUtils::vectorScale(particle->getVelocity(), MathUtils::vectorMag(particle->getVelocity())), -fieldDissipation));

            // Gravity
            particle->accelerate(MathUtils::vectorScale(gravity, dt));
        }

        // Updating bonds and drawing the connection lines
        tower.act(graphics, dt); 

        // Applying eventual external forces to the tower
        if (inputs.isForce1Applied) // Applying side force lines
        {
            for(int i = 11; i < 31; i += 2)
            { 
                tower.particles[particles_y*2-i]->applyForce(MathUtils::Vector({-200*timeScale*timeScale, 0}));

                double x = tower.particles[particles_y*2-i]->getPosition().x*spatialScale;
                double y = tower.particles[particles_y*2-i]->getPosition().y*spatialScale;
                
                graphics->drawForce(x, y, 0);
            }
        }
        if (inputs.isForce2Applied) // Applying top force lines
        {
            for(int i = 0; i < 2; i++)
            { 
                tower.particles[particles_y*2-1-i]->applyForce(MathUtils::Vector({0, 2500*timeScale*timeScale}));

                double x = tower.particles[particles_y*2-1-i]->getPosition().x*spatialScale;
                double y = tower.particles[particles_y*2-1-i]->getPosition().y*spatialScale;
                
                graphics->drawForce(x, y, 270);
            }
        }

        // Updating and drawing free, fixed and selected particles
        tower.update(graphics, inputs, spatialScale, timeScale, dt);

        graphics->drawClock();
        graphics->display();       
    }
 
    return 0;
}