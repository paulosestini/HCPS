#include <iostream>

#include "StructureElement.hpp"
#include "GraphicElements.hpp"
#include "MathUtils.hpp"
#include "DEFINITIONS.hpp"

int main()
{
    /* **  -----------------------------------------------------  ***
    * ***                                                         ***
    * ***  WELCOME TO HCSS (Hyper Cool Structural Simulator)!!!   ***
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
   * 1) Make the particle's size and collor atributes os each structure, not global atributes;
   * 2) Recheck all units relationships in the DLC file (exs: how changing the block's mass change it's hardness; how changing the fluid's damping change it's density.);
   * 3) Being able to turn on and off the particles collisions inside one structure;
   * 4) ...
   */

    // Inputs
    hc::Inputs inputs;
    // Graphic elements
    hc::GraphicElements* graphics = new hc::GraphicElements(SPATIAL_SCALE, CLOCK_DT);

    // Structures
    hc::StructureElement block = hc::StructureElement();
    block.build_RectShape_XGrid(JELLO_BLOCK);

    hc::StructureElement fluid = hc::StructureElement();
    fluid.build_Fluid(OIL_FLUID);

    
    while(graphics->isWindowOpen())
    {
        graphics->update(&inputs);
        graphics->clear();

        // Applying selection input tools with a priority order
        block.selectAndAct(inputs, UPDATE_DT);
        if (!block.alreadySelected)
        {
            fluid.selectAndAct(inputs, UPDATE_DT);
            // if (!fluid.alreadySelected)
            // {
            //     /* Continue this pattern for other structures */
            // }
        }

        // Acting inter-structure forces
        hc::StructureElement::interactStructures(&block, &fluid, graphics, BLOCK_FLUID_K, OIL_BLOCK_VISC);

        // Acting, updating and drawing free, fixed and selected particles
        block.update(graphics, inputs, COLLISION_K_IN_BLOCK, COLLISION_C_IN_BLOCK, UPDATE_DT);
        fluid.update(graphics, inputs, 1.0/OIL_FLUID_DAMPING, OIL_FLUID_VISCOSITY, UPDATE_DT);

        graphics->drawClock();
        graphics->display();     
    }
 
    return 0;
}