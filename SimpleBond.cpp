#include "SimpleBond.hpp"
/* ---class "Force" definitions--- */

namespace StructSim
{
    SimpleBond::SimpleBond(StructureElement::Particle* p1, StructureElement::Particle* p2, float equilibriumDistance)  : Bond(), _p1( p1 ) , _p2( p2 ), _equilibriumDistance( equilibriumDistance )
    {
        
    }

    StructureElement::Particle *SimpleBond::GetParticle1Ref()
    {
        return _p1;
    }

    StructureElement::Particle *SimpleBond::GetParticle2Ref()
    {
        return _p2;
    }

    void SimpleBond::Act(float dt)
    {
        /* Applies the force F = k*(r-r_equilbrium)
        * where r is the vector connecting particle p2 to p1 
        * and r_equilibrium is the vector giving the point
        * of equilibrium of the spring
        */
        MyMath::Vector r = MyMath::vectorGetSub(_p1->GetPosition(), _p2->GetPosition());

        float r_mag = MyMath::vectorGetMag(r);
        MyMath::Vector r_hat = MyMath::normalize(r);
        MyMath::Vector equilibrium_r = MyMath::vectorSetScale(r_hat, _equilibriumDistance);
        
        MyMath::Vector force = MyMath::vectorSetScale(vectorGetSub(r, equilibrium_r), _k);

        _p2->ApplyForce(force, dt);
        _p1->ApplyForce(MyMath::vectorSetScale(force, -1), dt);
    }
}