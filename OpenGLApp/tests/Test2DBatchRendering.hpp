#pragma once

#include "Test.hpp"
#include <vector>
//#include <array>
#include <memory>
#include "glm/glm.hpp"

#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "Renderer.hpp"
#include "Shader.hpp"
#include "Texture.hpp"


namespace test {
	class Test2DBatchRendering : public Test {
	public:
		Test2DBatchRendering();
		~Test2DBatchRendering();

		void onUpdate(float deltaTime) override;
		void onRender() override;
		void onImGuiRender() override;
	private:
		float m_clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

        VertexBufferLayout m_layout;

        std::unique_ptr<VertexArray> m_va;

        //VertexBuffer* m_vb;
        //std::unique_ptr<VertexBuffer> m_vb;

        std::unique_ptr<IndexBuffer> m_ib;
        std::unique_ptr<Shader> m_shader;

        std::unique_ptr<Texture> m_texture1;
        std::unique_ptr<Texture> m_texture2;

        Renderer m_renderer;

        glm::mat4 m_ident;
        glm::mat4 m_scale;
        glm::mat4 m_model;
        glm::mat4 m_view;
        glm::mat4 m_proj;
        glm::mat4 m_mvp;

        unsigned int m_width;
        unsigned int m_height;

        float m_hw = 0;
        float m_hh = 0;

        glm::vec3 m_translationA;
        glm::vec3 m_translationB;

	};
}
