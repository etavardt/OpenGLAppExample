#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <KewlF/Window.hpp>

class OpenGLWindow : Window {
private:
	GLFWwindow* window;

    unsigned int width;
    unsigned int height;

public:
	OpenGLWindow();
	~OpenGLWindow();

	void init() override;
	//void show() override;

	void pullEvents();
};