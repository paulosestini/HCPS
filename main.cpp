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
const int particles_y = 25; // How many particles of height the tower will have
const double y_spacing = 5.f/particles_y; // Vertical spacing between particles in the tower
const double x_spacing = 1.f;
const double fieldDissipation = 0.f;
MathUtils::Vector gravity{0, 9.8f*timeScale*timeScale};

// Inputs
hc::Inputs inputs;

// Graphic elements
hc::GraphicElements* graphics = new hc::GraphicElements(800, 800, circleRadius, spatialScale, clock_dt);

int main()
{
    hc::SimpleTower tower = hc::SimpleTower(particles_y, y_spacing, x_spacing, timeScale, true, true);

    while(graphics->isWindowOpen())
    {
        graphics->update(&inputs);

        graphics->clear();

        // Updating bonds and drawing the connection lines
        tower.act(graphics, dt); 

        // Updating and drawing free particles
        tower.update(graphics, dt);

        // Applying natural external forces to the tower
        for(auto particle: tower.particles)
        {
            // Some dissipation of energy
            particle->accelerate(MathUtils::vectorScale(MathUtils::vectorScale(particle->getVelocity(), MathUtils::vectorMag(particle->getVelocity())), -fieldDissipation));

            // Gravity
            particle->accelerate(MathUtils::vectorScale(gravity, dt));
        }

        // Applying eventual external forces to the tower
        if (inputs.isForceApplied) // Applying force lines
        {
            for(int i = 11; i < 31; i += 2)
            { 
                tower.particles[particles_y*2-i]->applyForce(MathUtils::Vector({-100*timeScale*timeScale, 0}));

                double x = tower.particles[particles_y*2-i]->getPosition().x*spatialScale;
                double y = tower.particles[particles_y*2-i]->getPosition().y*spatialScale;
                
                graphics->rect.setPosition(sf::Vector2f(x, y));
                graphics->window.draw(graphics->rect);
            }
        }
        if (inputs.isMouseClicked) // Dragging nodes with mouse
        {
            for (auto particle: tower.particles)
            {
                float distX = inputs.mousePos.x - particle->getPosition().x*spatialScale;
                float distY = inputs.mousePos.y - particle->getPosition().y*spatialScale;
                if (distX*distX + distY*distY <= circleRadius*spatialScale)
                    particle->isSelected = true;
                else 
                    particle->isSelected = false;
                
                if (particle->isSelected)
                {
                    particle->applyForce(MathUtils::Vector({distX*1000*timeScale*timeScale, distY*1000*timeScale*timeScale}));
                    //break;
                }
            }
        }

        graphics->drawClock();
        graphics->display();       
    }
 
    return 0;
}