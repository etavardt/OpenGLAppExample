#pragma once

#include <string>
#include <vector>
#include <functional>

#include <KewlF/Logger.hpp>

namespace test {
	class Test {
	public:
		Test() {}
		virtual ~Test() {}

		virtual void onUpdate(float deltaTime) {}
		virtual void onRender() {}
		virtual void onImGuiRender() {}
	};

	class TestMenu : public Test {
	private:
		Test*& m_currentTest;
		std::vector<std::pair<std::string, std::function<Test* ()>>> m_tests;
	public:
		TestMenu(Test*& currentTestPointer);

		void onImGuiRender() override;
		
		template<typename T>
		void RegisterTest(const std::string& name) {
			LOG(INFO) << "Registering test " << name << std::endl;
			m_tests.push_back(std::make_pair(name, []() { return new T(); }));
		}
	};
}