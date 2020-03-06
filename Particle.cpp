#include "StructureElement.hpp"

namespace StructSim
{
    // Constructor
    Particle::Particle(MyMath::Vector initPos, MyMath::Vector initVel, float initMass)
    {
        this->data.pos = initPos;
        this->data.vel = initVel;
        this->data.mass = initMass;
    }

    //Accesors
    MyMath::Vector Particle::GetPosition()
    {
        return data.pos;
    }

    void Particle::SetPosition(MyMath::Vector newPos)
    {
        data.pos = newPos;
    }

    void Particle::Move(MyMath::Vector dPos)
    {
        data.pos = MyMath::vectorGetAdd(data.pos, dPos);
    }

    MyMath::Vector Particle::GetVelocity()
    {
        return data.vel;
    }

    void Particle::SetVelocity(MyMath::Vector newVel)
    {
        data.vel = newVel;
    }

    void Particle::Accelerate(MyMath::Vector dVel)
    {
        data.vel = MyMath::vectorGetAdd(data.vel, dVel);
    }

    //Functions
    void Particle::ApplyForce(MyMath::Vector force, float dt)
    {   
        // Changes velocity according to the force applied
        MyMath::Vector acc = MyMath::vectorSetScale(force, data.mass);
        Accelerate(MyMath::vectorSetScale(acc, dt));
    }

    void Particle::Update(MyGraphics::GraphicElements *graphics, float dt)
    {   
        // Updating position
        Move(MyMath::vectorSetScale(data.vel, dt));

        graphics->DrawNode(data.pos, sf::Color::White);
    }
}