#pragma once

#include <map>

#include "String.hpp"

class EventHandler;
typedef unsigned long long EventHandlerId;
typedef std::map<EventHandlerId, EventHandler &> RegisteredEventHandlerMap;
typedef RegisteredEventHandlerMap::value_type RegisteredEventHandlerPair;

class EventHandler {
private:
    static RegisteredEventHandlerMap registeredEventHandlers;

protected:
    // EventHandler() = default;
    // EventHandler(EventHandler const &) = delete;
    // virtual ~EventHandler() = default;
    //virtual int registerEventHandling(EventHandler &ehObject);
    int registerEventHandling();
    void unRegisterEventHandling();

    // User overridable
    virtual bool pollAndHandleEvent();

    EventHandlerId id;

public:

};
