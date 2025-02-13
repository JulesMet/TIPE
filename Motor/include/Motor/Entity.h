#pragma once

#include "OpenGL\Renderer.h"

#include "pch.h"

namespace Motor {
    class Entity {
    protected:
        std::unique_ptr<VertexBuffer> m_VBO = nullptr;
        std::unique_ptr<VertexArray> m_VAO = nullptr;

        std::unique_ptr<IndexBuffer> m_IBO = nullptr;
        std::unique_ptr<Shader> m_Shader = nullptr;

    public:


        virtual ~Entity();

        virtual void Update(float ts);
        virtual void OnRender() const;
    };

}

