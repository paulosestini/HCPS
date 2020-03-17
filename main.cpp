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
    hc::StructureElement structure = hc::StructureElement();
    BUILD_STRUCTURES

    while(graphics->isWindowOpen())
    {
        graphics->update(&inputs);
        graphics->clear();

        // Updating and drawing free, fixed and selected particles
        structure.update(graphics, inputs, UPDATE_DT);

        graphics->drawClock();
        graphics->display();     
    }
 
    return 0;
}