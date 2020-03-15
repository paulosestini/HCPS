#include "Interactions.hpp"

namespace hc
{
    /* --- Functions --- */
    
    void SimpleBond::act(double dt)
    {
        /*
        * Applies the force F = k*(r-r_equilbrium)
        * where r is the vector connecting particle p2 to p1 
        * and r_equilibrium is the vector giving the point
        * of equilibrium of the spring
        */

        MathUtils::Vector force = calculateForce();
        


        p2->applyForce(force);
        p1->applyForce(MathUtils::vectorScale(force, -1));
    }
    MathUtils::Vector SimpleBond::calculateForce()
    {
        MathUtils::Vector r = MathUtils::vectorSub(p1->getPosition(), p2->getPosition());
        MathUtils::Vector v = MathUtils::vectorSub(p1->getVelocity(), p2->getVelocity());

        double r_mag = MathUtils::vectorMag(r);
        MathUtils::Vector r_hat = MathUtils::normalize(r);
        MathUtils::Vector equilibrium_r = MathUtils::vectorScale(r_hat, eqDist);

        MathUtils::Vector axial_v = MathUtils::vectorProj(v,r);
        
        MathUtils::Vector F_el = MathUtils::vectorScale(vectorSub(r, equilibrium_r), k);
        MathUtils::Vector F_at = MathUtils::vectorScale(axial_v, c);
        calculatedForce = MathUtils::vectorAdd(F_el, F_at);
        return calculatedForce;
    }
}