#pragma once

#include <GLFW/glfw3.h>
#include <KewlF/Window.hpp>

class OpenGLWindow : Window {
private:
	GLFWwindow* window;

	GLsizei bufNamesSize = 1;
	GLuint* bufNames = (GLuint*)alloca(bufNamesSize*sizeof(GLuint)); // bufNames[];
	GLuint shader;

public:
	OpenGLWindow();
	~OpenGLWindow();

	void init() override;
	//void show() override;

	void pullEvents();
};