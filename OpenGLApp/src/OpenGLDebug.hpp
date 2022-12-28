#pragma once

//#include "GL\glew.h"

namespace glDebug {
	void initialize();
	bool isEnabled();
	void glLogErrorMessage();
//#ifdef GL_KHR_debug
//
//#else // GL_KHR_debug
//
//#endif //GL_KHR_debug else
} // namespace glDebug