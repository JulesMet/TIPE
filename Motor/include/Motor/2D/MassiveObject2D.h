#pragma once

#include "Motor/Entity.h"
#include "Vector.h"

namespace Motor {
    class MassiveObject2D : public Entity
    {
    protected:
        const double m_Mass;
        Vec2<int> m_Pos;
        Vec2<double> m_Velocity;
        Vec2<double> m_Acceleration;

    public:

        MassiveObject2D(double mass, Vec2<int> pos, Vec2<double> initial_speed = Vec2<double>(0, 0), Vec2<double> initial_acceleration = Vec2<double>(0, 0));
        MassiveObject2D(const MassiveObject2D& massiveObject_2D);

        virtual ~MassiveObject2D();

        virtual void Update(float ts);
        virtual void OnRender() const;

    };

}

