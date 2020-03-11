#include "GraphicElements.hpp"
#include <cmath>

#include <iostream>
#include <string> 

namespace hc
{
    // Constructor
    GraphicElements::GraphicElements(int width, int height, const double circleRadius, const double scale, const double dt)
    {
        window.create(sf::VideoMode(width, height), "Simulation", sf::Style::Close | sf::Style::Titlebar);
        sf::View view = window.getView();
        view.setCenter(0, height/2.f);
        window.setView(view);

        this->scale = scale;
        virtual_dt = dt*1000000;

        rect.setSize(sf::Vector2f(100, 5));
        rect.setFillColor(sf::Color::White);
        rect.setOrigin(0, 2.5f);

        circleWhite.setRadius(circleRadius);
        circleWhite.setFillColor(sf::Color::White);

        circleRed.setRadius(circleRadius);
        circleRed.setFillColor(sf::Color::Red);

        circleYellow.setRadius(circleRadius);
        circleYellow.setFillColor(sf::Color::Yellow);

        clockFont.loadFromFile("Fonts/arial.ttf");
        clockText.setFont(clockFont);
        clockText.setFillColor(sf::Color::White);
        clockText.move(-width/2.f, 0);
    }

    // Acessors
    bool GraphicElements::isWindowOpen()
    {
        return window.isOpen();
    }

    void GraphicElements::pollEvents(Inputs* inputs)
    {
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
                    inputs->isForce1Applied = !inputs->isForce1Applied;
                if(event.key.code == sf::Keyboard::G)
                    inputs->isForce2Applied = !inputs->isForce2Applied;
            }
        }
    }

    void GraphicElements::updateMousePos(Inputs* inputs)
    {
        inputs->mousePos = window.mapPixelToCoords((sf::Mouse::getPosition(window)));
        inputs->isMouseClicked = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
    }

    void GraphicElements::update(Inputs* inputs)
    {
        pollEvents(inputs);
        updateMousePos(inputs);
    }

    // Functions
    void GraphicElements::drawForce(double x, double y, float radians)
    {
        rect.setPosition(sf::Vector2f(x, y));
        rect.setRotation(radians);
        window.draw(rect);
    }

    void GraphicElements::drawBond(MathUtils::Vector force, MathUtils::Vector p1Pos, MathUtils::Vector p2Pos)
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
        sf::Color color(R, G, B);

        sf::Vertex line[2] = {sf::Vector2f(0, 0), sf::Vector2f(0, 0)}; // It's used for drawing the lines
        line[0].position = sf::Vector2f(p1Pos.x*scale+circleWhite.getRadius(), 
                                        p1Pos.y*scale+circleWhite.getRadius());
        line[1].position = sf::Vector2f(p2Pos.x*scale+circleWhite.getRadius(), 
                                        p2Pos.y*scale+circleWhite.getRadius());
        line[0].color = color;
        line[1].color = color;
        window.draw(line, 2, sf::Lines);  
    }

    void GraphicElements::drawFreeNode(MathUtils::Vector pos)
    {
        circleWhite.setPosition(sf::Vector2f(pos.x*scale, pos.y*scale));
        window.draw(circleWhite);
    }

    void GraphicElements::drawFixedNode(MathUtils::Vector pos)
    {
        circleRed.setPosition(sf::Vector2f(pos.x*scale, pos.y*scale));
        window.draw(circleRed);
    }

    void GraphicElements::drawSelectedNode(MathUtils::Vector pos)
    {
        circleYellow.setPosition(sf::Vector2f(pos.x*scale, pos.y*scale));
        window.draw(circleYellow);
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