#pragma once

#include "Test.hpp"
namespace test {
	class TestClearColor : public Test {
	public:
		TestClearColor();
		~TestClearColor();

		void onUpdate(float deltaTime) override;
		void onRender() override;
		void onImGuiRender() override;
	private:
		float m_clearColor[4] = { 0.2f, 0.3f, 0.8f, 1.0f };
	};
}
