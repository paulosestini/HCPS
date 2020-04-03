#include "Renderer.hpp"

namespace hc
{
    /* --- Constructor --- */

    Renderer::Renderer(const double scale, const double dt)
    {
        window.create(sf::VideoMode(SCREEN_WIDTH*scale, SCREEN_HEIGHT*scale), "Simulation Box", sf::Style::Close | sf::Style::Titlebar);
        sf::View view = window.getView();
        view.setCenter(0, SCREEN_HEIGHT*scale/2.f);

        // The box boundaries definition
        boundBox.setSize(sf::Vector2f(BOUND_BOX_WIDTH*scale, BOUND_BOX_HEIGHT*scale));
        boundBox.setFillColor(sf::Color::Black);
        boundBox.setPosition(BOUND_BOX_POS_X*scale, BOUND_BOX_POS_Y*scale);

        clockFont.loadFromFile("Resources/Fonts/arial.ttf");
        clockText.setFont(clockFont);
        clockText.setFillColor(sf::Color::Blue);

        this->scale = scale;
        virtual_dt = dt*1000000;
    }

    /* --- Acessors --- */

    bool Renderer::isWindowOpen()
    {
        return window.isOpen();
    }

    /* --- Functions --- */

    void Renderer::clear()
    {
        window.clear(sf::Color::White);
        window.draw(boundBox);
    }

    void Renderer::drawBond(MathUtils::Vector force, double dt, MathUtils::Vector p1Pos, MathUtils::Vector p2Pos, int alpha)
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

    void Renderer::render(ParticleSystem *pSystem, sf::CircleShape *freeNodeShape, sf::CircleShape *fixdNodeShape, sf::CircleShape *slctNodeShape, double dt, int bondTransparency)
    {
        for (auto bond : pSystem->bonds)
        {
            drawBond(bond->calculatedForce, dt, bond->p1->getPosition(), bond->p2->getPosition(), bondTransparency);
        }

        for (auto particle : pSystem->particles)
        {
            freeNodeShape->setPosition(particle->getPosition().x*scale, particle->getPosition().y*scale);
            window.draw(*freeNodeShape);
        }
        if (pSystem->alreadySelected)
        {
            slctNodeShape->setPosition(pSystem->selectedParticle->getPosition().x*scale, pSystem->selectedParticle->getPosition().y*scale);
            window.draw(*slctNodeShape);
        }
        for (auto particle : (*pSystem).fixedParticles)
        {
            fixdNodeShape->setPosition(particle->getPosition().x*scale, particle->getPosition().y*scale);
            window.draw(*fixdNodeShape);
        }
    }

    void Renderer::drawClock()
    {
        clockText.setString(std::to_string((int)virtualTime));
        window.draw(clockText);
    }

    void Renderer::display()
    {
        virtualTime += virtual_dt;
        if (clock.getElapsedTime().asMicroseconds() >= frame_dt)
        {
            window.display();
            clock.restart();
        }
    }
}
