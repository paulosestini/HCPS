#include "InputHandler.hpp"

namespace hc
{
    void InputHandler::update(sf::RenderWindow *window)
    {
        isSelectionModeOn = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
        sf::Event event;
        while(window->pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window->close();
            }
            if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::F)
                    isFixModeOn = true;
                if(event.key.code == sf::Keyboard::U)
                    isUnfixModeOn = true;
            }
            if (event.type == sf::Event::KeyReleased)
            {
                if(event.key.code == sf::Keyboard::F)
                    isFixModeOn = false;
                if(event.key.code == sf::Keyboard::U)
                    isUnfixModeOn = false;
            }
        }

        mousePos = window->mapPixelToCoords((sf::Mouse::getPosition(*window)))/SPATIAL_SCALE;
    }
}