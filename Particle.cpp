#include "StructureElement.hpp"
/* ---class "Particle" definitions--- */

namespace StructSim
{
    StructureElement::Particle::Particle(MyMath::Vector initPos, MyMath::Vector initVel, float initMass)
    {
        this->_data.pos = initPos;
        this->_data.vel = initVel;
        this->_data.mass = initMass;
    }

    //Accesors
    MyMath::Vector StructureElement::Particle::GetPosition()
    {
        return _data.pos;
    }

    void StructureElement::Particle::SetPosition(MyMath::Vector newPos)
    {
        _data.pos = newPos;
    }

    void StructureElement::Particle::Move(MyMath::Vector dPos)
    {
        _data.pos = MyMath::vectorGetAdd(_data.pos, dPos);
    }

    MyMath::Vector StructureElement::Particle::GetVelocity()
    {
        return _data.vel;
    }

    void StructureElement::Particle::SetVelocity(MyMath::Vector newVel)
    {
        _data.pos = newVel;
    }

    void StructureElement::Particle::Accelerate(MyMath::Vector dVel)
    {
        _data.pos = MyMath::vectorGetAdd(_data.vel, dVel);
    }

    //Functions
    void StructureElement::Particle::ApplyForce(MyMath::Vector force, float dt)
    {   
        // Changes velocity according to the force applied
        MyMath::Vector acc = MyMath::vectorSetScale(force, _data.mass);
        Accelerate(MyMath::vectorSetScale(acc, dt));
    }

    void StructureElement::Particle::Update(float dt)
    {   
        // Some dissipation of energy
        Accelerate(MyMath::vectorSetScale(MyMath::vectorSetScale(_data.vel, MyMath::vectorGetMag(_data.vel)), -0.9));
        
        // Updating position
        Move(MyMath::vectorSetScale(_data.vel, dt));

    }
}