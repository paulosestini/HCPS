#pragma once

#include "DEFINITIONS.hpp"
#include "MathUtils.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace hc
{
    struct Inputs
    {
        bool isSelectionModeOn = false;
        bool isUnfixModeOn = false;
        bool isFixModeOn = false;
        sf::Vector2f mousePos;
    };

    class GraphicElements
    {
    public:
        // Constructor/Destructor
        GraphicElements(const double scale, const double dt);
        ~GraphicElements() {}

        // Acessors
        bool isWindowOpen();
        void pollEvents(Inputs* inputs);
        void updateMousePos(Inputs* inputs);
        void update(Inputs* inputs);

        // Functions
        void drawBond(MathUtils::Vector force, MathUtils::Vector p1Pos, MathUtils::Vector p2Pos, int alpha);
        void drawFreeNode(MathUtils::Vector pos);
        void drawFixedNode(MathUtils::Vector pos);
        void drawSelectedNode(MathUtils::Vector pos);
        void drawBoundaryRect(double top, double left, double width, double height);
        void drawClock();
        void clear() {window.clear(sf::Color::White); window.draw(boundBox);}
        void display();

        // Global variables
        sf::RenderWindow window;
        sf::RectangleShape boundBox;   // It's used to define the box boundaries
        sf::CircleShape freeNodeShape; // It's used for drawing the free particles
        sf::CircleShape fixdNodeShape; // It's used for drawing the static particles
        sf::CircleShape slctNodeShape; // It's used for drawing the selected particles
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
