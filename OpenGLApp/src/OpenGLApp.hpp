// OpenGLApp.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include "KewlF/App.hpp"
#include "OpenGLWindow.hpp"

// TODO: Reference additional headers your program requires here.
class OpenGLApp : public App { 
private:
    OpenGLWindow m_window;

    void processEventLoop() override;

protected:
    void init() override;
    void cleanUp() override; // Clean up what init(ed) items
    int runApp() override;

public:
    OpenGLApp();
    ~OpenGLApp();
};

extern OpenGLApp openGLApp;