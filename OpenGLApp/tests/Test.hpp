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
		Test*& m_CurrentTest;
		std::vector<std::pair<std::string, std::function<Test* ()>>> m_Tests;
	public:
		TestMenu(Test*& currentTestPointer);
		//~TestMenu();

		//void onUpdate(float deltaTime) override;
		//void onRender() override;
		void onImGuiRender() override;
		
		template<typename T>
		void RegisterTest(const std::string& name) {
			LOG(INFO) << "Regisering test " << name << std::endl;
			m_Tests.push_back(std::make_pair(name, []() { return new T(); }));
		}
	};
}