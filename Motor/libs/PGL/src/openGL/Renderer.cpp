#include "Renderer.h"

#include <iostream>

/*void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* functionName, const char* fileName, int lineNumber)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (error " << error << ")\n\tfunction : " << functionName
            << "\n\t" << fileName << ": line." << lineNumber << std::endl;
        return false;
    }
    return true;
}*/

void Renderer::Clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind();
    va.Bind();
    //ib.Bind();

    glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}