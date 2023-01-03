#include "Test2DBatchRendering.hpp"

#include <gl/glew.h>
#include "OpenGLDebug.hpp"
#include <imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace test {
	Test2DBatchRendering::Test2DBatchRendering() : m_ClearColor { 0.0f, 0.0f, 0.0f, 1.0f } {
		int vp[4];
		GLCall(glGetIntegerv(GL_VIEWPORT, vp));
		width = vp[2];
		height = vp[3];

		LOG(INFO) << "Window size = (" << width << "x" << height << ")" << std::endl;

		std::vector<float> vertexBuf = {
			-0.5f, -0.5f, 0.0f, 0.0f, //0
			 0.5f, -0.5f, 1.0f, 0.0f, //1
			 0.5f,  0.5f, 1.0f, 1.0f, //2
			-0.5f,  0.5f, 0.0f, 1.0f  //3
		};

		//Indices buffer
		unsigned int indices[6] = {
			0,1,2,
			2,3,0
		};

		// Scale //not: and Translate positions
		for (int i = 0; i < vertexBuf.size(); i += 4) {
			vertexBuf[i] *= 150;
			vertexBuf[i + 1] *= 150;
		}

		texture1 = std::make_unique<Texture>("res/textures/jrrt.png");
		texture2 = std::make_unique<Texture>("res/textures/Planning-And-Probing-1.jpg");

		shader  = std::make_unique<Shader>("res/shaders/basic.shader");
		va      = std::make_unique<VertexArray>();
		ib      = std::make_unique<IndexBuffer>(indices, 6);

		VertexBuffer vb(vertexBuf.data(), sizeof(vertexBuf[0]) * vertexBuf.size());

		// Start Center of screen
		hw = width * 0.5f;
		hh = height * 0.5f;

		float qw = hw * 0.5f;

		translationA = { -qw, 0.0f, 0.0f };
		translationB = {  qw, 0.0f, 0.0f };

		// Set Projection Matrix
		proj  = glm::ortho(-hw, hw, -hh, hh, -1.0f, 1.0f); // Orthographic Projection
		view  = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		//glm::mat4 mvp = model * view * proj; // not on screen because it is not reversed from mvp due to opengl and memory layout for math
		glm::mat4 mvp = proj * view * model; // reversed from mvp due to opengl and memory layout for math

		// Setup Blending
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		// Setup a Vertex Array
		va->bind();
		layout.push<float>(2); // vertices
		layout.push<float>(2); // texture mapping
		va->addBuffer(vb, layout);

		// Setup a Shader
		shader->bind();

		// Unbind once setup
		va->unbind();
		vb.unbind();
		ib->unbind();
		shader->unbind();
	}
	Test2DBatchRendering::~Test2DBatchRendering() {
	}

	void Test2DBatchRendering::onUpdate(float deltaTime) {
	}
	void Test2DBatchRendering::onRender() {
		GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
		renderer.clear(); //GLCall(glClear(GL_COLOR_BUFFER_BIT));

		{
			texture1->bind();
			model = glm::translate(glm::mat4(1.0f), translationA);
			mvp = proj * view * model;
			shader->bind();
			shader->setUniformMat4f("u_MVP", mvp);
			renderer.draw(*va, *ib, *shader);
			shader->unbind();
			texture1->unbind();
		}

		{
			texture2->bind();
			model = glm::translate(glm::mat4(1.0f), translationB);
			mvp = proj * view * model;
			shader->bind();
			shader->setUniformMat4f("u_MVP", mvp);
			renderer.draw(*va, *ib, *shader);
			shader->unbind();
			texture2->unbind();
		}
	}

	void Test2DBatchRendering::onImGuiRender() {
		{
			ImGui::SliderFloat("Image 1 - X Translation", &translationA.x, -hw, hw);            // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::SliderFloat("Image 1 - Y Translation", &translationA.y, -hh, hh);            // Edit 1 float using a slider from 0.0f to 1.0f
			//ImGui::SliderFloat("Z Translation", &translation.z, -hz, hz);            // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::SliderFloat("Image 2 - X Translation", &translationB.x, -hw, hw);            // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::SliderFloat("Image 2 - Y Translation", &translationB.y, -hh, hh);            // Edit 1 float using a slider from 0.0f to 1.0f
			//ImGui::ColorEdit3("clear color", (float*)&m_ClearColor); // Edit 3 floats representing a color
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		}
	}
}
