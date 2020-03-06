#include "Interactions.hpp"

namespace StructSim
{
    // Functions
    void SimpleBond::Act(MyGraphics::GraphicElements *graphics, float dt)
    {
        /* Applies the force F = k*(r-r_equilbrium)
        * where r is the vector connecting particle p2 to p1 
        * and r_equilibrium is the vector giving the point
        * of equilibrium of the spring
        */
       
        MyMath::Vector r = MyMath::vectorGetSub(p1->GetPosition(), p2->GetPosition());

        float r_mag = MyMath::vectorGetMag(r);
        MyMath::Vector r_hat = MyMath::normalize(r);
        MyMath::Vector equilibrium_r = MyMath::vectorSetScale(r_hat, eqDist);
        
        MyMath::Vector force = MyMath::vectorSetScale(vectorGetSub(r, equilibrium_r), k);

        p2->ApplyForce(force, dt);
        p1->ApplyForce(MyMath::vectorSetScale(force, -1), dt);

        graphics->DrawBond(p1->GetPosition(), p2->GetPosition());
    }
}