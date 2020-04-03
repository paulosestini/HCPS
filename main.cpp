#include <iostream>

#include "DEFINITIONS.hpp"
#include "Interface/Renderer.hpp"
#include "Interface/InputHandler.hpp"
#include "Utils/MathUtils.hpp"

#include "Presets/RectShape_XGrid.hpp"
#include "Presets/Fluid.hpp"

int main()
{
    /* **  -----------------------------------------------------  ***
    * ***                                                         ***
    * ***  WELCOME TO HCPS (Hyper Cool Physics Simulator)!!!   ***
    * ***                                                         ***
    * ***  -----------------------------------------------------  ***
    * ***  Creators:                                              ***
    * ***  Carlos Eduardo Jedwab && Paulo Otávio Sestini          ***
    * ***  -----------------------------------------------------  ***
    * 
    * We have a few preset structures ready for your usage:
    * -For 'block_RectShape_XGrid' types, we have HARD_BLOCK, JELLO_BLOCK and JELLYFISH_BLOCK
    * (NOTE: use the suffix _DATA followed by the initial position parameter to change just the initial position);
    * -For 'fluid' types, we have OIL_FLUID and WATER_FLUID
    * (NOTE: don't forget to change the fluid damping and viscosity in the update calling as well when changing fluid type)
    * (NOTE: don't forget to change the block-fluid viscosity as well).
    * 
    */

   /*
   * TASKS for future versions:
   * 1) MAKE THE PARTICLE'S SIZE AND COLLOR ATRIBUTES OS EACH STRUCTURE, NOT GLOBAL ATRIBUTES;
   * 2) Recheck all units relationships in the DLC file (exs: how changing the block's mass change it's hardness; how changing the fluid's damping change it's density.);
   * 3) Being able to turn on and off the particles collisions inside one structure;
   * 4) ...
   */

    // User inputs handler
        hc::InputHandler* inputHandler = new hc::InputHandler();

    // Screen renderer
        hc::Renderer* graphics = new hc::Renderer(SPATIAL_SCALE, CLOCK_DT);

    // Particle systems
        hc::HardBlock block(1.0/2); // Try it with different presets
            /* Edit block's parematers between here */
        block.build();
    
        hc::Water fluid; // Try it with different presets
            /* Edit fluid's parematers between here */
            fluid.collisionRadius /= 2;
        fluid.build();

    // Particle shapes
        sf::CircleShape freeBlock1Node = sf::CircleShape(1);
        freeBlock1Node.setOrigin(freeBlock1Node.getRadius(), freeBlock1Node.getRadius());
        freeBlock1Node.setFillColor(sf::Color::White);

        sf::CircleShape freeFluid1Node = sf::CircleShape(2);
        freeFluid1Node.setOrigin(freeFluid1Node.getRadius(), freeFluid1Node.getRadius());
        freeFluid1Node.setFillColor(sf::Color::Blue);

        sf::CircleShape slctNode = sf::CircleShape(3);
        slctNode.setOrigin(slctNode.getRadius(), slctNode.getRadius());
        slctNode.setFillColor(sf::Color::Yellow);
        
        sf::CircleShape fixdNode = sf::CircleShape(3);
        fixdNode.setOrigin(fixdNode.getRadius(), fixdNode.getRadius());
        fixdNode.setFillColor(sf::Color::Red);
    
    while(graphics->isWindowOpen())
    {
    // Simulation updating
        // Acting internally on the free particles
        block.internalAct(block.hardness, block.steadiness, UPDATE_DT);
        block.externalAct(UPDATE_DT);

        fluid.internalAct(1.0/fluid.damping, fluid.viscosity, UPDATE_DT);
        fluid.externalAct(UPDATE_DT);

        // Acting on the selected particles with a priority order
        inputHandler->update(&(graphics->window));
        block.selectionAct(inputHandler, UPDATE_DT);
        if (!block.alreadySelected)
        {
            fluid.selectionAct(inputHandler, UPDATE_DT);
            // if (!nextParticleSystem.alreadySelected)
            // {
            //     /* Continue this pattern for other particle systems */
            // }
        }

        // Acting the inter-structure forces
        hc::ParticleSystem::interAct(&block, &fluid, 1.0/fluid.damping, fluid.viscosity);

        block.finalUpdate(UPDATE_DT);
        fluid.finalUpdate(UPDATE_DT);

    // Renderization
        graphics->clear();
        
        graphics->render(&block, &freeBlock1Node, &fixdNode, &slctNode, UPDATE_DT, 255);
        graphics->render(&fluid, &freeFluid1Node, &fixdNode, &slctNode, UPDATE_DT, 70);
        graphics->drawClock();

        graphics->display(); 
    }
 
    return 0;
}