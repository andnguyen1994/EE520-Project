#ifndef __RELOAD_AGENT__H
#define __RELOAD_AGENT__H 

#include "enviro.h"

using namespace enviro;

class ReloadController : public Process, public AgentInterface {

    public:
    ReloadController() : Process(), AgentInterface() {}

    void init() {}
    void start() {}
    void update() {}
    void stop() {}

};

class Reload : public Agent {
    public:
    Reload(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    ReloadController c;
};

DECLARE_INTERFACE(Reload)

#endif