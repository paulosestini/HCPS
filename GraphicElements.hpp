#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "MathUtils.hpp"

#include <SFML/Graphics.hpp>
#include <unistd.h>

namespace MyGraphics
{
    class GraphicElements
    {
    public:
        // Constructor/Destructor
        GraphicElements(int width, int height, const float circleRadius, const float scale, const float dt);
        ~GraphicElements() {}

        // Acessors
        bool IsWindowOpen();
        bool PollEvents(bool boolVar);

        // Functions
        void DrawBond(MyMath::Vector p1Pos, MyMath::Vector p2Pos);
        void DrawNode(MyMath::Vector pos, sf::Color color);
        void Clear() {window.clear(sf::Color::Black);}
        void Display();

        // Global variables
        sf::RenderWindow window;  
        sf::CircleShape circle; // It's used for drawing the particles
        sf::RectangleShape rect; // Represents the force being applied
        float scale;

    private:
        // Local variables
        // Clock related variables
        const float frame_dt = 1000000.f/60.f; // Microseconds
        float simulation_dt;
        sf::Clock clock;
    };
}

#endif