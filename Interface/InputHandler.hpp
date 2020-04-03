#pragma once

#include <iostream>

#include "../DEFINITIONS.hpp"
#include "../Utils/MathUtils.hpp"

#include <SFML/Graphics.hpp>

namespace hc
{
    class InputHandler
    {
    public:
        bool isSelectionModeOn = false;
        bool isUnfixModeOn = false;
        bool isFixModeOn = false;
        sf::Vector2f mousePos;

        void update(sf::RenderWindow *window);
    };
}