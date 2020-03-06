#include "GraphicElements.hpp"
#include <iostream>

namespace MyGraphics
{
    // Constructor
    GraphicElements::GraphicElements(int width, int height, const float circleRadius, const float scale, const float dt)
    {
        window.create(sf::VideoMode(800, 800), "Simulation", sf::Style::Close | sf::Style::Titlebar);
        circle.setRadius(circleRadius);
        rect.setSize(sf::Vector2f(100, 5));
        rect.setFillColor(sf::Color::Yellow);
        this->scale = scale;
        simulation_dt = dt*1000000;
    }

    // Acessors
    bool GraphicElements::IsWindowOpen()
    {
        return window.isOpen();
    }

    bool GraphicElements::PollEvents(bool boolVar)
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
                if(event.key.code == sf::Keyboard::F) boolVar = !boolVar;
            }
        }
        return boolVar;
    }

    // Functions
    void GraphicElements::DrawBond(MyMath::Vector p1Pos, MyMath::Vector p2Pos)
    {
        sf::Vertex line[2] = {sf::Vector2f(0, 0), sf::Vector2f(0, 0)}; // It's used for drawing the lines
        line[0].position = sf::Vector2f(p1Pos.x*scale+circle.getRadius(), 
                                        p1Pos.y*scale+circle.getRadius());
        line[1].position = sf::Vector2f(p2Pos.x*scale+circle.getRadius(), 
                                        p2Pos.y*scale+circle.getRadius());
        window.draw(line, 2, sf::Lines);  
    }

    void GraphicElements::DrawNode(MyMath::Vector pos, sf::Color color)
    {
        circle.setFillColor(color);
        circle.setPosition(sf::Vector2f(pos.x*scale, pos.y*scale));
        window.draw(circle);
    }

    void GraphicElements::Display()
    {
        if (clock.getElapsedTime().asMicroseconds() >= frame_dt)
        {
            window.display();
            clock.restart();
        }
    }
}