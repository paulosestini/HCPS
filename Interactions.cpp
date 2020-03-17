#include "Interactions.hpp"

namespace hc
{
    /* --- Functions --- */

    bool SimpleBond::isBroken()
    {
        return false;
    }
    MathUtils::Vector SimpleBond::calculateForce()
    {
        /*
        * Applies the force F = k*(r-r_equilbrium) + c*(v perpendicular to r)
        * where r is the vector connecting particle p2 to p1, 
        * r_equilibrium is the vector giving the point of
        * equilibrium of the spring, and v is the relative
        * velocity between p2 and p1.
        */
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

    bool LimitedBond::isBroken()
    {
        return MathUtils::vectorMag(MathUtils::vectorSub(p1->getPosition(), p2->getPosition())) > maxDistFactor*eqDist;
    }
    MathUtils::Vector LimitedBond::calculateForce()
    {
        /*
        * Applies the force F = k*(r-r_equilbrium) + c*(v perpendicular to r)
        * where r is the vector connecting particle p2 to p1, 
        * r_equilibrium is the vector giving the point of
        * equilibrium of the spring, and v is the relative
        * velocity between p2 and p1.
        */
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