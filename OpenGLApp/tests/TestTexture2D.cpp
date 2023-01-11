#include "TestTexture2D.hpp"

#include <glad/glad.h>
#include "OpenGLDebug.hpp"
#include <imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace test {
	TestTexture2D::TestTexture2D() {
		int vp[4];
		GLCall(glGetIntegerv(GL_VIEWPORT, vp));
		m_width = vp[2];
		m_height = vp[3];

		LOG(INFO) << "Window size = (" << m_width << "x" << m_height << ")" << std::endl;

		// 2D point, 2D TexMap Point
		std::vector<float> vertexBuf = {
			-0.5f, -0.5f, 0.0f, 0.0f, //0
			 0.5f, -0.5f, 1.0f, 0.0f, //1
			 0.5f,  0.5f, 1.0f, 1.0f, //2
			-0.5f,  0.5f, 0.0f, 1.0f  //3
		};

		//Indices buffer
		std::vector<unsigned int> indices = {
			0,1,2,
			2,3,0
		};

		m_texture1 = std::make_unique<Texture>("res/textures/Planning-And-Probing-1.jpg");
		m_texture2 = std::make_unique<Texture>("res/textures/jrrt.png");

		m_shader  = std::make_unique<Shader>("res/shaders/basic.shader");
		m_va      = std::make_unique<VertexArray>();
		m_ib      = std::make_unique<IndexBuffer>(indices);

		VertexBuffer vb(vertexBuf);

		// Start Center of screen
		m_hw = m_width  * 0.5f; // m_width/2.0f
		m_hh = m_height * 0.5f; // m_height/2.0f

		float qw = m_hw * 0.5f;

		m_translationA = { -qw, 0.0f, 0.0f };
		m_translationB = {  qw, 0.0f, 0.0f };

		// Set Matrices
		m_ident = glm::mat4(1.0f);
		m_scale = glm::scale(m_ident, glm::vec3(300.0f));
		m_proj  = glm::ortho(-m_hw, m_hw, -m_hh, m_hh, -1.0f, 1.0f); // Orthographic Projection
		m_view  = glm::translate(m_ident, glm::vec3(0.0f, 0.0f, 0.0f));

		// Setup Blending
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		// Setup a Vertex Array
		m_va->bind();
		m_layout.push<float>(2); // vertices
		m_layout.push<float>(2); // texture mapping
		m_va->addBuffer(vb, m_layout);

		// Setup a Shader
		m_shader->bind();

		// Unbind once setup
		m_va->unbind();
		vb.unbind();
		m_ib->unbind();
		m_shader->unbind();

	}
	TestTexture2D::~TestTexture2D() {
	}

	void TestTexture2D::onUpdate(float deltaTime) {
	}
	void TestTexture2D::onRender() {
		GLCall(glClearColor(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]));
		m_renderer.clear();
		//GLCall(glClear(GL_COLOR_BUFFER_BIT));

		{
			m_texture1->bind();
			m_model = glm::translate(m_ident, m_translationA) * m_scale;
			m_mvp = m_proj * m_view * m_model;
			m_shader->bind();
			m_shader->setUniformMat4f("u_MVP", m_mvp);
			m_renderer.draw(*m_va, *m_ib, *m_shader);
			m_shader->unbind();
			m_texture1->unbind();
		}

		{
			m_texture2->bind();
			m_model = glm::translate(m_ident, m_translationB) * m_scale;
			m_mvp = m_proj * m_view * m_model;
			m_shader->bind();
			m_shader->setUniformMat4f("u_MVP", m_mvp);
			m_renderer.draw(*m_va, *m_ib, *m_shader);
			m_shader->unbind();
			m_texture2->unbind();
		}
	}

	void TestTexture2D::onImGuiRender() {
		{
			ImGui::SliderFloat("Image 1 - X Translation", &m_translationA.x, -m_hw, m_hw);            // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::SliderFloat("Image 1 - Y Translation", &m_translationA.y, -m_hh, m_hh);            // Edit 1 float using a slider from 0.0f to 1.0f
			//ImGui::SliderFloat("Z Translation", &translation.z, -hz, hz);            // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::SliderFloat("Image 2 - X Translation", &m_translationB.x, -m_hw, m_hw);            // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::SliderFloat("Image 2 - Y Translation", &m_translationB.y, -m_hh, m_hh);            // Edit 1 float using a slider from 0.0f to 1.0f
			//ImGui::ColorEdit3("clear color", (float*)&m_clearColor); // Edit 3 floats representing a color
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		}
	}
}
