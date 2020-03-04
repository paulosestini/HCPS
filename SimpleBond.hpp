#pragma once

#include "StructureElement.hpp"

namespace StructSim
{
    class SimpleBond : public StructureElement::Bond
    {
    public:
        SimpleBond(StructureElement::Particle* p1, StructureElement::Particle* p2, float equilibriumDistance);

        StructureElement::Particle *GetParticle1Ref();
        StructureElement::Particle *GetParticle2Ref();

        void Act(float dt); // Applies the forces

        StructureElement::Particle* _p1;
        StructureElement::Particle* _p2;

    private:
        float _equilibriumDistance;
        static constexpr float _k = 10;

    };
}