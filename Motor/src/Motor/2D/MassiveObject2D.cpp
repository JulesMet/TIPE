#include "Motor\2D\MassiveObject2D.h"


namespace Motor {
    MassiveObject2D::MassiveObject2D(double mass, Vec2<int> pos, Vec2<double> v0, Vec2<double> a0)
        : m_Mass(mass), m_Pos(pos), m_Velocity(v0), m_Acceleration(a0)
    {

    }

    MassiveObject2D::MassiveObject2D(const MassiveObject2D& other)
        : m_Mass(other.m_Mass), m_Pos(other.m_Pos), m_Velocity(other.m_Velocity), m_Acceleration(other.m_Acceleration)
    {
    }

    MassiveObject2D::~MassiveObject2D()
    {
    }

    void MassiveObject2D::Update(float ts)
    {
    }

    void MassiveObject2D::OnRender() const
    {
    }
}