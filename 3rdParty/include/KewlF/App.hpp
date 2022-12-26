///////////////////////////////////////////////////////////////////////////////
//
// App.h
//
// Description:
// A custom foundation base Application Class to aid in starting and developing
// a C++ application.  It is meant to be extended and not used directly. The
// main function is meant to be hidden in the foundation library.
//
// Usage:
// Step 1: Create your App Class and extend App as public
//   i.e.:
//      class YourApp : public App {
//      ...
//      public:
//
//      ...
//      }
// Step 2: Define a protected static pointer for your App in your App Class
//   i.e.:
//      protected:
//      static YourApp *yourApp;
// Step 3: Declare, Create and follow a Singleton getInstance function for your app
//   i.e.:
//      YourApp &YourApp::yourApp = YourApp::getInstance();
//
//      YourApp &YourApp::getInstance() {
//         static YourApp instance; // created on heap and there is only one and should be freed upon exit of the executable
//         app = &instance; // this allows the underlying main function to hook into yourApp
//         return instance;
//      }
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

//#include "EventHandler.hpp"
 
class App { //: public EventHandler {
public:
    void operator=(App const &) = delete;

    virtual int processCmdLine(int _argCnt, char **_argList) {
        argCnt = _argCnt;
        argList = _argList;
        return 1;
    }
    char *getAppFileName() { return argList[0]; }

    friend int main(int ac, char **av);

protected:
    static App *app;
    static App& getApp();

    App(); // Default constructor hidden to make it a singleton
    App(App const &) = delete;
    virtual ~App();

    virtual void init();
    virtual void cleanUp(); // Clean up what init(ed) items
    virtual int runApp();

private:

    int argCnt = 0;
    char **argList = nullptr;

    virtual void processEventLoop();

//    virtual void onShown(WindowEvent &event) override;
};
