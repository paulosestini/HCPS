#pragma once

#include "MathUtils.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace hc
{
    struct Inputs
    {
        bool isForce1Applied = false;
        bool isForce2Applied = false;
        bool isMouseClicked = false;
        sf::Vector2f mousePos;
    };

    class GraphicElements
    {
    public:
        // Constructor/Destructor
        GraphicElements(int width, int height, const double circleRadius, const double scale, const double dt);
        ~GraphicElements() {}

        // Acessors
        bool isWindowOpen();
        void pollEvents(Inputs* inputs);
        void updateMousePos(Inputs* inputs);
        void update(Inputs* inputs);

        // Functions
        void drawForce(double x, double y, float radians);
        void drawBond(MathUtils::Vector force, MathUtils::Vector p1Pos, MathUtils::Vector p2Pos);
        void drawFreeNode(MathUtils::Vector pos);
        void drawFixedNode(MathUtils::Vector pos);
        void drawSelectedNode(MathUtils::Vector pos);
        void drawClock();
        void clear() {window.clear(sf::Color::Black);}
        void display();

        // Global variables
        sf::RenderWindow window;  
        sf::CircleShape circleWhite; // It's used for drawing the free particles
        sf::CircleShape circleRed; // It's used for drawing the static particles
        sf::CircleShape circleYellow; // It's used for drawing the selected particles
        sf::RectangleShape rect; // Represents the force being applied
        sf::Font clockFont;
        sf::Text clockText;
        double scale;

    private:
        // Local variables
        // Clock related variables
        float colorK = 1e-20;
        const double frame_dt = 1000000.f/60.f; // Microseconds
        double virtual_dt, virtualTime = 0.f;
        sf::Clock clock;
    };
}
