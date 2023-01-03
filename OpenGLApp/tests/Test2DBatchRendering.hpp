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
		float m_ClearColor[4];

        VertexBufferLayout layout;

        //VertexArray* va;
        std::unique_ptr<VertexArray> va;

        VertexBuffer* vb;
        //std::unique_ptr<VertexBuffer> vb;

        //IndexBuffer* ib;
        std::unique_ptr<IndexBuffer> ib;

        //Shader shader;
        //Shader* shader;
        std::unique_ptr<Shader> shader;

        //Texture texture;
        //Texture* texture;
        //std::unique_ptr<Texture> texture;
        std::unique_ptr<Texture> texture1;
        std::unique_ptr<Texture> texture2;

        Renderer renderer;

        glm::mat4 proj;
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 mvp;

        unsigned int width;
        unsigned int height;

        float hw = 0;
        float hh = 0;

        glm::vec3 translationA;
        glm::vec3 translationB;

	};
}
