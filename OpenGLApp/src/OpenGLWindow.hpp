#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <KewlF/Window.hpp>

class OpenGLWindow : Window {
private:
	GLFWwindow* m_window;

    unsigned int m_width;
    unsigned int m_height;

public:
	OpenGLWindow();
	~OpenGLWindow();

	void init() override;
	//void show() override;

	void pullEvents();
};