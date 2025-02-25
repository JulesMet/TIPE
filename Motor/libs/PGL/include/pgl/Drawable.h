#pragma once

#include "pgl/openGL/Renderer.h"

#include "glm/glm.hpp"

#include <memory>

namespace pgl {

	class Drawable
	{
	protected :
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VBO;
		std::unique_ptr<IndexBuffer> m_IBO;

		std::unique_ptr<Shader> m_Shader;

		Renderer m_renderer;

		glm::mat4 m_Proj, m_View, m_Model;
		glm::mat4 m_MVP;


	public :
		virtual void OnRender() const;
		virtual void OnImGuiRender();

	};
};