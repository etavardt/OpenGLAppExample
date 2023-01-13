#pragma once

#include <assert.h>
#include <GLFW/glfw3.h>

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) glClearError();\
    x;\
    ASSERT(glLogCall(#x, __FILE__, __LINE__))

void glClearError();
bool glLogCall(const char* function, const char* file, int line);

void error_callback(int error, const char* description);
void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods);

namespace glDebug {
	void initialize();
	bool isEnabled();
	void glLogErrorMessage();
} // namespace glDebug
