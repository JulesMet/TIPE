#pragma once

#include "Drawable.h"

#include "glm/glm.hpp"

namespace pgl {

    class Circle : public Drawable
    {
    protected:
        float m_Radius;

        glm::vec2 m_Center;
        
    public:

        Circle(glm::vec2 center, float radius);


        virtual void OnRender() const override;
        virtual void OnImGuiRender() override;
    };

};