#include "Test2DBatchRendering.hpp"

#include <glad/glad.h>
#include "OpenGLDebug.hpp"
#include <imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Vertex.hpp"

namespace test {
    Test2DBatchRendering::Test2DBatchRendering() {
        int vp[4];
        GLCall(glGetIntegerv(GL_VIEWPORT, vp));
        m_width = vp[2];
        m_height = vp[3];
        LOG(INFO) << "Window size = (" << m_width << "x" << m_height << ")" << std::endl;

        /*
        // 3D point, 2D TexMap Point, Tex index
        std::vector<float> vertexBuf = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, //0
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, //1
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, //2
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, //3

           - 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, //0
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, //1
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, //2
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f  //3

        };
        */

        //Indices buffer
        std::vector<unsigned int> indices = {
            0,1,2,
            2,3,0,

            4,5,6,
            6,7,4
        };

        m_texture1 = std::make_unique<Texture>("res/textures/Planning-And-Probing-1.jpg");
        m_texture2 = std::make_unique<Texture>("res/textures/jrrt.png");

        m_shader  = std::make_unique<Shader>("res/shaders/Test2DBatchRendering.shader");
        GLCall(glUseProgram(m_shader->getID()));
        GLCall(auto loc = glGetUniformLocation(m_shader->getID(), "u_textures"));
        int samplers[2] = { 0, 1 };
        GLCall(glUniform1iv(loc, 2, samplers));

        m_va      = std::make_unique<VertexArray>();
        //m_ib      = std::make_unique<IndexBuffer>(indices, 6);
        m_ib      = std::make_unique<IndexBuffer>(indices);

        //VertexBuffer vb(vertexBuf.data(), sizeof(vertexBuf[0]) * vertexBuf.size());
        m_vb = std::make_unique<VertexBuffer>(nullptr, sizeof(Vertex) * 1000);
        // Start Center of screen
        m_hw = m_width * 0.5f;
        m_hh = m_height * 0.5f;

        float qw = m_hw * 0.5f;

        m_translationA = { -qw, 0.0f, 0.0f };
        m_translationB = {  qw, 0.0f, 0.0f };

        // Set Matrices
        m_ident = glm::mat4(1.0f);
        m_scale = glm::scale(m_ident, glm::vec3(300.0f));
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
        m_layout.push<float>(4); // color
        m_layout.push<float>(2); // texture mapping
        m_layout.push<float>(1); // texture id
        m_va->addBuffer(*m_vb, m_layout);

        // Setup a Shader
        m_shader->bind();

        // Unbind once setup
        m_va->unbind();
        m_vb->unbind();
        m_ib->unbind();
        m_shader->unbind();
    }
    Test2DBatchRendering::~Test2DBatchRendering() {
    }

    void Test2DBatchRendering::onUpdate(float deltaTime) {
    }
    void Test2DBatchRendering::onRender() {
        GLCall(glClearColor(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]));
        m_renderer.clear(); //GLCall(glClear(GL_COLOR_BUFFER_BIT));

        {
            //set dynamic vertex buffer
            // 3D point, 2D TexMap Point, Tex index
            //std::vector<float> vertexBuf = {

            auto q0 = Vertex::CreateQuad(0);
            auto q1 = Vertex::CreateQuad(1);

            Vertex vertices[8];
            memcpy(vertices, q0.data(), q0.size() * sizeof(Vertex));
            memcpy(vertices + q0.size(), q1.data(), q1.size() * sizeof(Vertex));

            m_vb->bind();
            //GLCall(glMapBuffer());
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

            glBindTextureUnit(0, m_texture1->getID());
            glBindTextureUnit(1, m_texture2->getID());

            m_model = glm::translate(m_ident, m_translationA) * m_scale;
            m_mvp = m_proj * m_view * m_model;
            m_shader->bind();
            m_shader->setUniformMat4f("u_MVP", m_mvp);

            m_renderer.draw(*m_va, *m_ib, *m_shader);
            m_shader->unbind();
        }

        //{
        //    m_texture2->bind();
        //    m_model = glm::translate(m_ident, m_translationB) * m_scale;
        //    m_mvp = m_proj * m_view * m_model;
        //    m_shader->bind();
        //    m_shader->setUniformMat4f("u_MVP", m_mvp);
        //    m_renderer.draw(*m_va, *m_ib, *m_shader);
        //    m_shader->unbind();
        //    m_texture2->unbind();
        //}
    }

    void Test2DBatchRendering::onImGuiRender() {
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
