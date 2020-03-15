#include <iostream>

#include "StructureElement.hpp"
#include "GraphicElements.hpp"
#include "MathUtils.hpp"
#include "DEFINITIONS.hpp"

int main()
{
    // Inputs
    hc::Inputs inputs;
    // Graphic elements
    hc::GraphicElements* graphics = new hc::GraphicElements(SPATIAL_SCALE, CLOCK_DT);
    // Structure
    hc::RectangularBody tower = hc::RectangularBody(20, PARTICLES_Y, PARTICLES_X, Y_SPACING, X_SPACING, TIME_SCALE);

    while(graphics->isWindowOpen())
    {
        graphics->update(&inputs);
        graphics->clear();

        // Applying natural external forces to the tower
        for(auto particle: tower.particles)
        {
            // Some external dissipation of energy
            particle->applyForce(MathUtils::vectorScale(MathUtils::vectorScale(particle->getVelocity(), MathUtils::vectorMag(particle->getVelocity())), -FIELD_DISSIPATION));

            // Gravity aplication
            particle->accelerate(MathUtils::vectorScale(GRAVITY_FORCE, UPDATE_DT));
        }

        // Updating bonds and drawing the connection lines
        tower.act(graphics, UPDATE_DT);

        // Applying eventual external forces to the tower
        if (inputs.isForce1Applied) // Applying side force lines (force 1, press 1 to activate)
        {
            for(int i = 1; i < 9; i += 2)
            { 
                tower.particles[PARTICLES_Y*2-i]->applyForce(MathUtils::Vector({-200*TIME_SCALE*TIME_SCALE, 0}));

                double x = tower.particles[PARTICLES_Y*2-i]->getPosition().x;
                double y = tower.particles[PARTICLES_Y*2-i]->getPosition().y;
                
                graphics->drawForce(x, y, 0);
            }
        }
        if (inputs.isForce2Applied) // Applying top force lines (force 2, press 2 to activate)
        {
            for(int i = 0; i < 2; i++)
            { 
                tower.particles[PARTICLES_Y*2-1-i]->applyForce(MathUtils::Vector({0, 2500*TIME_SCALE*TIME_SCALE}));

                double x = tower.particles[PARTICLES_Y*2-1-i]->getPosition().x;
                double y = tower.particles[PARTICLES_Y*2-1-i]->getPosition().y;
                
                graphics->drawForce(x, y, 270);
            }
        }

        // Updating and drawing free, fixed and selected particles
        tower.update(graphics, inputs, TIME_SCALE, UPDATE_DT);

        graphics->drawClock();
        graphics->display();       
    }
 
    return 0;
}