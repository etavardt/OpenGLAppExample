#include "Test.hpp"

#include "imgui.h"

namespace test {

	TestMenu::TestMenu(Test*& currentTestPointer) : m_CurrentTest(currentTestPointer) {

	}
	
	//TestMenu::~TestMenu() {}

	void TestMenu::onImGuiRender() {
		for (auto& test : m_Tests) {
			if (ImGui::Button(test.first.c_str())) {
				m_CurrentTest = test.second();
			}
		}
	}

}