#include "TestViewImage.hpp"

#include <glad/glad.h>
#include "OpenGLDebug.hpp"
#include <imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Quad.hpp"

namespace test {
	TestViewImage::TestViewImage() {
        int vp[4];
        GLCall(glGetIntegerv(GL_VIEWPORT, vp));
        m_width = vp[2];
        m_height = vp[3];
        LOG(INFO) << "Window size = (" << m_width << "x" << m_height << ")" << std::endl;

        //set dynamic vertex buffer
        // 3D point, RGBA color, 2D TexMap Point, Tex index, mvp index
        auto q0 = QuadNs::createQuad();
        m_vBuf = QuadNs::getVertexBuf(q0, false, true, false, false);

        //std::cout << "m_vBuf.capacity() = " << m_vBuf.capacity() << std::endl;
        //std::cout << "m_vBuf.size() = " << m_vBuf.size() << std::endl;

        //Indices buffer
        Indices indices = QuadNs::getIndices();

        m_texture1 = std::make_unique<Texture>("res/textures/_MG_1005.bmp");

        m_shader = std::make_unique<Shader>("res/shaders/basicTexture.shader");
        GLCall(glUseProgram(m_shader->getID()));

        m_va = std::make_unique<VertexArray>();
        m_ib = std::make_unique<IndexBuffer>(indices);

        m_vb = std::make_unique<VertexBuffer>(nullptr, sizeof(Vertex) * 1000);
        // Start Center of screen
        m_hw = m_width * 0.5f;
        m_hh = m_height * 0.5f;

        float qw = m_hw * 0.5f;

        m_translationA = { 0.0f, 0.0f, 0.0f };

        // Set Matrices
        m_ident = glm::mat4(1.0f);
        m_scale = glm::scale(m_ident, glm::vec3(m_width, m_height, 1.0f));
        m_proj = glm::ortho(-m_hw, m_hw, -m_hh, m_hh, -1.0f, 1.0f); // Orthographic Projection
        m_view = glm::translate(m_ident, glm::vec3(0.0f, 0.0f, 0.0f));
        glm::mat4 m_mvp = m_proj * m_view * m_model; // reversed from m_mvp due to opengl and memory m_layout for math

        // Setup Blending
        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        // Setup a Vertex Array
        m_va->bind();
        //m_layout.push<float>(6);
        m_layout.push<float>(3); // vertex
        //m_layout.push<float>(4); // color
        m_layout.push<float>(2); // texture mapping
        //m_layout.push<float>(1); // texture id
        //m_layout.push<float>(1); // mvp id
        m_va->addBuffer(*m_vb, m_layout);

        // Setup a Shader
        m_shader->bind();

        // Unbind once setup
        m_va->unbind();
        m_vb->unbind();
        m_ib->unbind();
        m_shader->unbind();
	}

    TestViewImage::~TestViewImage() {
	}

	void TestViewImage::onUpdate(float deltaTime) {
	}
	void TestViewImage::onRender() {
        GLCall(glClearColor(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]));
        m_renderer.clear(); //GLCall(glClear(GL_COLOR_BUFFER_BIT));

        {
            m_texture1->bind();
            m_vb->bind();

            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(m_vBuf[0]) * m_vBuf.size(), m_vBuf.data());

            glBindTextureUnit(0, m_texture1->getID());

            m_model = glm::translate(m_ident, m_translationA) * m_scale;
            
            m_mvp = m_proj * m_view * m_model;

            m_shader->bind();

            m_shader->setUniformMat4f("u_MVP", m_mvp);

            m_renderer.draw(*m_va, *m_ib, *m_shader);
            m_shader->unbind();

            m_texture1->unbind();
        }
    }

	//void TestViewImage::onImGuiRender() {
	//	{
	//		ImGui::SliderFloat("Image 1 - X Translation", &m_translationA.x, -m_hw, m_hw);            // Edit 1 float using a slider from 0.0f to 1.0f
	//		ImGui::SliderFloat("Image 1 - Y Translation", &m_translationA.y, -m_hh, m_hh);            // Edit 1 float using a slider from 0.0f to 1.0f
	//		//ImGui::SliderFloat("Z Translation", &translation.z, -hz, hz);            // Edit 1 float using a slider from 0.0f to 1.0f
	//		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	//	}
	//}
}
