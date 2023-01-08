#include "Test.hpp"

#include "imgui.h"

namespace test {

	TestMenu::TestMenu(Test*& currentTestPointer) : m_currentTest(currentTestPointer) {

	}
	
	//TestMenu::~TestMenu() {}

	void TestMenu::onImGuiRender() {
		for (auto& test : m_tests) {
			if (ImGui::Button(test.first.c_str())) {
				m_currentTest = test.second();
			}
		}
	}

}