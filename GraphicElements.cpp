#include "GraphicElements.hpp"
#include <cmath>

#include <iostream>
#include <string> 

namespace hc
{
    /* --- Constructor --- */

    GraphicElements::GraphicElements(const double scale, const double dt)
    {
        window.create(sf::VideoMode(SCREEN_WIDTH*SPATIAL_SCALE, SCREEN_HEIGHT*SPATIAL_SCALE), "Simulation Box", sf::Style::Close | sf::Style::Titlebar);
        sf::View view = window.getView();
        view.setCenter(0, SCREEN_HEIGHT*SPATIAL_SCALE/2.f);
        //window.setView(view);

        // The box boundaries definition
        boundBox.setSize(sf::Vector2f(BOUND_BOX_WIDTH*SPATIAL_SCALE, BOUND_BOX_HEIGHT*SPATIAL_SCALE));
        boundBox.setFillColor(sf::Color::Black);
        boundBox.setPosition(BOUND_BOX_POS_X*SPATIAL_SCALE, BOUND_BOX_POS_Y*SPATIAL_SCALE);

        freeNodeShape.setRadius(NODE_SHAPE_RADIUS);
        freeNodeShape.setOrigin(NODE_SHAPE_RADIUS, NODE_SHAPE_RADIUS);
        freeNodeShape.setFillColor(FREE_NODE_COLOR);

        fixdNodeShape.setRadius(NODE_SELECTION_RADIUS*SPATIAL_SCALE);
        fixdNodeShape.setOrigin(NODE_SELECTION_RADIUS*SPATIAL_SCALE, NODE_SELECTION_RADIUS*SPATIAL_SCALE);
        fixdNodeShape.setFillColor(FIXD_NODE_COLOR);

        slctNodeShape.setRadius(NODE_SELECTION_RADIUS*SPATIAL_SCALE);
        slctNodeShape.setOrigin(NODE_SELECTION_RADIUS*SPATIAL_SCALE, NODE_SELECTION_RADIUS*SPATIAL_SCALE);
        slctNodeShape.setFillColor(SLCT_NODE_COLOR);

        clockFont.loadFromFile("Fonts/arial.ttf");
        clockText.setFont(clockFont);
        clockText.setFillColor(sf::Color::Blue);

        this->scale = scale;
        virtual_dt = dt*1000000;
    }

    /* --- Acessors --- */

    bool GraphicElements::isWindowOpen()
    {
        return window.isOpen();
    }

    void GraphicElements::pollEvents(Inputs* inputs)
    {
        inputs->isSelectionModeOn = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
            if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::F)
                    inputs->isFixModeOn = true;
                if(event.key.code == sf::Keyboard::U)
                    inputs->isUnfixModeOn = true;
            }
            if (event.type == sf::Event::KeyReleased)
            {
                if(event.key.code == sf::Keyboard::F)
                    inputs->isFixModeOn = false;
                if(event.key.code == sf::Keyboard::U)
                    inputs->isUnfixModeOn = false;
            }
        }
    }

    void GraphicElements::updateMousePos(Inputs* inputs)
    {
        inputs->mousePos = window.mapPixelToCoords((sf::Mouse::getPosition(window)))/SPATIAL_SCALE;
    }

    void GraphicElements::update(Inputs* inputs)
    {
        pollEvents(inputs);
        updateMousePos(inputs);
    }

    /* --- Functions --- */

    void GraphicElements::drawBond(MathUtils::Vector force, MathUtils::Vector p1Pos, MathUtils::Vector p2Pos, int alpha)
    {
        double R, G, B;
        if(vectorDot(force, vectorSub(p2Pos, p1Pos)) > 0)
        {
            R = 255;
            G = 255*(1-std::tanh(colorK*vectorMag(force)));
            B = 255*(1-std::tanh(colorK*vectorMag(force)));
        }
        else
        {
            R = 255*(1-std::tanh(colorK*vectorMag(force)));
            G = 255*(1-std::tanh(colorK*vectorMag(force)));
            B = 255;
        }
        sf::Color color(R, G, B, alpha);

        sf::Vertex line[2] = {sf::Vector2f(0, 0), sf::Vector2f(0, 0)}; // It's used for drawing the lines
        line[0].position = sf::Vector2f(p1Pos.x*scale, 
                                        p1Pos.y*scale);
        line[1].position = sf::Vector2f(p2Pos.x*scale, 
                                        p2Pos.y*scale);
        line[0].color = color;
        line[1].color = color;
        window.draw(line, 2, sf::Lines);  
    }

    void GraphicElements::drawFreeNode(MathUtils::Vector pos)
    {
        freeNodeShape.setPosition(sf::Vector2f(pos.x*scale, pos.y*scale));
        window.draw(freeNodeShape);
    }

    void GraphicElements::drawFixedNode(MathUtils::Vector pos)
    {
        fixdNodeShape.setPosition(sf::Vector2f(pos.x*scale, pos.y*scale));
        window.draw(fixdNodeShape);
    }

    void GraphicElements::drawSelectedNode(MathUtils::Vector pos)
    {
        slctNodeShape.setPosition(sf::Vector2f(pos.x*scale, pos.y*scale));
        window.draw(slctNodeShape);
    }

    void GraphicElements::drawClock()
    {
        clockText.setString(std::to_string((int)virtualTime));
        window.draw(clockText);
    }

    void GraphicElements::display()
    {
        virtualTime += virtual_dt;
        if (clock.getElapsedTime().asMicroseconds() >= frame_dt)
        {
            window.display();
            clock.restart();
        }
    }
}