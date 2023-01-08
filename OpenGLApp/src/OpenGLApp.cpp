// OpenGLApp.cpp : Defines the entry point for the application.
//
#include "OpenGLApp.hpp"

#include <iostream>
#include <KewlF/Logger.hpp>
//#include "OpenGLWindow.hpp"

OpenGLApp openGLApp;

OpenGLApp::OpenGLApp() {
	LOG(INFO) << "OpenGLApp Constructed" << std::endl;
}
OpenGLApp::~OpenGLApp() {
	LOG(INFO) << "OpenGLApp Destructed" << std::endl;
}

void OpenGLApp::init() {
	m_window.init();
}

int OpenGLApp::runApp() {

	//m_window.show();

	return App::runApp();
}

void OpenGLApp::cleanUp() {

}

void OpenGLApp::processEventLoop() {
	m_window.pullEvents();
}