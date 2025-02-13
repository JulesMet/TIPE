#include "Motor\2D\Planet2D.h"

namespace Motor {
    Planet2D::Planet2D(double mass, Vec2<int> center, double radius, Vec2<double> v0, Vec2<double> a0)
        : MassiveObject2D{ mass, center, v0, a0 }, m_Radius(radius)
    {
    }

    Planet2D::Planet2D(const Planet2D& p)
        : m_Radius(p.m_Radius), MassiveObject2D{ p.m_Mass, p.m_Pos, p.m_Velocity, p.m_Acceleration }
    {
    }

    Planet2D::~Planet2D()
    {
        // need to handle everything
    }

    void Planet2D::Update(float ts)
    {
        // look for forces
        // apply the resultant to the acceleration 
        // ( WARNING : do not ADD the forces to the acceleration / velocity, Newton's laws is   acceleration IS EQUAL TO the sum of forces)

        // check for potential collisions

        // if there is no collisions, let the physics make its job
        // 
        // if there is collisions, delete both planets  ---->  the desctructor need to clear everything potentially including rendering stuff

        // apply acceleration to velocity
        // apply velocity to position

        // done ?
    }

    void Planet2D::OnRender() const
    {
        // rendering stuff
    }
}