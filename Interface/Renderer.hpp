#pragma once

#include <iostream>

#include "../DEFINITIONS.hpp"
#include "../Utils/MathUtils.hpp"
#include "../Simulation/ParticleSystem.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace hc
{
    class Renderer
    {
    public:
        // Constructor/Destructor
        Renderer(const double scale, const double dt);
        ~Renderer() {}

        // Acessors
        bool isWindowOpen();

        // Functions
        void clear();
        void drawBond(MathUtils::Vector force, double dt, MathUtils::Vector p1Pos, MathUtils::Vector p2Pos, int alpha);
        void render(ParticleSystem *pSystem, sf::CircleShape *freeNodeShape, sf::CircleShape *fixdNodeShape, sf::CircleShape *slctNodeShape, double dt, int bondTransparency);
        void drawClock();
        void display();

        // Global variables
        sf::RenderWindow window;
        sf::RectangleShape boundBox;   // It's used to define the box boundaries
        sf::Font clockFont;
        sf::Text clockText;
        double scale;

    private:
        // Local variables
        // Clock related variables
        float colorK = 4e-4;
        const double frame_dt = 1000000.f/60.f; // Microseconds
        double virtual_dt, virtualTime = 0.f;
        sf::Clock clock;
    };
}
