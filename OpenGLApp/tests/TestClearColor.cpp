#include "TestClearColor.hpp"

#include <gl/glew.h>
#include "OpenGLDebug.hpp"
#include <imgui.h>


namespace test {
	TestClearColor::TestClearColor() {
	}
	TestClearColor::~TestClearColor() {
	}

	void TestClearColor::onUpdate(float deltaTime) {
	}
	void TestClearColor::onRender() {
		GLCall(glClearColor(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}
	void TestClearColor::onImGuiRender() {
		ImGui::ColorEdit4("Clear Color", m_clearColor);
	}
}
