﻿// OpenGLApp.cpp : Defines the entry point for the application.
//

#include "OpenGLApp.hpp"

OpenGLApp& OpenGLApp::openGLApp = OpenGLApp::getInstance();

OpenGLApp::OpenGLApp() {
	std::cout << "OpenGLApp Constructed" << std::endl;
}
OpenGLApp::~OpenGLApp() {
	std::cout << "OpenGLApp Destructed" << std::endl;
}

OpenGLApp& OpenGLApp::getInstance() {
	static OpenGLApp instance; // should be created on heap? and there is only one and should be freed upon exit of the executable
	app = &instance; // this allows the underlying main function to hook into yourApp
	return instance;
}

int OpenGLApp::runApp() {
	std::cout << "Hello CMake." << std::endl;
	return 0;
}
