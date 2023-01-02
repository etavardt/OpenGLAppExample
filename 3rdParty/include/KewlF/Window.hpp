#pragma once

#include "EventHandler.hpp"

#include "String.hpp"
#include "Color.hpp"
#include "Image.hpp"

enum DrawPosition {
    CENTERED = -1
};
class Window : public EventHandler {
private:
    // unsigned int width  = 0;
    // unsigned int height = 0;

protected:
    // Color backgroundColor(0,0,0,255);
    Color backgroundColor = {0,0,0,255};
    Color foregroundColor = {255,255,255,255};

    float aspectRatio = 0.75f;
    float scale = 1.0f;

    int minWidth  = 0;
    int minHeight = 0;

    virtual void init();

    void displayText(const String &str, const int x, const int y);
    void displayImage(Image &image, const int x, const int y);

public:
    Window();
    virtual ~Window();

    bool toggleFullScreen();

    //void createWindow(const String title, int x, int y, int w, int h, Uint32 flags);
    virtual void createWindow();
    virtual void show();

    // Event functions


    // Window Specific
 
};