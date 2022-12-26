// OpenGLApp.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include "KewlF/App.hpp"

// TODO: Reference additional headers your program requires here.
class OpenGLApp : public App { 
private:
    static OpenGLApp &openGLApp;

    OpenGLApp();
    ~OpenGLApp();

    void processEventLoop() override {};

protected:
    //void init() override {};
    //void cleanUp() override {}; // Clean up what init(ed) items
    int runApp() override;

public:
    static inline OpenGLApp& getApp() { return openGLApp; }
    static OpenGLApp& getInstance();


};